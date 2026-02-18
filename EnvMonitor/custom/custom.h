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
#include "chart_display.h"
#include "resource_optimizer.h"
#include <modbus.h>
#include <pthread.h>
#include <stdint.h>
#include <errno.h>
#include <stdbool.h>

// 传感器数据结构体
typedef struct {
    uint16_t aht10_humi;     // AHT10湿度 (%)
    uint16_t bh1750_light;   // BH1750光照强度 (lx)
    int16_t bmp280_temp;     // BMP280温度 (°C)
    uint16_t bmp280_press;   // BMP280压强 (hPa)
    uint16_t sgp30_co2;      // SGP30 eCO2 (ppm)
    uint16_t sgp30_tvoc;     // SGP30 TVOC (ppb)
    uint16_t altitude;       // 计算得到的海拔 (m)
    bool data_valid;         // 数据有效性标志
    uint32_t update_count;   // 更新计数器
} sensor_data_t;

// 传感器数据范围定义（用于有效性检查）
typedef struct {
    uint16_t humi_min, humi_max;       // 湿度范围: 0-100%
    uint16_t light_min, light_max;     // 光照范围: 0-65535 lx
    int16_t temp_min, temp_max;        // 温度范围: -40-85°C
    uint16_t press_min, press_max;     // 气压范围: 300-1100 hPa
    uint16_t co2_min, co2_max;         // CO2范围: 400-5000 ppm
    uint16_t tvoc_min, tvoc_max;       // TVOC范围: 0-60000 ppb
} sensor_range_t;

// 全局变量声明
extern sensor_data_t current_sensor_data;
extern sensor_data_t last_display_data;
extern pthread_mutex_t data_mutex;
extern pthread_cond_t data_cond;
extern modbus_t *modbus_ctx;
extern volatile int modbus_connection_status;

// 函数声明
void custom_init(lv_ui *ui);
void update_lvgl_display(lv_ui *ui);
void *modbus_read_thread(void *arg);
void start_modbus_thread(void);
void stop_modbus_thread(void);
bool validate_sensor_data(const sensor_data_t *data);
bool sensor_data_changed(const sensor_data_t *old_data, const sensor_data_t *new_data);
void reconnect_modbus(void);

#ifdef __cplusplus
}
#endif
#endif /* __CUSTOM_H_ */
