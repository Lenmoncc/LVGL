/*
* Copyright 2024 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef __CUSTOM_H_
#define __CUSTOM_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "EnvMonitor/generated/gui_guider.h"
#include "EnvMonitor/generated/events_init.h"
#include <modbus.h>
#include <pthread.h>
#include <stdint.h>
#include <errno.h>

// 传感器数据结构体
typedef struct {
    uint16_t aht10_humi;     // AHT10湿度 (%)
    uint16_t bh1750_light;   // BH1750光照强度 (lx)
    int16_t bmp280_temp;     // BMP280温度 (°C)
    uint16_t bmp280_press;   // BMP280压强 (hPa)
    uint16_t sgp30_co2;      // SGP30 eCO2 (ppm)
    uint16_t sgp30_tvoc;     // SGP30 TVOC (ppb)
    uint16_t altitude;       // 计算得到的海拔 (m)
} sensor_data_t;

// 全局变量声明
extern sensor_data_t current_sensor_data;
extern pthread_mutex_t data_mutex;
extern modbus_t *modbus_ctx;

// 函数声明
void custom_init(lv_ui *ui);
void update_lvgl_display(lv_ui *ui);
void *modbus_read_thread(void *arg);
void start_modbus_thread(void);
void stop_modbus_thread(void);


#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
