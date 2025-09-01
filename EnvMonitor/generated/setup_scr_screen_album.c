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



void setup_scr_screen_album(lv_ui *ui)
{
    //Write codes screen_album
    ui->screen_album = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_album, 800, 480);
    lv_obj_set_scrollbar_mode(ui->screen_album, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_album, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_album, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_album_tileview_1
    ui->screen_album_tileview_1 = lv_tileview_create(ui->screen_album);
    lv_obj_set_pos(ui->screen_album_tileview_1, 0, 0);
    lv_obj_set_size(ui->screen_album_tileview_1, 800, 480);
    lv_obj_set_scrollbar_mode(ui->screen_album_tileview_1, LV_SCROLLBAR_MODE_OFF);
    ui->screen_album_tileview_1_img1 = lv_tileview_add_tile(ui->screen_album_tileview_1, 0, 0, LV_DIR_RIGHT);
    ui->screen_album_tileview_1_img3 = lv_tileview_add_tile(ui->screen_album_tileview_1, 1, 0, LV_DIR_LEFT | LV_DIR_RIGHT);
    ui->screen_album_tileview_1_img4 = lv_tileview_add_tile(ui->screen_album_tileview_1, 2, 0, LV_DIR_LEFT | LV_DIR_RIGHT);
    ui->screen_album_tileview_1_img5 = lv_tileview_add_tile(ui->screen_album_tileview_1, 3, 0, LV_DIR_LEFT | LV_DIR_RIGHT);
    ui->screen_album_tileview_1_img2 = lv_tileview_add_tile(ui->screen_album_tileview_1, 4, 0, LV_DIR_LEFT);

    //Write style for screen_album_tileview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_album_tileview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_album_tileview_1, lv_color_hex(0xf6f6f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_album_tileview_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_album_tileview_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_album_tileview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_album_tileview_1, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_album_tileview_1, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_album_tileview_1, lv_color_hex(0xeaeff3), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_album_tileview_1, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_album_tileview_1, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);



    //Write codes screen_album_img_1
    ui->screen_album_img_1 = lv_image_create(ui->screen_album_tileview_1_img1);
    lv_obj_set_pos(ui->screen_album_img_1, 0, 0);
    lv_obj_set_size(ui->screen_album_img_1, 800, 480);
    lv_obj_add_flag(ui->screen_album_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_album_img_1, &_5_RGB565A8_800x480);
    lv_image_set_pivot(ui->screen_album_img_1, 50,50);
    lv_image_set_rotation(ui->screen_album_img_1, 0);

    //Write style for screen_album_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_album_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_album_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);



    //Write codes screen_album_img_3
    ui->screen_album_img_3 = lv_image_create(ui->screen_album_tileview_1_img3);
    lv_obj_set_pos(ui->screen_album_img_3, 0, 0);
    lv_obj_set_size(ui->screen_album_img_3, 800, 480);
    lv_obj_add_flag(ui->screen_album_img_3, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_album_img_3, &_4_RGB565A8_800x480_tresh);
    lv_image_set_pivot(ui->screen_album_img_3, 50,50);
    lv_image_set_rotation(ui->screen_album_img_3, 0);

    //Write style for screen_album_img_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_album_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_album_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);



    //Write codes screen_album_img_4
    ui->screen_album_img_4 = lv_image_create(ui->screen_album_tileview_1_img4);
    lv_obj_set_pos(ui->screen_album_img_4, 0, 0);
    lv_obj_set_size(ui->screen_album_img_4, 800, 480);
    lv_obj_add_flag(ui->screen_album_img_4, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_album_img_4, &_3_RGB565A8_800x480_tresh);
    lv_image_set_pivot(ui->screen_album_img_4, 50,50);
    lv_image_set_rotation(ui->screen_album_img_4, 0);

    //Write style for screen_album_img_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_album_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_album_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);



    //Write codes screen_album_img_5
    ui->screen_album_img_5 = lv_image_create(ui->screen_album_tileview_1_img5);
    lv_obj_set_pos(ui->screen_album_img_5, 0, 0);
    lv_obj_set_size(ui->screen_album_img_5, 800, 480);
    lv_obj_add_flag(ui->screen_album_img_5, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_album_img_5, &_1_RGB565A8_800x480_tresh);
    lv_image_set_pivot(ui->screen_album_img_5, 50,50);
    lv_image_set_rotation(ui->screen_album_img_5, 0);

    //Write style for screen_album_img_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_album_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_album_img_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);



    //Write codes screen_album_img_2
    ui->screen_album_img_2 = lv_image_create(ui->screen_album_tileview_1_img2);
    lv_obj_set_pos(ui->screen_album_img_2, 0, 0);
    lv_obj_set_size(ui->screen_album_img_2, 800, 480);
    lv_obj_add_flag(ui->screen_album_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_album_img_2, &_2_RGB565A8_800x480_tresh);
    lv_image_set_pivot(ui->screen_album_img_2, 50,50);
    lv_image_set_rotation(ui->screen_album_img_2, 0);

    //Write style for screen_album_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_album_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_album_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_album_btn_1
    ui->screen_album_btn_1 = lv_button_create(ui->screen_album);
    lv_obj_set_pos(ui->screen_album_btn_1, 4, 5);
    lv_obj_set_size(ui->screen_album_btn_1, 71, 36);
    ui->screen_album_btn_1_label = lv_label_create(ui->screen_album_btn_1);
    lv_label_set_text(ui->screen_album_btn_1_label, "BACK");
    lv_label_set_long_mode(ui->screen_album_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_album_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_album_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_album_btn_1_label, LV_PCT(100));

    //Write style for screen_album_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_album_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_album_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_album_btn_1, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_album_btn_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_album_btn_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_album_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_album_btn_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_album_btn_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_album_btn_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_album_btn_1, lv_color_hex(0x191717), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_album_btn_1, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_album_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_album_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_album.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_album);

    //Init events for screen.
    events_init_screen_album(ui);
}
