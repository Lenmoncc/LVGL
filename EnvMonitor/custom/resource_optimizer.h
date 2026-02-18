#ifndef __RESOURCE_OPTIMIZER_H_
#define __RESOURCE_OPTIMIZER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include <stdint.h>
#include <stddef.h>

/*
 * 资源优化模块
 * 通过字体子集化和背景图片压缩降低显存占用
 * 目标: 降低显存占用30%
 */

// 字体优化配置
typedef struct {
    const lv_font_t *original_font;     // 原始字体
    uint32_t char_set_mask;             // 字符集掩码
    uint16_t glyph_count;               // 字形数量
    size_t original_size;               // 原始大小（字节）
    size_t optimized_size;              // 优化后大小（字节）
} font_optimize_info_t;

// 背景图片信息
typedef struct {
    const lv_image_dsc_t *image;        // 图片描述符
    lv_img_cf_t color_format;           // 颜色格式
    uint16_t width, height;             // 分辨率
    size_t original_size;               // 原始大小（字节）
    size_t optimized_size;              // 优化后大小（字节）
} image_optimize_info_t;

// 资源统计信息
typedef struct {
    uint32_t total_font_size;           // 总字体大小
    uint32_t total_image_size;          // 总图片大小
    uint32_t total_optimized_size;      // 优化后总大小
    uint32_t total_saved_bytes;         // 节省字节数
    float compression_ratio;            // 压缩率 (%)
} resource_stats_t;

/*
 * 函数声明
 */

// 字体优化
font_optimize_info_t* font_optimize_analyze(const lv_font_t *font,
                                            const char *text);
void font_optimize_info_free(font_optimize_info_t *info);

// 背景图片优化
image_optimize_info_t* image_optimize_analyze(const lv_image_dsc_t *image);
void image_optimize_info_free(image_optimize_info_t *info);

// 资源统计
resource_stats_t resource_stats_collect(void);
void resource_stats_print(const resource_stats_t *stats);

// 批量优化
void resource_optimize_all(void);
float resource_get_savings_percentage(void);

#ifdef __cplusplus
}
#endif
#endif /* __RESOURCE_OPTIMIZER_H_ */
