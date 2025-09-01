/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"


typedef struct
{
  
	lv_obj_t *screen;
	bool screen_del;
	lv_obj_t *screen_background;
	lv_obj_t *screen_img_1;
	lv_obj_t *screen_img_2;
	lv_obj_t *screen_img_3;
	lv_obj_t *screen_img_4;
	lv_obj_t *screen_img_5;
	lv_obj_t *screen_label_1;
	lv_obj_t *screen_label_2;
	lv_obj_t *screen_label_3;
	lv_obj_t *screen_label_4;
	lv_obj_t *screen_img_6;
	lv_obj_t *screen_label_5;
	lv_obj_t *screen_label_6;
	lv_obj_t *screen_img_7;
	lv_obj_t *screen_img_8;
	lv_obj_t *screen_label_7;
	lv_obj_t *screen_label_8;
	lv_obj_t *screen_album;
	bool screen_album_del;
	lv_obj_t *screen_album_tileview_1;
	lv_obj_t *screen_album_tileview_1_img1;
	lv_obj_t *screen_album_tileview_1_img3;
	lv_obj_t *screen_album_tileview_1_img4;
	lv_obj_t *screen_album_tileview_1_img5;
	lv_obj_t *screen_album_tileview_1_img2;
	lv_obj_t *screen_album_img_1;
	lv_obj_t *screen_album_img_3;
	lv_obj_t *screen_album_img_4;
	lv_obj_t *screen_album_img_5;
	lv_obj_t *screen_album_img_2;
	lv_obj_t *screen_album_btn_1;
	lv_obj_t *screen_album_btn_1_label;
	lv_obj_t *screen_weather;
	bool screen_weather_del;
	lv_obj_t *screen_weather_img_1;
	lv_obj_t *screen_weather_img_8;
	lv_obj_t *screen_weather_img_9;
	lv_obj_t *screen_weather_img_10;
	lv_obj_t *screen_weather_img_11;
	lv_obj_t *screen_weather_img_12;
	lv_obj_t *screen_weather_img_3;
	lv_obj_t *screen_weather_img_2;
	lv_obj_t *screen_weather_img_4;
	lv_obj_t *screen_weather_img_5;
	lv_obj_t *screen_weather_img_6;
	lv_obj_t *screen_weather_btn_1;
	lv_obj_t *screen_weather_btn_1_label;
	lv_obj_t *screen_weather_label_1;
	lv_obj_t *screen_weather_label_2;
	lv_obj_t *screen_weather_label_3;
	lv_obj_t *screen_weather_label_4;
	lv_obj_t *screen_weather_label_5;
	lv_obj_t *screen_weather_label_6;
	lv_obj_t *screen_weather_label_7;
	lv_obj_t *screen_weather_label_8;
	lv_obj_t *screen_weather_label_9;
	lv_obj_t *screen_weather_img_13;
	lv_obj_t *screen_weather_img_14;
	lv_obj_t *screen_weather_label_10;
	lv_obj_t *screen_weather_label_11;
	lv_obj_t *screen_weather_label_12;
	lv_obj_t *screen_weather_label_13;
	lv_obj_t *screen_weather_img_15;
	lv_obj_t *screen_weather_label_14;
	lv_obj_t *screen_weather_label_15;
	lv_obj_t *screen_weather_img_16;
	lv_obj_t *screen_weather_label_16;
	lv_obj_t *screen_weather_label_17;
	lv_obj_t *screen_weather_label_18;
	lv_obj_t *screen_weather_label_19;
	lv_obj_t *screen_weather_slider_1;
	lv_obj_t *screen_weather_label_20;
	lv_obj_t *screen_weather_label_21;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_screen_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, uint32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                  uint32_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                  lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_completed_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_bottom_layer(void);

void setup_ui(lv_ui *ui);

void video_play(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;


void setup_scr_screen(lv_ui *ui);
void setup_scr_screen_album(lv_ui *ui);
void setup_scr_screen_weather(lv_ui *ui);
LV_IMAGE_DECLARE(_5_RGB565A8_817x492_tresh);
LV_IMAGE_DECLARE(_7_RGB565A8_72x76_tresh);
LV_IMAGE_DECLARE(_8_RGB565A8_65x61_tresh);
LV_IMAGE_DECLARE(_10_RGB565A8_71x67_tresh);
LV_IMAGE_DECLARE(_11_RGB565A8_35x35);
LV_IMAGE_DECLARE(_12_RGB565A8_20x20);
LV_IMAGE_DECLARE(_13_RGB565A8_71x66);
LV_IMAGE_DECLARE(_16_RGB565A8_368x19);
LV_IMAGE_DECLARE(_15_RGB565A8_13x10);
LV_IMAGE_DECLARE(_5_RGB565A8_800x480);
LV_IMAGE_DECLARE(_4_RGB565A8_800x480_tresh);
LV_IMAGE_DECLARE(_3_RGB565A8_800x480_tresh);
LV_IMAGE_DECLARE(_1_RGB565A8_800x480_tresh);
LV_IMAGE_DECLARE(_2_RGB565A8_800x480_tresh);
LV_IMAGE_DECLARE(_17_RGB565A8_800x480);
LV_IMAGE_DECLARE(_24_RGB565A8_193x195_tresh);
LV_IMAGE_DECLARE(_24_RGB565A8_313x195_tresh);
LV_IMAGE_DECLARE(_19_RGB565A8_30x30);
LV_IMAGE_DECLARE(_18_RGB565A8_30x30);
LV_IMAGE_DECLARE(_20_RGB565A8_70x78);
LV_IMAGE_DECLARE(_21_RGB565A8_128x80);
LV_IMAGE_DECLARE(_22_RGB565A8_30x30);
LV_IMAGE_DECLARE(_25_RGB565A8_30x30);
LV_IMAGE_DECLARE(_26_RGB565A8_178x34);
LV_IMAGE_DECLARE(_27_RGB565A8_30x30);
LV_IMAGE_DECLARE(_28_RGB565A8_151x71);

LV_FONT_DECLARE(lv_font_Acme_Regular_16)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_Acme_Regular_97)
LV_FONT_DECLARE(lv_font_Acme_Regular_14)
LV_FONT_DECLARE(lv_font_Acme_Regular_24)
LV_FONT_DECLARE(lv_font_montserratMedium_18)
LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_montserratMedium_21)
LV_FONT_DECLARE(lv_font_montserratMedium_30)
LV_FONT_DECLARE(lv_font_montserratMedium_40)


#ifdef __cplusplus
}
#endif
#endif
