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
static int consecutive_errors = 0;
static const int MAX_CONSECUTIVE_ERRORS = 5;
static const int MODBUS_RECONNECT_DELAY = 3;

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
 *           Modbus连接和重连管理
 ***************************************************/
void reconnect_modbus(void)
{
    if (modbus_ctx) {
        modbus_close(modbus_ctx);
        modbus_free(modbus_ctx);
        modbus_ctx = NULL;
    }

    modbus_ctx = modbus_new_rtu("/dev/ttymxc2", 115200, 'N', 8, 1);
    if (!modbus_ctx) {
        fprintf(stderr, "Unable to create libmodbus context\n");
        modbus_connection_status = 0;
        return;
    }

    modbus_set_slave(modbus_ctx, 1);
    modbus_set_response_timeout(modbus_ctx, 1, 0);

    if (modbus_connect(modbus_ctx) == -1) {
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        modbus_free(modbus_ctx);
        modbus_ctx = NULL;
        modbus_connection_status = 0;
        return;
    }

    fprintf(stdout, "Connected to Modbus slave\n");
    modbus_connection_status = 1;
    consecutive_errors = 0;
}

/****************************************************
 *                Modbus线程与数据更新
 ***************************************************/
void start_modbus_thread(void)
{
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
    pthread_detach(modbus_thread);
}

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
}

void *modbus_read_thread(void *arg)
{
    (void)arg;
    uint16_t tab_reg[7];
    int failure_count = 0;
    const int MAX_READ_FAILURES = 3;

    while (modbus_thread_running) {
        if (!modbus_ctx) {
            sleep(MODBUS_RECONNECT_DELAY);
            continue;
        }

        int rc = modbus_read_registers(modbus_ctx, 0, 7, tab_reg);

        if (rc == 7) {
            // 创建临时数据结构进行验证
            sensor_data_t new_data;
            new_data.aht10_humi = tab_reg[1];
            new_data.bh1750_light = tab_reg[2];
            new_data.bmp280_temp = (int16_t)tab_reg[3];
            new_data.bmp280_press = tab_reg[4];
            new_data.sgp30_co2 = tab_reg[5];
            new_data.sgp30_tvoc = tab_reg[6];

            // 数据验证
            if (validate_sensor_data(&new_data)) {
                // 计算海拔
                float pressure_ratio = new_data.bmp280_press / 1013.25f;
                new_data.altitude = (uint16_t)(44330.0f * (1.0f - powf(pressure_ratio, 0.1903f)));
                new_data.data_valid = true;

                // 原子性更新数据和标志
                pthread_mutex_lock(&data_mutex);
                if (sensor_data_changed(&current_sensor_data, &new_data)) {
                    current_sensor_data = new_data;
                    current_sensor_data.update_count++;
                    // 通知显示线程有新数据
                    pthread_cond_signal(&data_cond);
                }
                pthread_mutex_unlock(&data_mutex);

                failure_count = 0;
                consecutive_errors = 0;
                fprintf(stdout, "Sensor data updated (update_count: %u)\n", new_data.update_count);
            } else {
                fprintf(stderr, "Received invalid sensor data\n");
                failure_count++;
            }
        } else {
            fprintf(stderr, "Modbus read failed: %s\n", modbus_strerror(errno));
            failure_count++;
            consecutive_errors++;
        }

        // 如果连续失败过多次，尝试重连
        if (failure_count >= MAX_READ_FAILURES && consecutive_errors >= MAX_CONSECUTIVE_ERRORS) {
            fprintf(stderr, "Too many read failures, attempting to reconnect...\n");
            reconnect_modbus();
            failure_count = 0;
        }

        // 优化：使用条件变量等待或2秒超时以降低CPU占用
        struct timespec timeout;
        clock_gettime(CLOCK_REALTIME, &timeout);
        timeout.tv_sec += 2;

        pthread_mutex_lock(&data_mutex);
        pthread_cond_timedwait(&data_cond, &data_mutex, &timeout);
        pthread_mutex_unlock(&data_mutex);
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
