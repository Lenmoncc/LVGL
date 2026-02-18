/*
 * 环境数据曲线显示和告警实现
 * 提供高效的环形缓冲区数据管理和实时告警机制
 */

#include "chart_display.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

// 默认告警配置
static const alert_config_t default_alert_config = {
    // 温度: 正常18-28°C，警告10-35°C，严重<5或>40°C
    .temp_warning_min = 10,
    .temp_warning_max = 35,
    .temp_critical_min = 5,
    .temp_critical_max = 40,

    // 湿度: 正常30-70%，警告20-80%，严重<10或>90%
    .humidity_warning_min = 20,
    .humidity_warning_max = 80,
    .humidity_critical_min = 10,
    .humidity_critical_max = 90,

    // CO2: 正常<800ppm，警告800-1200ppm，严重>1200ppm
    .co2_warning = 800,
    .co2_critical = 1200,

    // TVOC: 正常<260ppb，警告260-660ppb，严重>660ppb
    .tvoc_warning = 260,
    .tvoc_critical = 660,

    // 气压: 正常980-1040hPa，警告950-1070hPa，严重<920或>1100hPa
    .press_warning_min = 950,
    .press_warning_max = 1070,
    .press_critical_min = 920,
    .press_critical_max = 1100
};

/*
 * 环形缓冲区操作
 */

void chart_buffer_push(chart_ring_buffer_t *buf, const chart_data_point_t *point)
{
    if (!buf || !point) return;

    pthread_mutex_lock(&buf->lock);

    // 写入新数据
    buf->data[buf->head] = *point;
    buf->head = (buf->head + 1) % CHART_DATA_CAPACITY;

    // 如果还未填满，增加计数
    if (buf->count < CHART_DATA_CAPACITY) {
        buf->count++;
    }

    pthread_mutex_unlock(&buf->lock);
}

void chart_buffer_clear(chart_ring_buffer_t *buf)
{
    if (!buf) return;

    pthread_mutex_lock(&buf->lock);
    buf->head = 0;
    buf->count = 0;
    memset(buf->data, 0, sizeof(buf->data));
    pthread_mutex_unlock(&buf->lock);
}

uint16_t chart_buffer_count(chart_ring_buffer_t *buf)
{
    if (!buf) return 0;

    pthread_mutex_lock(&buf->lock);
    uint16_t count = buf->count;
    pthread_mutex_unlock(&buf->lock);

    return count;
}

const chart_data_point_t* chart_buffer_get(chart_ring_buffer_t *buf, uint16_t index)
{
    if (!buf || index >= buf->count) return NULL;

    static chart_data_point_t copy;

    pthread_mutex_lock(&buf->lock);

    // 计算实际位置：最早的数据在 (head - count + index) % capacity
    uint16_t actual_index = (buf->head - buf->count + index) % CHART_DATA_CAPACITY;
    copy = buf->data[actual_index];

    pthread_mutex_unlock(&buf->lock);

    return &copy;
}

/*
 * 告警判断逻辑
 */

static alert_level_t check_single_alert(int16_t value, int16_t warn_min, int16_t warn_max,
                                        int16_t crit_min, int16_t crit_max)
{
    if (value < crit_min || value > crit_max) {
        return ALERT_LEVEL_CRITICAL;
    }
    if (value < warn_min || value > warn_max) {
        return ALERT_LEVEL_WARNING;
    }
    return ALERT_LEVEL_NONE;
}

static alert_level_t check_single_alert_u16(uint16_t value, uint16_t warn_min, uint16_t warn_max,
                                            uint16_t crit_min, uint16_t crit_max)
{
    if (value < crit_min || value > crit_max) {
        return ALERT_LEVEL_CRITICAL;
    }
    if (value < warn_min || value > warn_max) {
        return ALERT_LEVEL_WARNING;
    }
    return ALERT_LEVEL_NONE;
}

static alert_level_t check_upper_threshold(uint16_t value, uint16_t warn, uint16_t crit)
{
    if (value >= crit) {
        return ALERT_LEVEL_CRITICAL;
    }
    if (value >= warn) {
        return ALERT_LEVEL_WARNING;
    }
    return ALERT_LEVEL_NONE;
}

alert_level_t chart_check_alert(chart_display_context_t *ctx, const sensor_data_t *data)
{
    if (!ctx || !data) return ALERT_LEVEL_NONE;

    alert_level_t max_level = ALERT_LEVEL_NONE;
    alert_config_t *cfg = &ctx->alert_config;

    // 检查温度
    alert_level_t temp_level = check_single_alert(
        data->bmp280_temp,
        cfg->temp_warning_min, cfg->temp_warning_max,
        cfg->temp_critical_min, cfg->temp_critical_max
    );
    ctx->alert_status.temp_alert = temp_level;
    if (temp_level > max_level) max_level = temp_level;

    // 检查湿度
    alert_level_t hum_level = check_single_alert_u16(
        data->aht10_humi,
        cfg->humidity_warning_min, cfg->humidity_warning_max,
        cfg->humidity_critical_min, cfg->humidity_critical_max
    );
    ctx->alert_status.humidity_alert = hum_level;
    if (hum_level > max_level) max_level = hum_level;

    // 检查CO2（仅上限告警）
    alert_level_t co2_level = check_upper_threshold(
        data->sgp30_co2,
        cfg->co2_warning,
        cfg->co2_critical
    );
    ctx->alert_status.co2_alert = co2_level;
    if (co2_level > max_level) max_level = co2_level;

    // 检查TVOC（仅上限告警）
    alert_level_t tvoc_level = check_upper_threshold(
        data->sgp30_tvoc,
        cfg->tvoc_warning,
        cfg->tvoc_critical
    );
    ctx->alert_status.tvoc_alert = tvoc_level;
    if (tvoc_level > max_level) max_level = tvoc_level;

    // 检查气压
    alert_level_t press_level = check_single_alert_u16(
        data->bmp280_press,
        cfg->press_warning_min, cfg->press_warning_max,
        cfg->press_critical_min, cfg->press_critical_max
    );
    ctx->alert_status.pressure_alert = press_level;
    if (press_level > max_level) max_level = press_level;

    // 更新告警统计
    if (max_level > ALERT_LEVEL_NONE) {
        ctx->alert_status.last_alert_time = time(NULL);
        ctx->alert_status.alert_count++;
    }

    return max_level;
}

/*
 * 初始化和清理
 */

chart_display_context_t* chart_display_create(lv_obj_t *parent)
{
    chart_display_context_t *ctx = (chart_display_context_t *)
        malloc(sizeof(chart_display_context_t));

    if (!ctx) return NULL;

    // 初始化
    ctx->parent = parent;
    ctx->chart = NULL;
    ctx->last_update_time = 0;
    ctx->update_interval = 5000;        // 默认5秒更新一次
    ctx->flashing = false;
    ctx->flash_count = 0;

    // 初始化缓冲区
    ctx->buffer.head = 0;
    ctx->buffer.count = 0;
    pthread_mutex_init(&ctx->buffer.lock, NULL);
    memset(ctx->buffer.data, 0, sizeof(ctx->buffer.data));

    // 设置默认告警配置
    ctx->alert_config = default_alert_config;

    // 初始化告警状态
    ctx->alert_status.temp_alert = ALERT_LEVEL_NONE;
    ctx->alert_status.humidity_alert = ALERT_LEVEL_NONE;
    ctx->alert_status.co2_alert = ALERT_LEVEL_NONE;
    ctx->alert_status.tvoc_alert = ALERT_LEVEL_NONE;
    ctx->alert_status.pressure_alert = ALERT_LEVEL_NONE;
    ctx->alert_status.last_alert_time = 0;
    ctx->alert_status.alert_count = 0;

    return ctx;
}

void chart_display_destroy(chart_display_context_t *ctx)
{
    if (!ctx) return;

    pthread_mutex_destroy(&ctx->buffer.lock);
    free(ctx);
}

void chart_set_alert_config(chart_display_context_t *ctx, const alert_config_t *config)
{
    if (!ctx || !config) return;
    ctx->alert_config = *config;
}

const alert_status_t* chart_get_alert_status(chart_display_context_t *ctx)
{
    if (!ctx) return NULL;
    return &ctx->alert_status;
}

/*
 * 数据更新和显示
 */

void chart_display_update(chart_display_context_t *ctx, const sensor_data_t *data)
{
    if (!ctx || !data) return;

    // 检查更新间隔
    uint32_t current_time = time(NULL) * 1000;
    if (current_time - ctx->last_update_time < ctx->update_interval) {
        return;
    }

    // 创建数据点
    chart_data_point_t point;
    point.timestamp = current_time;
    point.temp = data->bmp280_temp;
    point.humidity = data->aht10_humi;
    point.co2 = data->sgp30_co2;
    point.tvoc = data->sgp30_tvoc;
    point.pressure = data->bmp280_press;
    point.light = data->bh1750_light;

    // 添加到缓冲区
    chart_buffer_push(&ctx->buffer, &point);

    // 更新时间戳
    ctx->last_update_time = current_time;

    // 检查告警
    chart_check_alert(ctx, data);
}

void chart_display_draw(chart_display_context_t *ctx)
{
    if (!ctx || !ctx->parent) return;

    // TODO: 实现曲线绘制逻辑
    // 这里可以使用LVGL的lv_chart对象或自定义绘制
}

void chart_display_flash_alert(chart_display_context_t *ctx)
{
    if (!ctx) return;

    alert_status_t *status = &ctx->alert_status;

    // 检查是否有告警
    alert_level_t max_level = ALERT_LEVEL_NONE;
    if (status->temp_alert > max_level) max_level = status->temp_alert;
    if (status->humidity_alert > max_level) max_level = status->humidity_alert;
    if (status->co2_alert > max_level) max_level = status->co2_alert;
    if (status->tvoc_alert > max_level) max_level = status->tvoc_alert;
    if (status->pressure_alert > max_level) max_level = status->pressure_alert;

    if (max_level == ALERT_LEVEL_NONE) {
        ctx->flashing = false;
        ctx->flash_count = 0;
        return;
    }

    // 启用闪烁
    ctx->flashing = true;
    ctx->flash_count++;

    // 停止条件：闪烁10次后停止
    if (ctx->flash_count >= 20) {
        ctx->flashing = false;
        ctx->flash_count = 0;
    }
}

/*
 * 统计函数
 */

float chart_get_temp_average(chart_display_context_t *ctx)
{
    if (!ctx || ctx->buffer.count == 0) return 0.0f;

    int32_t sum = 0;
    uint16_t count = chart_buffer_count(&ctx->buffer);

    for (uint16_t i = 0; i < count; i++) {
        const chart_data_point_t *point = chart_buffer_get(&ctx->buffer, i);
        if (point) {
            sum += point->temp;
        }
    }

    return (float)sum / count;
}

float chart_get_humidity_average(chart_display_context_t *ctx)
{
    if (!ctx || ctx->buffer.count == 0) return 0.0f;

    uint32_t sum = 0;
    uint16_t count = chart_buffer_count(&ctx->buffer);

    for (uint16_t i = 0; i < count; i++) {
        const chart_data_point_t *point = chart_buffer_get(&ctx->buffer, i);
        if (point) {
            sum += point->humidity;
        }
    }

    return (float)sum / count;
}

int16_t chart_get_temp_max(chart_display_context_t *ctx)
{
    if (!ctx || ctx->buffer.count == 0) return 0;

    int16_t max = -100;
    uint16_t count = chart_buffer_count(&ctx->buffer);

    for (uint16_t i = 0; i < count; i++) {
        const chart_data_point_t *point = chart_buffer_get(&ctx->buffer, i);
        if (point && point->temp > max) {
            max = point->temp;
        }
    }

    return max;
}

int16_t chart_get_temp_min(chart_display_context_t *ctx)
{
    if (!ctx || ctx->buffer.count == 0) return 0;

    int16_t min = 100;
    uint16_t count = chart_buffer_count(&ctx->buffer);

    for (uint16_t i = 0; i < count; i++) {
        const chart_data_point_t *point = chart_buffer_get(&ctx->buffer, i);
        if (point && point->temp < min) {
            min = point->temp;
        }
    }

    return min;
}
