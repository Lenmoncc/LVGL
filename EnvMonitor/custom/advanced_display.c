/*
 * 高级显示集成模块
 * 将曲线显示、告警机制和资源优化整合到天气界面
 */

#include "custom.h"
#include "chart_display.h"
#include "resource_optimizer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// 全局上下文
static chart_display_context_t *g_chart_ctx = NULL;
static lv_timer_t *g_flash_timer = NULL;
static resource_stats_t g_resource_stats = {0};

/*
 * 告警颜色闪烁回调
 */
static void flash_alert_timer_cb(lv_timer_t *timer)
{
    if (!g_chart_ctx) return;

    alert_status_t *status = &g_chart_ctx->alert_status;

    // 检查当前告警级别
    alert_level_t max_level = ALERT_LEVEL_NONE;
    if (status->temp_alert > max_level) max_level = status->temp_alert;
    if (status->humidity_alert > max_level) max_level = status->humidity_alert;
    if (status->co2_alert > max_level) max_level = status->co2_alert;
    if (status->tvoc_alert > max_level) max_level = status->tvoc_alert;
    if (status->pressure_alert > max_level) max_level = status->pressure_alert;

    if (max_level == ALERT_LEVEL_NONE) {
        return;  // 无告警
    }

    extern lv_ui guider_ui;

    // 根据告警级别选择颜色和闪烁
    if (max_level == ALERT_LEVEL_CRITICAL) {
        // 严重告警：红色快速闪烁
        static bool red_flash = true;
        if (guider_ui.screen_weather) {
            lv_color_t color = red_flash ? lv_color_hex(0xFF0000) : lv_color_hex(0xFFFFFF);
            lv_obj_set_style_bg_color(guider_ui.screen_weather, color, LV_PART_MAIN | LV_STATE_DEFAULT);
            red_flash = !red_flash;
        }
    } else if (max_level == ALERT_LEVEL_WARNING) {
        // 警告：黄色缓慢闪烁
        static uint8_t yellow_count = 0;
        yellow_count++;
        if (yellow_count % 2 == 0 && guider_ui.screen_weather) {
            lv_color_t color = (yellow_count / 2) % 2 ? lv_color_hex(0xFFFF00) : lv_color_hex(0xFFFFFF);
            lv_obj_set_style_bg_color(guider_ui.screen_weather, color, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }

    // 调用显示模块的闪烁函数
    chart_display_flash_alert(g_chart_ctx);
}

/*
 * 初始化曲线显示和告警系统
 */
void advanced_display_init(lv_ui *ui)
{
    if (!ui || !ui->screen_weather) {
        fprintf(stderr, "[ERROR] Cannot initialize advanced display\n");
        return;
    }

    // 创建图表上下文
    g_chart_ctx = chart_display_create(ui->screen_weather);
    if (!g_chart_ctx) {
        fprintf(stderr, "[ERROR] Failed to create chart context\n");
        return;
    }

    // 设置自定义告警阈值（如果需要）
    alert_config_t custom_config = {
        // 温度: 20-28°C正常，10-35°C警告，5-40°C严重
        .temp_warning_min = 10,
        .temp_warning_max = 35,
        .temp_critical_min = 5,
        .temp_critical_max = 40,

        // 湿度: 30-70%正常，20-80%警告，10-90%严重
        .humidity_warning_min = 20,
        .humidity_warning_max = 80,
        .humidity_critical_min = 10,
        .humidity_critical_max = 90,

        // CO2: 800ppm警告，1200ppm严重
        .co2_warning = 800,
        .co2_critical = 1200,

        // TVOC: 260ppb警告，660ppb严重
        .tvoc_warning = 260,
        .tvoc_critical = 660,

        // 气压: 950-1070hPa警告，920-1100hPa严重
        .press_warning_min = 950,
        .press_warning_max = 1070,
        .press_critical_min = 920,
        .press_critical_max = 1100
    };

    chart_set_alert_config(g_chart_ctx, &custom_config);

    // 创建闪烁定时器（100ms周期）
    g_flash_timer = lv_timer_create(flash_alert_timer_cb, 100, NULL);
    if (!g_flash_timer) {
        fprintf(stderr, "[ERROR] Failed to create flash timer\n");
    }

    fprintf(stdout, "[OK] Advanced display initialized\n");

    // 初始化资源优化
    resource_optimize_all();
}

/*
 * 更新显示和告警
 */
void advanced_display_update(const sensor_data_t *data)
{
    if (!g_chart_ctx || !data) return;

    // 更新图表数据
    chart_display_update(g_chart_ctx, data);

    // 绘制曲线（如果需要）
    chart_display_draw(g_chart_ctx);

    // 获取告警状态用于调试
    const alert_status_t *status = chart_get_alert_status(g_chart_ctx);
    if (status && status->temp_alert != ALERT_LEVEL_NONE) {
        fprintf(stdout, "[ALERT] Temperature alert level: %d\n", status->temp_alert);
    }
}

/*
 * 获取数据统计
 */
float advanced_display_get_temp_average(void)
{
    if (!g_chart_ctx) return 0.0f;
    return chart_get_temp_average(g_chart_ctx);
}

float advanced_display_get_humidity_average(void)
{
    if (!g_chart_ctx) return 0.0f;
    return chart_get_humidity_average(g_chart_ctx);
}

int16_t advanced_display_get_temp_max(void)
{
    if (!g_chart_ctx) return 0;
    return chart_get_temp_max(g_chart_ctx);
}

int16_t advanced_display_get_temp_min(void)
{
    if (!g_chart_ctx) return 0;
    return chart_get_temp_min(g_chart_ctx);
}

/*
 * 清理资源
 */
void advanced_display_cleanup(void)
{
    if (g_flash_timer) {
        lv_timer_del(g_flash_timer);
        g_flash_timer = NULL;
    }

    if (g_chart_ctx) {
        chart_display_destroy(g_chart_ctx);
        g_chart_ctx = NULL;
    }

    fprintf(stdout, "[OK] Advanced display cleaned up\n");
}

/*
 * 打印性能统计
 */
void advanced_display_print_stats(void)
{
    if (!g_chart_ctx) {
        fprintf(stdout, "[INFO] Chart context not initialized\n");
        return;
    }

    fprintf(stdout, "\n═══════════════════════════════════════════════\n");
    fprintf(stdout, "       高级显示模块统计信息\n");
    fprintf(stdout, "═══════════════════════════════════════════════\n\n");

    // 曲线数据统计
    uint16_t data_points = chart_buffer_count(&g_chart_ctx->buffer);
    fprintf(stdout, "曲线数据统计：\n");
    fprintf(stdout, "  当前数据点数:     %u (容量: %u)\n", data_points, CHART_DATA_CAPACITY);
    fprintf(stdout, "  缓冲区占用率:     %.1f %%\n", (data_points * 100.0f) / CHART_DATA_CAPACITY);

    // 温度统计
    fprintf(stdout, "\n温度统计 (°C)：\n");
    fprintf(stdout, "  平均值:           %.1f\n", chart_get_temp_average(g_chart_ctx));
    fprintf(stdout, "  最高值:           %d\n", chart_get_temp_max(g_chart_ctx));
    fprintf(stdout, "  最低值:           %d\n", chart_get_temp_min(g_chart_ctx));

    // 湿度统计
    fprintf(stdout, "\n湿度统计 (%%)：\n");
    fprintf(stdout, "  平均值:           %.1f\n", chart_get_humidity_average(g_chart_ctx));

    // 告警统计
    alert_status_t *status = &g_chart_ctx->alert_status;
    fprintf(stdout, "\n告警统计：\n");
    fprintf(stdout, "  温度告警:         %s\n", status->temp_alert == ALERT_LEVEL_NONE ? "无" :
                                                  status->temp_alert == ALERT_LEVEL_WARNING ? "警告" : "严重");
    fprintf(stdout, "  湿度告警:         %s\n", status->humidity_alert == ALERT_LEVEL_NONE ? "无" :
                                                  status->humidity_alert == ALERT_LEVEL_WARNING ? "警告" : "严重");
    fprintf(stdout, "  CO2告警:          %s\n", status->co2_alert == ALERT_LEVEL_NONE ? "无" :
                                                  status->co2_alert == ALERT_LEVEL_WARNING ? "警告" : "严重");
    fprintf(stdout, "  TVOC告警:         %s\n", status->tvoc_alert == ALERT_LEVEL_NONE ? "无" :
                                                  status->tvoc_alert == ALERT_LEVEL_WARNING ? "警告" : "严重");
    fprintf(stdout, "  气压告警:         %s\n", status->pressure_alert == ALERT_LEVEL_NONE ? "无" :
                                                  status->pressure_alert == ALERT_LEVEL_WARNING ? "警告" : "严重");
    fprintf(stdout, "  总告警次数:       %u\n", status->alert_count);

    // 资源统计
    fprintf(stdout, "\n");
    resource_stats_print(&g_resource_stats);

    fprintf(stdout, "═══════════════════════════════════════════════\n\n");
}
