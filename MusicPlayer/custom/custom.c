/*
* Copyright 2024 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl/lvgl.h"
#include "custom.h"
#include "spectrum_1.h"
#include "spectrum_2.h"
#include "spectrum_3.h"

/*********************
 *      DEFINES
 *********************/
#define ACTIVE_TRACK_CNT    3
#define BAR_CNT             20
#define BAND_CNT            4
#define BAR_PER_BAND_CNT    (BAR_CNT / BAND_CNT)
#define DEG_STEP            (180/BAR_CNT)
#define BAR_COLOR1_STOP     80
#define BAR_COLOR2_STOP     100
#define BAR_COLOR3_STOP     (LV_MAX(LV_HOR_RES, LV_VER_RES) / 3)
#define BAR_COLOR1          lv_color_hex(0xe9dbfc)
#define BAR_COLOR2          lv_color_hex(0x6f8af6)
#define BAR_COLOR3          lv_color_hex(0xffffff)
#define BAR_REST_RADIUS     82

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void album_gesture_event_cb(lv_event_t * e);
static void spectrum_draw_event_cb(lv_event_t * e);
static int32_t get_cos(int32_t deg, int32_t a);
static int32_t get_sin(int32_t deg, int32_t a);
static void album_fade_anim_cb(void * var, int32_t v);
static lv_obj_t * album_img_create(lv_obj_t * parent);

/**********************
 *  STATIC VARIABLES
 **********************/
static uint32_t utime;
static uint32_t track_id;
static lv_timer_t *  sec_counter_timer;
static bool playing;
static bool start_anim;
static int32_t start_anim_values[40];

static uint32_t spectrum_i = 0;
static uint32_t bar_rot = 0;
static uint32_t bar_ofs = 0;
static uint32_t spectrum_i_pause = 0;
static uint32_t spectrum_lane_ofs_start = 0;
static const uint16_t (* spectrum)[4] = spectrum_1;
static uint32_t spectrum_len = sizeof(spectrum_1) / sizeof(spectrum_1[0]);
static const uint16_t rnd_array[30] = {994, 285, 553, 11, 792, 707, 966, 641, 852, 827, 44, 352, 146, 581, 490, 80, 729, 58, 695, 940, 724, 561, 124, 653, 27, 292, 557, 506, 382, 199};
static const char * title_list[] = {
    "Waiting for true love",
    "Need a Better Future",
    "Vibrations",
};

static const char * artist_list[] = {
    "The John Smith Band",
    "My True Name",
    "Robotics",
};

static const uint32_t time_list[] = {
    1*60 + 14,
    2*60 + 26,
    1*60 + 54,
};

/**
 * Create a demo application
 */

static void timer_cb(lv_timer_t *t)
{
    utime++;
    lv_label_set_text_fmt(guider_ui.screen_label_slider_time, "%d:%02d", utime / 60, utime % 60);
    lv_slider_set_value(guider_ui.screen_slider_time, utime, LV_ANIM_ON);
}

void custom_init(lv_ui *ui)
{
    /* Add your codes here */
    sec_counter_timer = lv_timer_create(timer_cb, 1000, NULL);
    lv_timer_pause(sec_counter_timer);
    lv_obj_add_event_cb(guider_ui.screen_img_album, album_gesture_event_cb, LV_EVENT_GESTURE, NULL);
    lv_obj_clear_flag(guider_ui.screen_img_album, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_refresh_ext_draw_size(guider_ui.screen_cont_album);
    lv_obj_add_event_cb(guider_ui.screen_cont_album, spectrum_draw_event_cb, LV_EVENT_ALL, NULL);
}

static void spectrum_anim_cb(void * a, int32_t v)
{
    lv_obj_t * obj = a;
    spectrum_i = v;
    lv_obj_invalidate(obj);

    static uint32_t bass_cnt = 0;
    static int32_t last_bass = -1000;
    static int32_t dir = 1;
    if(spectrum[spectrum_i][0] > 12) {
        if(spectrum_i-last_bass > 5) {
            bass_cnt++;
            last_bass = spectrum_i;
            if(bass_cnt >= 2) {
                bass_cnt = 0;
                spectrum_lane_ofs_start = spectrum_i;
                bar_ofs++;
            }
        }
    }
    if(spectrum[spectrum_i][0] < 4) bar_rot+= dir;

    lv_image_set_scale(guider_ui.screen_img_album, LV_SCALE_NONE + spectrum[spectrum_i][0]);
}

static void spectrum_end_cb(lv_anim_t * a)
{
    lv_demo_music_album_next(true);
}

void lv_demo_music_resume(void)
{
    playing = true;
    spectrum_i = spectrum_i_pause;
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_values(&a, spectrum_i, spectrum_len - 1);
    lv_anim_set_exec_cb(&a, spectrum_anim_cb);
    lv_anim_set_var(&a, guider_ui.screen_cont_album);
    lv_anim_set_time(&a, ((spectrum_len - spectrum_i) * 1000) / 30);
    lv_anim_set_playback_time(&a, 0);
    lv_anim_set_ready_cb(&a, spectrum_end_cb);
    lv_anim_start(&a);

    lv_timer_resume(sec_counter_timer);
    lv_slider_set_range(guider_ui.screen_slider_time, 0, time_list[track_id]);

    lv_obj_add_state(guider_ui.screen_imgbtn_play, LV_STATE_CHECKED);
}

void lv_demo_music_pause(void)
{
    playing = false;
    spectrum_i_pause = spectrum_i;
    spectrum_i = 0;
    lv_anim_delete(guider_ui.screen_cont_album, spectrum_anim_cb);
    lv_obj_invalidate(guider_ui.screen_cont_album);
    lv_image_set_scale(guider_ui.screen_img_album, LV_SCALE_NONE);
    lv_timer_pause(sec_counter_timer);
    lv_obj_clear_state(guider_ui.screen_imgbtn_play, LV_STATE_CHECKED);
}

static void album_gesture_event_cb(lv_event_t * e)
{
    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
    if(dir == LV_DIR_LEFT) lv_demo_music_album_next(true);
    if(dir == LV_DIR_RIGHT) lv_demo_music_album_next(false);
}

static lv_obj_t * album_img_create(lv_obj_t * parent)
{
    LV_IMAGE_DECLARE(_cover_2_ARGB8888_300x300);
    LV_IMAGE_DECLARE(_cover_3_ARGB8888_300x300);

    lv_obj_t * img;
    img = lv_image_create(parent);
	lv_obj_set_pos(img, 59, 59);

    switch(track_id) {
    case 2:
        lv_image_set_src(img, &_cover_3_ARGB8888_300x300);
        spectrum = spectrum_3;
        spectrum_len = sizeof(spectrum_3) / sizeof(spectrum_3[0]);
        break;
    case 1:
        lv_image_set_src(img, &_cover_2_ARGB8888_300x300);
        spectrum = spectrum_2;
        spectrum_len = sizeof(spectrum_2) / sizeof(spectrum_2[0]);
        break;
    case 0:
        lv_image_set_src(img, &_cover_1_ARGB8888_300x300);
        spectrum = spectrum_1;
        spectrum_len = sizeof(spectrum_1) / sizeof(spectrum_1[0]);
        break;
    }
    lv_image_set_antialias(img, false);
    lv_obj_add_event_cb(img, album_gesture_event_cb, LV_EVENT_GESTURE, NULL);
    lv_obj_clear_flag(img, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_add_flag(img, LV_OBJ_FLAG_CLICKABLE);

    return img;

}

static void track_load(uint32_t id)
{
    spectrum_i = 0;
    utime = 0;
    spectrum_i_pause = 0;
    lv_slider_set_value(guider_ui.screen_slider_time, 0, LV_ANIM_OFF);
    lv_label_set_text(guider_ui.screen_label_slider_time, "0:00");

    if(id == track_id) return;
    bool next = false;
    if((track_id + 1) % ACTIVE_TRACK_CNT == id) next = true;

    lv_demo_music_list_btn_check(track_id, false);

    track_id = id;

    lv_demo_music_list_btn_check(id, true);

    lv_label_set_text(guider_ui.screen_label_title_music, title_list[track_id]);
    lv_label_set_text(guider_ui.screen_label_title_author, artist_list[track_id]);

    lv_obj_fade_out(guider_ui.screen_img_album, 500, 0);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, guider_ui.screen_img_album);
    lv_anim_set_values(&a, lv_obj_get_style_image_opa(guider_ui.screen_img_album, 0), LV_OPA_TRANSP);
    lv_anim_set_exec_cb(&a, album_fade_anim_cb);
    lv_anim_set_duration(&a, 500);
    lv_anim_start(&a);

    lv_anim_init(&a);
    lv_anim_set_var(&a, guider_ui.screen_img_album);
    lv_anim_set_time(&a, 500);
    lv_anim_set_path_cb(&a, lv_anim_path_ease_out);

    if(next) {
        lv_anim_set_values(&a,  0, - LV_HOR_RES / 2);
    } else {
        lv_anim_set_values(&a, 0, LV_HOR_RES / 2);
    }

    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) lv_obj_set_x);
    lv_anim_set_completed_cb(&a, lv_obj_delete_anim_completed_cb);
    lv_anim_start(&a);

    lv_anim_set_path_cb(&a, lv_anim_path_linear);
    lv_anim_set_var(&a, guider_ui.screen_img_album);
    lv_anim_set_time(&a, 500);
    lv_anim_set_values(&a, LV_SCALE_NONE, LV_SCALE_NONE / 2);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) lv_image_set_scale);
    lv_anim_set_completed_cb(&a, NULL);
    lv_anim_start(&a);

    guider_ui.screen_img_album = album_img_create(guider_ui.screen_cont_album);

    lv_anim_set_path_cb(&a, lv_anim_path_overshoot);
    lv_anim_set_var(&a, guider_ui.screen_img_album);
    lv_anim_set_time(&a, 500);
    lv_anim_set_delay(&a, 100);
    lv_anim_set_values(&a, LV_SCALE_NONE / 4, LV_SCALE_NONE);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) lv_image_set_scale);
    lv_anim_set_ready_cb(&a, NULL);
    lv_anim_start(&a);

    lv_anim_init(&a);
    lv_anim_set_var(&a, guider_ui.screen_img_album);
    lv_anim_set_values(&a, 0, LV_OPA_COVER);
    lv_anim_set_exec_cb(&a, album_fade_anim_cb);
    lv_anim_set_duration(&a, 500);
    lv_anim_set_delay(&a, 100);
    lv_anim_start(&a);
}

void lv_demo_music_album_next(bool next)
{
    uint32_t id = track_id;
    if(next) {
        id++;
        if(id >= ACTIVE_TRACK_CNT) id = 0;
    } else {
        if(id == 0) {
            id = ACTIVE_TRACK_CNT - 1;
        } else {
            id--;
        }
    }

    if(playing) {
        lv_demo_music_play(id);
    } else {
        track_load(id);
    }
}

void lv_demo_music_play(uint32_t id)
{
    track_load(id);
    lv_demo_music_resume();
}

static void album_fade_anim_cb(void * var, int32_t v)
{
    lv_obj_set_style_image_opa(var, v, 0);
}

static lv_obj_t * lv_demo_music_get_list_img(uint32_t track_id)
{
    switch (track_id)
    {
    case 0:
        return guider_ui.screen_img_1;
        break;
    case 1:
        return guider_ui.screen_img_2;
        break;
    case 2:
        return guider_ui.screen_img_3;
        break;
    default:
        return NULL;
        break;
    }
}

static lv_obj_t * lv_demo_music_get_list_btn(uint32_t track_id)
{
    switch (track_id)
    {
    case 0:
        return guider_ui.screen_btn_1;
        break;
    case 1:
        return guider_ui.screen_btn_2;
        break;
    case 2:
        return guider_ui.screen_btn_3;
        break;
    default:
        return NULL;
        break;
    }
}

void lv_demo_music_list_btn_check(uint32_t track_id, bool state)
{
    lv_obj_t * btn = lv_demo_music_get_list_btn(track_id);
    lv_obj_t * icon = lv_demo_music_get_list_img(track_id);

    if(state) {
        lv_obj_add_state(btn, LV_STATE_PRESSED);
        lv_image_set_src(icon, &_btn_list_pause_RGB565A8_70x70);
        lv_obj_scroll_to_view(btn, LV_ANIM_ON);
    }
    else {
        lv_obj_clear_state(btn, LV_STATE_PRESSED);
        lv_image_set_src(icon, &_btn_list_play_RGB565A8_70x70);
    }
}

int32_t get_cos(int32_t deg, int32_t a)
{
    int32_t r = (lv_trigo_cos(deg) * a);

    r += LV_TRIGO_SIN_MAX / 2;
    return r >> LV_TRIGO_SHIFT;
}

int32_t get_sin(int32_t deg, int32_t a)
{
    int32_t r = lv_trigo_sin(deg) * a;

    return (r + LV_TRIGO_SIN_MAX / 2) >> LV_TRIGO_SHIFT;
}

static void spectrum_draw_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_REFR_EXT_DRAW_SIZE) {
        lv_event_set_ext_draw_size(e, LV_VER_RES);
    }
    else if(code == LV_EVENT_COVER_CHECK) {
        lv_event_set_cover_res(e, LV_COVER_RES_NOT_COVER);
    }
    else if(code == LV_EVENT_DRAW_MAIN) {

        // static int32_t center_value = NaN;
        lv_obj_t * obj = lv_event_get_target(e);
        lv_layer_t * layer = lv_event_get_layer(e);

        lv_opa_t opa = lv_obj_get_style_opa_recursive(obj, LV_PART_MAIN);
        if(opa < LV_OPA_MIN) return;

        lv_point_t poly[4];
        lv_point_t center;
        //center.x = obj->coords.x1 + lv_obj_get_width(obj) / 2;
        //center.y = obj->coords.y1 + lv_obj_get_height(obj) / 2;
        lv_area_t coords;
        lv_obj_get_coords(obj, &coords);
        center.x = coords.x1 + lv_obj_get_width(obj) / 2;
        center.y = coords.y1 + lv_obj_get_height(obj) / 2;

        lv_draw_triangle_dsc_t draw_dsc;
        lv_draw_triangle_dsc_init(&draw_dsc);
        draw_dsc.opa = LV_OPA_COVER;

        uint16_t r[64];
        uint32_t i;

        lv_coord_t min_a = 0;
        lv_coord_t r_in = 134;
        
        r_in = (r_in * lv_image_get_scale(guider_ui.screen_img_album)) >> 8;
        for(i = 0; i < BAR_CNT; i++) r[i] = r_in + min_a;

        uint32_t s;
        for(s = 0; s < 4; s++) {
            uint32_t f;
            uint32_t band_w = 0;    /*Real number of bars in this band.*/
            switch(s) {
            case 0:
                band_w = 20;
                break;
            case 1:
                band_w = 8;
                break;
            case 2:
                band_w = 4;
                break;
            case 3:
                band_w = 2;
                break;
            }

            /* Add "side bars" with cosine characteristic.*/
            for(f = 0; f < band_w; f++) {
                uint32_t ampl_main = spectrum[spectrum_i][s];
                int32_t ampl_mod = get_cos(f * 360 / band_w + 180, 180) + 180;
                int32_t t = BAR_PER_BAND_CNT * s - band_w / 2 + f;
                if(t < 0) t = BAR_CNT + t;
                if(t >= BAR_CNT) t = t - BAR_CNT;
                r[t] += (ampl_main * ampl_mod) >> 9;
            }
        }

        uint32_t amax = 10;
        int32_t animv = spectrum_i - spectrum_lane_ofs_start;
        if(animv > amax) animv = amax;
        for(i = 0; i < BAR_CNT; i++) {
            uint32_t deg_space = 1;
            uint32_t deg = i * DEG_STEP + 90;
            uint32_t j =  (i + bar_rot + rnd_array[bar_ofs %10]) % BAR_CNT;
            uint32_t k = (i + bar_rot + rnd_array[(bar_ofs + 1) % 10]) % BAR_CNT;

            uint32_t v = (r[k] * animv + r[j] * (amax - animv)) / amax;

            if(v < BAR_COLOR1_STOP) draw_dsc.color = BAR_COLOR1;
            else if(v > BAR_COLOR3_STOP) draw_dsc.color = BAR_COLOR3;
            else if(v > BAR_COLOR2_STOP) draw_dsc.color = lv_color_mix(BAR_COLOR3, BAR_COLOR2, ((v - BAR_COLOR2_STOP) * 255) / (BAR_COLOR3_STOP-BAR_COLOR2_STOP));
            else draw_dsc.color = lv_color_mix(BAR_COLOR2, BAR_COLOR1, ((v - BAR_COLOR1_STOP) * 255) / (BAR_COLOR2_STOP - BAR_COLOR1_STOP));

            uint32_t di = deg + deg_space;

            int32_t x1_out = get_cos(di, v);
            draw_dsc.p[0].x = center.x + x1_out;
            draw_dsc.p[0].y = center.y + get_sin(di, v);

            di += DEG_STEP - deg_space * 2;

            int32_t x2_out = get_cos(di, v);
            draw_dsc.p[1].x = center.x + x2_out;
            draw_dsc.p[1].y = center.y + get_sin(di, v);

            int32_t x2_in = get_cos(di, 0);
            draw_dsc.p[2].x = center.x + x2_in;
            draw_dsc.p[2].y = center.y + get_sin(di, 0);
            lv_draw_triangle(layer, &draw_dsc);

            draw_dsc.p[0].x = center.x - x1_out;
            draw_dsc.p[1].x = center.x - x2_out;
            draw_dsc.p[2].x = center.x - x2_in;
            lv_draw_triangle(layer, &draw_dsc);
        }
    }
}
