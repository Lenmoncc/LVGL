/*
* Copyright 2024 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include "lvgl.h"
#include "custom.h"
#include "advanced_display.h"

/**********************
 * STATIC VARIABLES
 **********************/
static void lvgl_update_timer(lv_timer_t *timer);

static lv_timer_t *update_timer = NULL;
static pthread_t modbus_thread;
static volatile int modbus_thread_running = 0;

/* Modbus连接管理参数 */
static int consecutive_errors = 0;              // 连续读取失败计数
static const int MAX_CONSECUTIVE_ERRORS = 5;   // 触发重连的最大连续错误次数
static const int MODBUS_RECONNECT_DELAY = 3;   // 重连延迟时间（秒）

/* 轮询周期配置 */
static const int MODBUS_POLL_PERIOD_MS = 1000; // 定时轮询周期：1秒

sensor_data_t current_sensor_data = {0};
sensor_data_t last_display_data = {0};
pthread_mutex_t data_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t data_cond = PTHREAD_COND_INITIALIZER;
modbus_t *modbus_ctx = NULL;
volatile int modbus_connection_status = 0;

extern lv_ui guider_ui;

// 传感器数据有效范围定义
static const sensor_range_t sensor_ranges = {
    .humi_min = 0,      .humi_max = 100,
    .light_min = 0,     .light_max = 65535,
    .temp_min = -40,    .temp_max = 85,
    .press_min = 300,   .press_max = 1100,
    .co2_min = 400,     .co2_max = 5000,
    .tvoc_min = 0,      .tvoc_max = 60000
};

/****************************************************
 *          数据有效性检查和比较函数
 ***************************************************/
bool validate_sensor_data(const sensor_data_t *data)
{
    if (!data) return false;

    return (data->aht10_humi >= sensor_ranges.humi_min &&
            data->aht10_humi <= sensor_ranges.humi_max) &&
           (data->bh1750_light >= sensor_ranges.light_min &&
            data->bh1750_light <= sensor_ranges.light_max) &&
           (data->bmp280_temp >= sensor_ranges.temp_min &&
            data->bmp280_temp <= sensor_ranges.temp_max) &&
           (data->bmp280_press >= sensor_ranges.press_min &&
            data->bmp280_press <= sensor_ranges.press_max) &&
           (data->sgp30_co2 >= sensor_ranges.co2_min &&
            data->sgp30_co2 <= sensor_ranges.co2_max) &&
           (data->sgp30_tvoc >= sensor_ranges.tvoc_min &&
            data->sgp30_tvoc <= sensor_ranges.tvoc_max);
}

bool sensor_data_changed(const sensor_data_t *old_data, const sensor_data_t *new_data)
{
    if (!old_data || !new_data) return true;

    return (old_data->aht10_humi != new_data->aht10_humi) ||
           (old_data->bh1750_light != new_data->bh1750_light) ||
           (old_data->bmp280_temp != new_data->bmp280_temp) ||
           (old_data->bmp280_press != new_data->bmp280_press) ||
           (old_data->sgp30_co2 != new_data->sgp30_co2) ||
           (old_data->sgp30_tvoc != new_data->sgp30_tvoc) ||
           (old_data->altitude != new_data->altitude);
}

/****************************************************
 *                界面切换事件回调函数
 ***************************************************/
static void photo_event_handler(lv_event_t *e)
{
    LV_UNUSED(e);
    lv_obj_add_flag(guider_ui.screen, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.screen_album, LV_OBJ_FLAG_HIDDEN);
    lv_scr_load(guider_ui.screen_album);
}

static void album_back_event_handler(lv_event_t *e)
{
    LV_UNUSED(e);
    lv_obj_add_flag(guider_ui.screen_album, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.screen, LV_OBJ_FLAG_HIDDEN);
    lv_scr_load(guider_ui.screen);
}

static void weather_event_handler(lv_event_t *e)
{
    LV_UNUSED(e);
    lv_obj_add_flag(guider_ui.screen, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.screen_weather, LV_OBJ_FLAG_HIDDEN);
    lv_scr_load(guider_ui.screen_weather);
}

static void weather_back_event_handler(lv_event_t *e)
{
    LV_UNUSED(e);
    lv_obj_add_flag(guider_ui.screen_weather, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.screen, LV_OBJ_FLAG_HIDDEN);
    lv_scr_load(guider_ui.screen);
}

/****************************************************
 *                事件绑定辅助函数
 ***************************************************/
static void bind_main_screen_events(lv_ui *ui)
{
    if (ui->screen_img_1)
        lv_obj_add_event_cb(ui->screen_img_1, photo_event_handler, LV_EVENT_CLICKED, NULL);

    if (ui->screen_img_2)
        lv_obj_add_event_cb(ui->screen_img_2, weather_event_handler, LV_EVENT_CLICKED, NULL);
}

static void bind_album_screen_events(lv_ui *ui)
{
    if (ui->screen_album_btn_1)
        lv_obj_add_event_cb(ui->screen_album_btn_1, album_back_event_handler, LV_EVENT_CLICKED, NULL);
}

static void bind_weather_screen_events(lv_ui *ui)
{
    if (ui->screen_weather_btn_1)
        lv_obj_add_event_cb(ui->screen_weather_btn_1, weather_back_event_handler, LV_EVENT_CLICKED, NULL);
}

/****************************************************
 *                确保界面创建
 ***************************************************/
static void create_all_screens(lv_ui *ui)
{
    if (!ui->screen) {
        setup_ui(ui);
        bind_main_screen_events(ui);
    }
    if (!ui->screen_album) {
        setup_scr_screen_album(ui);
        bind_album_screen_events(ui);
        lv_obj_add_flag(ui->screen_album, LV_OBJ_FLAG_HIDDEN);
    }
    if (!ui->screen_weather) {
        setup_scr_screen_weather(ui);
        bind_weather_screen_events(ui);
        lv_obj_add_flag(ui->screen_weather, LV_OBJ_FLAG_HIDDEN);
    }
}

/****************************************************
 *                初始化入口
 ***************************************************/
void custom_init(lv_ui *ui)
{
    create_all_screens(ui);

    // 创建更新定时器，降低频率至1000ms以减少不必要的更新
    update_timer = lv_timer_create(lvgl_update_timer, 1000, ui);
    if (update_timer) {
        // 仅在有数据时期运行定时器
        lv_timer_pause(update_timer);
    }

    // 初始化高级显示模块（曲线显示、告警、资源优化）
    advanced_display_init(ui);

    // 启动 Modbus 线程
    start_modbus_thread();

    fprintf(stdout, "[OK] Custom initialization completed\n");
}

/****************************************************
 *           Modbus连接和超时重连管理
 ****************************************************/

/**
 * @brief Modbus 连接和重连函数
 *
 * 功能描述：
 * 1. 关闭现有的 Modbus 连接（如果存在）
 * 2. 创建新的 RTU 上下文
 * 3. 设置从机地址和响应超时
 * 4. 建立新的连接
 *
 * 超时配置：
 * - modbus_set_response_timeout(ctx, 1, 0)：设置响应超时为 1 秒
 * - 如果从机在 1 秒内未响应，Modbus 库会自动返回错误
 * - 这个超时触发后会被上层的"连续错误检测"机制捕获
 *
 * 重连机制：
 * - 当连续读取失败次数达到 MAX_CONSECUTIVE_ERRORS (5次) 时触发
 * - 重连会在关闭旧连接 3 秒后创建新连接
 * - 这样可以确保串口完全释放，避免资源泄漏
 */
void reconnect_modbus(void)
{
    if (modbus_ctx) {
        modbus_close(modbus_ctx);
        modbus_free(modbus_ctx);
        modbus_ctx = NULL;
        fprintf(stderr, "Previous Modbus connection closed\n");
    }

    fprintf(stdout, "Attempting to create new Modbus RTU context...\n");

    /* 创建 RTU 上下文
     * 参数说明：
     * - "/dev/ttymxc2"：串口设备路径
     * - 115200：波特率
     * - 'N'：奇偶校验（None）
     * - 8：数据位
     * - 1：停止位
     */
    modbus_ctx = modbus_new_rtu("/dev/ttymxc2", 115200, 'N', 8, 1);
    if (!modbus_ctx) {
        fprintf(stderr, "Unable to create the libmodbus context\n");
        modbus_connection_status = 0;
        return;
    }

    /* 设置从机地址 */
    modbus_set_slave(modbus_ctx, 1);

    /* 设置响应超时为 1 秒（1 秒 0 微秒）
     * 这是串口级别的超时，如果从机在此时间内未响应，会返回错误
     * 该错误被轮询线程捕获，连续超时会触发自动重连
     */
    modbus_set_response_timeout(modbus_ctx, 1, 0);

    /* 尝试建立连接 */
    if (modbus_connect(modbus_ctx) == -1) {
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        modbus_free(modbus_ctx);
        modbus_ctx = NULL;
        modbus_connection_status = 0;
        return;
    }

    fprintf(stdout, "Successfully connected to Modbus slave\n");
    modbus_connection_status = 1;
    consecutive_errors = 0;  /* 重置错误计数 */
}

/****************************************************
 *         Modbus线程启动和停止管理
 ****************************************************/

/**
 * @brief 启动 Modbus 读取线程
 *
 * 功能描述：
 * 1. 初始化 Modbus 连接
 * 2. 创建独立的读取线程
 * 3. 该线程定时轮询从机数据
 *
 * 线程生命周期：
 * - 线程以分离态运行，自动释放资源
 * - 通过 modbus_thread_running 标志控制
 * - 由 stop_modbus_thread() 函数关闭
 */
void start_modbus_thread(void)
{
    /* 首次连接初始化 */
    reconnect_modbus();

    if (!modbus_ctx) {
        fprintf(stderr, "Failed to initialize Modbus context\n");
        return;
    }

    modbus_thread_running = 1;
    if (pthread_create(&modbus_thread, NULL, modbus_read_thread, NULL) != 0) {
        fprintf(stderr, "Failed to create Modbus thread\n");
        modbus_close(modbus_ctx);
        modbus_free(modbus_ctx);
        modbus_ctx = NULL;
        modbus_thread_running = 0;
        return;
    }

    /* 线程分离态运行
     * 这样线程结束时会自动释放资源，无需 pthread_join
     */
    pthread_detach(modbus_thread);
    fprintf(stdout, "Modbus read thread started (1 second poll period)\n");
}

/**
 * @brief 停止 Modbus 读取线程
 *
 * 功能描述：
 * 1. 设置停止标志，使轮询线程退出
 * 2. 发送条件变量信号唤醒可能正在等待的线程
 * 3. 关闭 Modbus 连接
 * 4. 释放资源
 */
void stop_modbus_thread(void)
{
    modbus_thread_running = 0;
    pthread_cond_signal(&data_cond);

    if (modbus_ctx) {
        modbus_close(modbus_ctx);
        modbus_free(modbus_ctx);
        modbus_ctx = NULL;
    }
    modbus_connection_status = 0;
    fprintf(stdout, "Modbus thread stopped\n");
}

/**
 * @brief Modbus 主站读取线程
 *
 * 功能描述：
 * 1. 按照 1 秒的固定周期轮询从机数据
 * 2. 实现串口超时自动重连机制
 * 3. 数据有效性验证
 * 4. 条件变量通知 UI 更新
 *
 * 工作流程：
 * - 每 1 秒读取一次寄存器数据（7 个寄存器）
 * - 读取成功且数据有效则更新共享数据
 * - 连续失败超过阈值则自动重连串口
 * - 通过条件变量通知 UI 线程进行更新
 */
void *modbus_read_thread(void *arg)
{
    (void)arg;
    uint16_t tab_reg[7];
    int failure_count = 0;
    const int MAX_READ_FAILURES = 3;
    struct timespec poll_time;

    while (modbus_thread_running) {
        /* 如果连接未建立，等待 MODBUS_RECONNECT_DELAY 秒后重试 */
        if (!modbus_ctx) {
            fprintf(stderr, "Modbus context not available, waiting %d seconds before retry\n",
                    MODBUS_RECONNECT_DELAY);
            sleep(MODBUS_RECONNECT_DELAY);
            continue;
        }

        /* ===== 数据读取阶段 ===== */
        /* 尝试从从机读取 7 个寄存器：
         * 寄存器0：AHT10温度
         * 寄存器1：AHT10湿度
         * 寄存器2：BH1750光照
         * 寄存器3：BMP280温度
         * 寄存器4：BMP280气压
         * 寄存器5：SGP30 CO2
         * 寄存器6：SGP30 TVOC
         */
        int rc = modbus_read_registers(modbus_ctx, 0, 7, tab_reg);

        if (rc == 7) {
            /* ===== 数据验证阶段 ===== */
            sensor_data_t new_data;
            new_data.aht10_humi = tab_reg[1];
            new_data.bh1750_light = tab_reg[2];
            new_data.bmp280_temp = (int16_t)tab_reg[3];
            new_data.bmp280_press = tab_reg[4];
            new_data.sgp30_co2 = tab_reg[5];
            new_data.sgp30_tvoc = tab_reg[6];

            /* 检查数据是否在有效范围内 */
            if (validate_sensor_data(&new_data)) {
                /* 计算海拔高度（基于气压值） */
                float pressure_ratio = new_data.bmp280_press / 1013.25f;
                new_data.altitude = (uint16_t)(44330.0f * (1.0f - powf(pressure_ratio, 0.1903f)));
                new_data.data_valid = true;

                /* ===== 数据更新阶段 ===== */
                /* 使用互斥锁保护共享数据，确保线程安全 */
                pthread_mutex_lock(&data_mutex);
                if (sensor_data_changed(&current_sensor_data, &new_data)) {
                    current_sensor_data = new_data;
                    current_sensor_data.update_count++;
                    /* 发送条件变量信号，唤醒等待的 UI 更新线程 */
                    pthread_cond_signal(&data_cond);
                }
                pthread_mutex_unlock(&data_mutex);

                /* 读取成功，清除错误计数 */
                failure_count = 0;
                consecutive_errors = 0;
                fprintf(stdout, "Sensor data updated (update_count: %u)\n", new_data.update_count);
            } else {
                /* 数据验证失败，记录错误 */
                fprintf(stderr, "Received invalid sensor data (out of range)\n");
                failure_count++;
            }
        } else {
            /* ===== 读取失败处理 ===== */
            fprintf(stderr, "Modbus read failed: %s\n", modbus_strerror(errno));
            failure_count++;
            consecutive_errors++;
        }

        /* ===== 超时重连机制 ===== */
        /* 如果连续读取失败超过阈值，主动断开连接并重连
         * 这样可以恢复可能卡住的串口状态
         */
        if (failure_count >= MAX_READ_FAILURES && consecutive_errors >= MAX_CONSECUTIVE_ERRORS) {
            fprintf(stderr, "Too many read failures (%d), attempting to reconnect...\n",
                    consecutive_errors);
            reconnect_modbus();
            failure_count = 0;
        }

        /* ===== 轮询周期控制 ===== */
        /* 使用 clock_nanosleep 实现精确的 1 秒周期轮询
         * 相比使用 sleep() 或条件变量超时，这种方式更精确
         * CLOCK_MONOTONIC 不受系统时间调整影响
         */
        clock_gettime(CLOCK_MONOTONIC, &poll_time);
        poll_time.tv_sec += 1;  // 增加 1 秒

        /* 进行 nanosleep，精确等待直到下一个轮询周期 */
        while (clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &poll_time, NULL) == EINTR) {
            /* 如果被信号中断，继续等待 */
        }
    }
    return NULL;
}

/****************************************************
 *                更新 LVGL 显示
 ***************************************************/
void update_lvgl_display(lv_ui *ui)
{
    sensor_data_t local_data;
    pthread_mutex_lock(&data_mutex);
    local_data = current_sensor_data;
    pthread_mutex_unlock(&data_mutex);

    // 检查数据有效性和是否有实际变化
    if (!local_data.data_valid) {
        return;
    }

    // 更新高级显示（包含曲线、告警等）
    advanced_display_update(&local_data);

    // 只在天气界面显示时更新数据，并且只在数据变化时更新
    if (ui->screen_weather && lv_obj_check_type(ui->screen_weather, &lv_obj_class) &&
        !lv_obj_has_flag(ui->screen_weather, LV_OBJ_FLAG_HIDDEN))
    {
        // 检查数据是否真的有变化
        if (!sensor_data_changed(&last_display_data, &local_data)) {
            return;
        }

        // 条件性更新各个字段
        if (ui->screen_weather_label_11)
            lv_label_set_text_fmt(ui->screen_weather_label_11, "%d°C", local_data.bmp280_temp);
        if (ui->screen_weather_label_17)
            lv_label_set_text_fmt(ui->screen_weather_label_17, "%d%%", local_data.aht10_humi);
        if (ui->screen_weather_label_9)
            lv_label_set_text_fmt(ui->screen_weather_label_9, "%dhPa", local_data.bmp280_press);
        if (ui->screen_weather_label_15)
            lv_label_set_text_fmt(ui->screen_weather_label_15, "%dm", local_data.altitude);
        if (ui->screen_weather_label_12)
            lv_label_set_text_fmt(ui->screen_weather_label_12, "%dlx", local_data.bh1750_light);
        if (ui->screen_weather_label_14)
            lv_label_set_text_fmt(ui->screen_weather_label_14, "%d", local_data.sgp30_co2);
        if (ui->screen_weather_label_13)
            lv_label_set_text_fmt(ui->screen_weather_label_13, "%d", local_data.sgp30_tvoc);

        // 更新记录，避免重复更新
        last_display_data = local_data;
        fprintf(stdout, "Display updated\n");
    }
}

/****************************************************
 *                LVGL定时器回调
 ***************************************************/
static void lvgl_update_timer(lv_timer_t *timer)
{
    lv_ui *ui = (lv_ui *)lv_timer_get_user_data(timer);
    if (ui)
        update_lvgl_display(ui);
}
