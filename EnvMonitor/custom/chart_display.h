#ifndef __CHART_DISPLAY_H_
#define __CHART_DISPLAY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "custom.h"
#include <stdint.h>
#include <time.h>

/*
 * 环境数据曲线显示和告警模块
 * 提供实时曲线绘制、数据缓冲和异常告警功能
 */

// 曲线数据点容量（设计为环形缓冲区，省内存）
#define CHART_DATA_CAPACITY 120          // 120个数据点，约10分钟（每5秒采样一次）
#define CHART_POINT_SIZE sizeof(chart_data_point_t)

// 告警级别定义
typedef enum {
    ALERT_LEVEL_NONE = 0,               // 无告警
    ALERT_LEVEL_WARNING = 1,            // 警告（黄色）
    ALERT_LEVEL_CRITICAL = 2            // 严重（红色）
} alert_level_t;

// 单个数据点结构
typedef struct {
    uint32_t timestamp;                 // 时间戳
    int16_t temp;                       // 温度
    uint16_t humidity;                  // 湿度
    uint16_t co2;                       // CO2
    uint16_t tvoc;                      // TVOC
    uint16_t pressure;                  // 气压
    uint16_t light;                     // 光照
} chart_data_point_t;

// 曲线缓冲区结构（环形缓冲区）
typedef struct {
    chart_data_point_t data[CHART_DATA_CAPACITY];
    uint16_t head;                      // 写入位置
    uint16_t count;                     // 当前数据点数
    pthread_mutex_t lock;               // 线程安全保护
} chart_ring_buffer_t;

// 告警配置结构
typedef struct {
    // 温度告警阈值 (°C)
    int16_t temp_warning_min, temp_warning_max;
    int16_t temp_critical_min, temp_critical_max;

    // 湿度告警阈值 (%)
    uint16_t humidity_warning_min, humidity_warning_max;
    uint16_t humidity_critical_min, humidity_critical_max;

    // CO2告警阈值 (ppm)
    uint16_t co2_warning;
    uint16_t co2_critical;

    // TVOC告警阈值 (ppb)
    uint16_t tvoc_warning;
    uint16_t tvoc_critical;

    // 气压告警阈值 (hPa)
    uint16_t press_warning_min, press_warning_max;
    uint16_t press_critical_min, press_critical_max;
} alert_config_t;

// 告警状态结构
typedef struct {
    alert_level_t temp_alert;
    alert_level_t humidity_alert;
    alert_level_t co2_alert;
    alert_level_t tvoc_alert;
    alert_level_t pressure_alert;
    uint32_t last_alert_time;           // 上次告警时间
    uint32_t alert_count;               // 告警次数
} alert_status_t;

// 曲线显示上下文
typedef struct {
    lv_obj_t *parent;                   // 父容器
    lv_obj_t *chart;                    // 曲线对象（可选，用于高级场景）

    chart_ring_buffer_t buffer;         // 环形缓冲区
    alert_config_t alert_config;        // 告警配置
    alert_status_t alert_status;        // 告警状态

    uint32_t last_update_time;          // 上次更新时间
    uint32_t update_interval;           // 更新间隔（毫秒）

    bool flashing;                      // 是否闪烁
    uint32_t flash_count;               // 闪烁计数
} chart_display_context_t;

// 函数声明

// 初始化和清理
chart_display_context_t* chart_display_create(lv_obj_t *parent);
void chart_display_destroy(chart_display_context_t *ctx);

// 环形缓冲区操作
void chart_buffer_push(chart_ring_buffer_t *buf, const chart_data_point_t *point);
void chart_buffer_clear(chart_ring_buffer_t *buf);
uint16_t chart_buffer_count(chart_ring_buffer_t *buf);
const chart_data_point_t* chart_buffer_get(chart_ring_buffer_t *buf, uint16_t index);

// 告警配置
void chart_set_alert_config(chart_display_context_t *ctx, const alert_config_t *config);
alert_level_t chart_check_alert(chart_display_context_t *ctx, const sensor_data_t *data);
const alert_status_t* chart_get_alert_status(chart_display_context_t *ctx);

// 数据更新和显示
void chart_display_update(chart_display_context_t *ctx, const sensor_data_t *data);
void chart_display_draw(chart_display_context_t *ctx);
void chart_display_flash_alert(chart_display_context_t *ctx);

// 获取统计数据
float chart_get_temp_average(chart_display_context_t *ctx);
float chart_get_humidity_average(chart_display_context_t *ctx);
int16_t chart_get_temp_max(chart_display_context_t *ctx);
int16_t chart_get_temp_min(chart_display_context_t *ctx);

#ifdef __cplusplus
}
#endif
#endif /* __CHART_DISPLAY_H_ */
