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
#include "lvgl.h"
#include "custom.h"

/**********************
 * STATIC VARIABLES
 **********************/
static void lvgl_update_timer(lv_timer_t *timer);

static lv_timer_t *update_timer = NULL;
static pthread_t modbus_thread;
static int modbus_thread_running = 0;

sensor_data_t current_sensor_data = {0};
pthread_mutex_t data_mutex = PTHREAD_MUTEX_INITIALIZER;
modbus_t *modbus_ctx = NULL;

extern lv_ui guider_ui; // GUI Guider 全局 UI 结构体

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
    // 主界面
    if (!ui->screen) {
        setup_ui(ui);
        bind_main_screen_events(ui);
    }
    // 相册界面
    if (!ui->screen_album) {
        setup_scr_screen_album(ui);
        bind_album_screen_events(ui);
        lv_obj_add_flag(ui->screen_album, LV_OBJ_FLAG_HIDDEN);
    }
    // 天气界面
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

    // 创建更新定时器
    update_timer = lv_timer_create(lvgl_update_timer, 500, ui);

    // 启动 Modbus 线程
    start_modbus_thread();
}

/****************************************************
 *                Modbus线程与数据更新
 ***************************************************/
void start_modbus_thread(void)
{
    modbus_ctx = modbus_new_rtu("/dev/ttymxc2", 115200, 'N', 8, 1);
    if (!modbus_ctx) {
        fprintf(stderr, "Unable to create libmodbus context\n");
        return;
    }
    modbus_set_slave(modbus_ctx, 1);
    modbus_set_response_timeout(modbus_ctx, 1, 0);
    if (modbus_connect(modbus_ctx) == -1) {
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        modbus_free(modbus_ctx);
        modbus_ctx = NULL;
        return;
    }
    printf("Connected to Modbus slave\n");

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
    if (modbus_ctx) {
        modbus_close(modbus_ctx);
        modbus_free(modbus_ctx);
        modbus_ctx = NULL;
    }
}

void *modbus_read_thread(void *arg)
{
    uint16_t tab_reg[7];
    while (modbus_thread_running) {
        int rc = modbus_read_registers(modbus_ctx, 0, 7, tab_reg);
        if (rc == 7) {
            pthread_mutex_lock(&data_mutex);
            current_sensor_data.aht10_humi = tab_reg[1];
            current_sensor_data.bh1750_light = tab_reg[2];
            current_sensor_data.bmp280_temp = (int16_t)tab_reg[3];
            current_sensor_data.bmp280_press = tab_reg[4];
            current_sensor_data.sgp30_co2 = tab_reg[5];
            current_sensor_data.sgp30_tvoc = tab_reg[6];
            float pressure_ratio = current_sensor_data.bmp280_press / 1013.25f;
            current_sensor_data.altitude = (uint16_t)(44330.0f * (1.0f - powf(pressure_ratio, 0.1903f)));
            pthread_mutex_unlock(&data_mutex);
            printf("Sensor data updated successfully\n");
        } else {
            fprintf(stderr, "Modbus read failed: %s\n", modbus_strerror(errno));
        }
        sleep(2);
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

    // 只在天气界面显示时更新数据
    if (ui->screen_weather && lv_obj_check_type(ui->screen_weather, &lv_obj_class) &&
        !lv_obj_has_flag(ui->screen_weather, LV_OBJ_FLAG_HIDDEN))
    {
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
        printf("Display updated with new data\n");
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
