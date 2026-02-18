#ifndef __ADVANCED_DISPLAY_H_
#define __ADVANCED_DISPLAY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "custom.h"

/*
 * 高级显示集成模块
 * 将曲线显示、告警机制和资源优化整合到一个统一界面
 */

// 初始化和清理
void advanced_display_init(lv_ui *ui);
void advanced_display_cleanup(void);

// 数据更新
void advanced_display_update(const sensor_data_t *data);

// 数据查询
float advanced_display_get_temp_average(void);
float advanced_display_get_humidity_average(void);
int16_t advanced_display_get_temp_max(void);
int16_t advanced_display_get_temp_min(void);

// 统计和调试
void advanced_display_print_stats(void);

#ifdef __cplusplus
}
#endif
#endif /* __ADVANCED_DISPLAY_H_ */
