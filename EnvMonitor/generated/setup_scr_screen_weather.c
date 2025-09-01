/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_screen_weather(lv_ui *ui)
{
    //Write codes screen_weather
    ui->screen_weather = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_weather, 800, 480);
    lv_obj_set_scrollbar_mode(ui->screen_weather, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_weather, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_weather, 222, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_weather, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_weather, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_img_1
    ui->screen_weather_img_1 = lv_image_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_img_1, 0, 0);
    lv_obj_set_size(ui->screen_weather_img_1, 800, 480);
    lv_obj_add_flag(ui->screen_weather_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_weather_img_1, &_17_RGB565A8_800x480);
    lv_image_set_pivot(ui->screen_weather_img_1, 50,50);
    lv_image_set_rotation(ui->screen_weather_img_1, 0);

    //Write style for screen_weather_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_weather_img_1, 83, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_recolor(ui->screen_weather_img_1, lv_color_hex(0x65c6ff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_weather_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_img_8
    ui->screen_weather_img_8 = lv_image_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_img_8, 51, 67);
    lv_obj_set_size(ui->screen_weather_img_8, 193, 195);
    lv_obj_add_flag(ui->screen_weather_img_8, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_weather_img_8, &_24_RGB565A8_193x195_tresh);
    lv_image_set_pivot(ui->screen_weather_img_8, 50,50);
    lv_image_set_rotation(ui->screen_weather_img_8, 0);

    //Write style for screen_weather_img_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_weather_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_weather_img_8, 158, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_img_9
    ui->screen_weather_img_9 = lv_image_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_img_9, 300, 67);
    lv_obj_set_size(ui->screen_weather_img_9, 193, 195);
    lv_obj_add_flag(ui->screen_weather_img_9, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_weather_img_9, &_24_RGB565A8_193x195_tresh);
    lv_image_set_pivot(ui->screen_weather_img_9, 50,50);
    lv_image_set_rotation(ui->screen_weather_img_9, 0);

    //Write style for screen_weather_img_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_weather_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_weather_img_9, 158, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_img_10
    ui->screen_weather_img_10 = lv_image_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_img_10, 51, 279);
    lv_obj_set_size(ui->screen_weather_img_10, 313, 195);
    lv_obj_add_flag(ui->screen_weather_img_10, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_weather_img_10, &_24_RGB565A8_313x195_tresh);
    lv_image_set_pivot(ui->screen_weather_img_10, 50,50);
    lv_image_set_rotation(ui->screen_weather_img_10, 0);

    //Write style for screen_weather_img_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_weather_img_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_weather_img_10, 158, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_img_11
    ui->screen_weather_img_11 = lv_image_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_img_11, 549, 67);
    lv_obj_set_size(ui->screen_weather_img_11, 193, 195);
    lv_obj_add_flag(ui->screen_weather_img_11, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_weather_img_11, &_24_RGB565A8_193x195_tresh);
    lv_image_set_pivot(ui->screen_weather_img_11, 50,50);
    lv_image_set_rotation(ui->screen_weather_img_11, 0);

    //Write style for screen_weather_img_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_weather_img_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_weather_img_11, 158, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_img_12
    ui->screen_weather_img_12 = lv_image_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_img_12, 431, 279);
    lv_obj_set_size(ui->screen_weather_img_12, 313, 195);
    lv_obj_add_flag(ui->screen_weather_img_12, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_weather_img_12, &_24_RGB565A8_313x195_tresh);
    lv_image_set_pivot(ui->screen_weather_img_12, 50,50);
    lv_image_set_rotation(ui->screen_weather_img_12, 0);

    //Write style for screen_weather_img_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_weather_img_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_weather_img_12, 158, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_img_3
    ui->screen_weather_img_3 = lv_image_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_img_3, 196, 84);
    lv_obj_set_size(ui->screen_weather_img_3, 30, 30);
    lv_obj_add_flag(ui->screen_weather_img_3, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_weather_img_3, &_19_RGB565A8_30x30);
    lv_image_set_pivot(ui->screen_weather_img_3, 50,50);
    lv_image_set_rotation(ui->screen_weather_img_3, 0);

    //Write style for screen_weather_img_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_weather_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_weather_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_img_2
    ui->screen_weather_img_2 = lv_image_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_img_2, 442, 84);
    lv_obj_set_size(ui->screen_weather_img_2, 30, 30);
    lv_obj_add_flag(ui->screen_weather_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_weather_img_2, &_18_RGB565A8_30x30);
    lv_image_set_pivot(ui->screen_weather_img_2, 50,50);
    lv_image_set_rotation(ui->screen_weather_img_2, 0);

    //Write style for screen_weather_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_weather_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_weather_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_img_4
    ui->screen_weather_img_4 = lv_image_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_img_4, 258, 322);
    lv_obj_set_size(ui->screen_weather_img_4, 70, 78);
    lv_obj_add_flag(ui->screen_weather_img_4, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_weather_img_4, &_20_RGB565A8_70x78);
    lv_image_set_pivot(ui->screen_weather_img_4, 50,50);
    lv_image_set_rotation(ui->screen_weather_img_4, 0);

    //Write style for screen_weather_img_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_weather_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_weather_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_img_5
    ui->screen_weather_img_5 = lv_image_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_img_5, 77, 322);
    lv_obj_set_size(ui->screen_weather_img_5, 128, 80);
    lv_obj_add_flag(ui->screen_weather_img_5, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_weather_img_5, &_21_RGB565A8_128x80);
    lv_image_set_pivot(ui->screen_weather_img_5, 50,50);
    lv_image_set_rotation(ui->screen_weather_img_5, 0);

    //Write style for screen_weather_img_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_weather_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_weather_img_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_img_6
    ui->screen_weather_img_6 = lv_image_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_img_6, 688, 84);
    lv_obj_set_size(ui->screen_weather_img_6, 30, 30);
    lv_obj_add_flag(ui->screen_weather_img_6, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_weather_img_6, &_22_RGB565A8_30x30);
    lv_image_set_pivot(ui->screen_weather_img_6, 50,50);
    lv_image_set_rotation(ui->screen_weather_img_6, 0);

    //Write style for screen_weather_img_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_weather_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_weather_img_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_btn_1
    ui->screen_weather_btn_1 = lv_button_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_btn_1, 8, 7);
    lv_obj_set_size(ui->screen_weather_btn_1, 69, 35);
    ui->screen_weather_btn_1_label = lv_label_create(ui->screen_weather_btn_1);
    lv_label_set_text(ui->screen_weather_btn_1_label, "BACK");
    lv_label_set_long_mode(ui->screen_weather_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_weather_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_weather_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_weather_btn_1_label, LV_PCT(100));

    //Write style for screen_weather_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_weather_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_weather_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_btn_1, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_btn_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_weather_btn_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_weather_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_weather_btn_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_weather_btn_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_weather_btn_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_btn_1, lv_color_hex(0x191717), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_btn_1, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_1
    ui->screen_weather_label_1 = lv_label_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_label_1, 41, 89);
    lv_obj_set_size(ui->screen_weather_label_1, 100, 32);
    lv_label_set_text(ui->screen_weather_label_1, "Hum");
    lv_label_set_long_mode(ui->screen_weather_label_1, LV_LABEL_LONG_WRAP);

    //Write style for screen_weather_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_1, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_2
    ui->screen_weather_label_2 = lv_label_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_label_2, 288, 89);
    lv_obj_set_size(ui->screen_weather_label_2, 100, 32);
    lv_label_set_text(ui->screen_weather_label_2, "Feel");
    lv_label_set_long_mode(ui->screen_weather_label_2, LV_LABEL_LONG_WRAP);

    //Write style for screen_weather_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_2, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_3
    ui->screen_weather_label_3 = lv_label_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_label_3, 549, 89);
    lv_obj_set_size(ui->screen_weather_label_3, 100, 32);
    lv_label_set_text(ui->screen_weather_label_3, "Light");
    lv_label_set_long_mode(ui->screen_weather_label_3, LV_LABEL_LONG_WRAP);

    //Write style for screen_weather_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_3, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_4
    ui->screen_weather_label_4 = lv_label_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_label_4, 450, 295);
    lv_obj_set_size(ui->screen_weather_label_4, 100, 32);
    lv_label_set_text(ui->screen_weather_label_4, "SGP30");
    lv_label_set_long_mode(ui->screen_weather_label_4, LV_LABEL_LONG_WRAP);

    //Write style for screen_weather_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_4, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_5
    ui->screen_weather_label_5 = lv_label_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_label_5, 311, 13);
    lv_obj_set_size(ui->screen_weather_label_5, 177, 32);
    lv_label_set_text(ui->screen_weather_label_5, "SENSOT DATA");
    lv_label_set_long_mode(ui->screen_weather_label_5, LV_LABEL_LONG_WRAP);

    //Write style for screen_weather_label_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_5, &lv_font_montserratMedium_21, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_6
    ui->screen_weather_label_6 = lv_label_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_label_6, 450, 344);
    lv_obj_set_size(ui->screen_weather_label_6, 100, 32);
    lv_label_set_text(ui->screen_weather_label_6, "TVOC");
    lv_label_set_long_mode(ui->screen_weather_label_6, LV_LABEL_LONG_WRAP);

    //Write style for screen_weather_label_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_6, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_6, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_7
    ui->screen_weather_label_7 = lv_label_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_label_7, 450, 409);
    lv_obj_set_size(ui->screen_weather_label_7, 100, 32);
    lv_label_set_text(ui->screen_weather_label_7, "eCO2");
    lv_label_set_long_mode(ui->screen_weather_label_7, LV_LABEL_LONG_WRAP);

    //Write style for screen_weather_label_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_7, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_7, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_8
    ui->screen_weather_label_8 = lv_label_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_label_8, 58, 295);
    lv_obj_set_size(ui->screen_weather_label_8, 100, 32);
    lv_label_set_text(ui->screen_weather_label_8, "Pres/Atl");
    lv_label_set_long_mode(ui->screen_weather_label_8, LV_LABEL_LONG_WRAP);

    //Write style for screen_weather_label_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_8, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_9
    ui->screen_weather_label_9 = lv_label_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_label_9, 94, 425);
    lv_obj_set_size(ui->screen_weather_label_9, 100, 32);
    lv_label_set_text(ui->screen_weather_label_9, "886hPa");
    lv_label_set_long_mode(ui->screen_weather_label_9, LV_LABEL_LONG_WRAP);

    //Write style for screen_weather_label_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_9, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_9, &lv_font_montserratMedium_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_img_13
    ui->screen_weather_img_13 = lv_image_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_img_13, 304, 288);
    lv_obj_set_size(ui->screen_weather_img_13, 30, 30);
    lv_obj_add_flag(ui->screen_weather_img_13, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_weather_img_13, &_25_RGB565A8_30x30);
    lv_image_set_pivot(ui->screen_weather_img_13, 50,50);
    lv_image_set_rotation(ui->screen_weather_img_13, 0);

    //Write style for screen_weather_img_13, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_weather_img_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_weather_img_13, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_img_14
    ui->screen_weather_img_14 = lv_image_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_img_14, 311, 145);
    lv_obj_set_size(ui->screen_weather_img_14, 178, 34);
    lv_obj_add_flag(ui->screen_weather_img_14, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_weather_img_14, &_26_RGB565A8_178x34);
    lv_image_set_pivot(ui->screen_weather_img_14, 50,50);
    lv_image_set_rotation(ui->screen_weather_img_14, 0);

    //Write style for screen_weather_img_14, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_weather_img_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_weather_img_14, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_10
    ui->screen_weather_label_10 = lv_label_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_label_10, 396, 214);
    lv_obj_set_size(ui->screen_weather_label_10, 100, 32);
    lv_label_set_text(ui->screen_weather_label_10, "Comf");
    lv_label_set_long_mode(ui->screen_weather_label_10, LV_LABEL_LONG_WRAP);

    //Write style for screen_weather_label_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_10, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_10, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_10, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_11
    ui->screen_weather_label_11 = lv_label_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_label_11, 306, 206);
    lv_obj_set_size(ui->screen_weather_label_11, 100, 32);
    lv_label_set_text(ui->screen_weather_label_11, "21 C");
    lv_label_set_long_mode(ui->screen_weather_label_11, LV_LABEL_LONG_WRAP);

    //Write style for screen_weather_label_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_11, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_11, &lv_font_montserratMedium_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_11, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_12
    ui->screen_weather_label_12 = lv_label_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_label_12, 561, 206);
    lv_obj_set_size(ui->screen_weather_label_12, 100, 32);
    lv_label_set_text(ui->screen_weather_label_12, "1013lx");
    lv_label_set_long_mode(ui->screen_weather_label_12, LV_LABEL_LONG_WRAP);

    //Write style for screen_weather_label_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_12, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_12, &lv_font_montserratMedium_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_12, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_13
    ui->screen_weather_label_13 = lv_label_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_label_13, 549, 330);
    lv_obj_set_size(ui->screen_weather_label_13, 110, 51);
    lv_label_set_text(ui->screen_weather_label_13, "250");
    lv_label_set_long_mode(ui->screen_weather_label_13, LV_LABEL_LONG_WRAP);

    //Write style for screen_weather_label_13, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_13, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_13, &lv_font_montserratMedium_40, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_13, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_13, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_img_15
    ui->screen_weather_img_15 = lv_image_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_img_15, 676, 284);
    lv_obj_set_size(ui->screen_weather_img_15, 30, 30);
    lv_obj_add_flag(ui->screen_weather_img_15, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_weather_img_15, &_27_RGB565A8_30x30);
    lv_image_set_pivot(ui->screen_weather_img_15, 50,50);
    lv_image_set_rotation(ui->screen_weather_img_15, 0);

    //Write style for screen_weather_img_15, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_weather_img_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_weather_img_15, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_14
    ui->screen_weather_label_14 = lv_label_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_label_14, 553, 395);
    lv_obj_set_size(ui->screen_weather_label_14, 105, 60);
    lv_label_set_text(ui->screen_weather_label_14, "996");
    lv_label_set_long_mode(ui->screen_weather_label_14, LV_LABEL_LONG_WRAP);

    //Write style for screen_weather_label_14, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_14, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_14, &lv_font_montserratMedium_40, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_14, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_14, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_15
    ui->screen_weather_label_15 = lv_label_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_label_15, 247, 425);
    lv_obj_set_size(ui->screen_weather_label_15, 100, 32);
    lv_label_set_text(ui->screen_weather_label_15, "1013m");
    lv_label_set_long_mode(ui->screen_weather_label_15, LV_LABEL_LONG_WRAP);

    //Write style for screen_weather_label_15, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_15, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_15, &lv_font_montserratMedium_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_15, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_15, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_img_16
    ui->screen_weather_img_16 = lv_image_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_img_16, 567, 123);
    lv_obj_set_size(ui->screen_weather_img_16, 151, 71);
    lv_obj_add_flag(ui->screen_weather_img_16, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_weather_img_16, &_28_RGB565A8_151x71);
    lv_image_set_pivot(ui->screen_weather_img_16, 50,50);
    lv_image_set_rotation(ui->screen_weather_img_16, 0);

    //Write style for screen_weather_img_16, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_weather_img_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_weather_img_16, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_16
    ui->screen_weather_label_16 = lv_label_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_label_16, 661, 214);
    lv_obj_set_size(ui->screen_weather_label_16, 100, 32);
    lv_label_set_text(ui->screen_weather_label_16, "Good");
    lv_label_set_long_mode(ui->screen_weather_label_16, LV_LABEL_LONG_WRAP);

    //Write style for screen_weather_label_16, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_16, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_16, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_16, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_16, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_17
    ui->screen_weather_label_17 = lv_label_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_label_17, 51, 206);
    lv_obj_set_size(ui->screen_weather_label_17, 100, 40);
    lv_label_set_text(ui->screen_weather_label_17, "86%");
    lv_label_set_long_mode(ui->screen_weather_label_17, LV_LABEL_LONG_WRAP);

    //Write style for screen_weather_label_17, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_17, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_17, &lv_font_montserratMedium_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_17, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_17, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_18
    ui->screen_weather_label_18 = lv_label_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_label_18, 151, 214);
    lv_obj_set_size(ui->screen_weather_label_18, 100, 43);
    lv_label_set_text(ui->screen_weather_label_18, "Wet");
    lv_label_set_long_mode(ui->screen_weather_label_18, LV_LABEL_LONG_WRAP);

    //Write style for screen_weather_label_18, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_18, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_18, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_18, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_18, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_19
    ui->screen_weather_label_19 = lv_label_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_label_19, 682, 14);
    lv_obj_set_size(ui->screen_weather_label_19, 100, 32);
    lv_label_set_text(ui->screen_weather_label_19, "10:30");
    lv_label_set_long_mode(ui->screen_weather_label_19, LV_LABEL_LONG_WRAP);

    //Write style for screen_weather_label_19, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_19, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_19, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_19, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_19, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_slider_1
    ui->screen_weather_slider_1 = lv_slider_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_slider_1, 68, 157);
    lv_obj_set_size(ui->screen_weather_slider_1, 160, 8);
    lv_slider_set_range(ui->screen_weather_slider_1, 0, 100);
    lv_slider_set_mode(ui->screen_weather_slider_1, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui->screen_weather_slider_1, 50, LV_ANIM_OFF);

    //Write style for screen_weather_slider_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_weather_slider_1, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_weather_slider_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_weather_slider_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_slider_1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->screen_weather_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_weather_slider_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_weather_slider_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_weather_slider_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_weather_slider_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_slider_1, 8, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for screen_weather_slider_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_weather_slider_1, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_weather_slider_1, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_weather_slider_1, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_slider_1, 8, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_20
    ui->screen_weather_label_20 = lv_label_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_label_20, 630, 344);
    lv_obj_set_size(ui->screen_weather_label_20, 100, 32);
    lv_label_set_text(ui->screen_weather_label_20, "ppb");
    lv_label_set_long_mode(ui->screen_weather_label_20, LV_LABEL_LONG_WRAP);

    //Write style for screen_weather_label_20, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_20, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_20, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_20, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_20, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_21
    ui->screen_weather_label_21 = lv_label_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_label_21, 635, 409);
    lv_obj_set_size(ui->screen_weather_label_21, 100, 32);
    lv_label_set_text(ui->screen_weather_label_21, "ppm");
    lv_label_set_long_mode(ui->screen_weather_label_21, LV_LABEL_LONG_WRAP);

    //Write style for screen_weather_label_21, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_21, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_21, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_21, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_21, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_weather.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_weather);

    //Init events for screen.
    events_init_screen_weather(ui);
}
