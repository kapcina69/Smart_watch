#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/display.h>
#include <lvgl.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/timeutil.h>
// #include "background.h"
#include "steps_img.h"
#include "heart.h"
#include "bluetooth.h"
#include "font1.h"
#include "background1.h"
#include "rtc_driver.h"
#include "display_ili9341.h"
#include "watchface1bg.h"
#include "shoesw1.h"
#include "cardiogram.h"
#include "bluetooth1.h"
#include "font2.h"

// Definicije LVGL objekata
lv_obj_t *battery_label;
lv_obj_t *battery_label1;
lv_obj_t *battery_label2;
lv_obj_t *battery_label3;
lv_obj_t *battery_label_empty;
lv_obj_t *heart_label;
lv_obj_t *steps_label;
lv_obj_t *my_time_label;
lv_obj_t *short_time_label;
lv_obj_t *my_date_label;
lv_obj_t *battery_percent_label = NULL;
lv_obj_t *image;
lv_obj_t *image1;
lv_obj_t *wachface1bg_img = NULL;
lv_obj_t *bluetooth_img = NULL;
lv_obj_t *bluetooth_img1 = NULL;
lv_obj_t *bt_label = NULL;
lv_obj_t *steps_img = NULL;
lv_obj_t *heart_img = NULL;
lv_obj_t *shoesw1_img = NULL;
lv_obj_t *cardiogram_img = NULL;
lv_obj_t *charging_img;
lv_obj_t *charging_img1;

void initialize_ui(void)
{
    image = lv_img_create(lv_scr_act());
    lv_img_set_src(image, &background1);
    lv_obj_align(image, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_flag(image, LV_OBJ_FLAG_HIDDEN);

    image1 = lv_img_create(lv_scr_act());
    lv_img_set_src(image1, &background1);
    lv_obj_align(image1, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_flag(image1, LV_OBJ_FLAG_HIDDEN);

    wachface1bg_img = lv_img_create(lv_scr_act());
    lv_img_set_src(wachface1bg_img, &watchface1bg);
    lv_obj_align(wachface1bg_img, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_flag(wachface1bg_img, LV_OBJ_FLAG_HIDDEN);


    bluetooth_img = lv_img_create(lv_scr_act());
    lv_img_set_src(bluetooth_img, &image_30x30);
    lv_obj_align(bluetooth_img, LV_ALIGN_CENTER, -63, -63);
    lv_obj_add_flag(bluetooth_img, LV_OBJ_FLAG_HIDDEN);

    bluetooth_img1 = lv_img_create(lv_scr_act());
    lv_img_set_src(bluetooth_img1, &bluetooth1);
    lv_obj_align(bluetooth_img1, LV_ALIGN_CENTER, -70, -90);
    lv_obj_add_flag(bluetooth_img1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_img_recolor(bluetooth_img1, lv_color_white(), LV_PART_MAIN);

    bt_label = lv_label_create(lv_scr_act());
    lv_label_set_text(bt_label, LV_SYMBOL_BLUETOOTH);
    lv_obj_set_style_text_color(bt_label, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(bt_label, &lv_font_montserrat_16, LV_PART_MAIN);
    lv_obj_add_flag(bt_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_align(bt_label, LV_ALIGN_CENTER, -80, -90);

    battery_label = lv_label_create(lv_scr_act());
    lv_label_set_text(battery_label, LV_SYMBOL_BATTERY_FULL);
    lv_obj_set_style_text_color(battery_label, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(battery_label, &lv_font_montserrat_16, LV_PART_MAIN);

    battery_label1 = lv_label_create(lv_scr_act());
    lv_label_set_text(battery_label1, LV_SYMBOL_BATTERY_3);
    lv_obj_set_style_text_color(battery_label1, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(battery_label1, &lv_font_montserrat_16, LV_PART_MAIN);

    battery_label2 = lv_label_create(lv_scr_act());
    lv_label_set_text(battery_label2, LV_SYMBOL_BATTERY_2);
    lv_obj_set_style_text_color(battery_label2, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(battery_label2, &lv_font_montserrat_16, LV_PART_MAIN);

    battery_label3 = lv_label_create(lv_scr_act());
    lv_label_set_text(battery_label3, LV_SYMBOL_BATTERY_1);
    lv_obj_set_style_text_color(battery_label3, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(battery_label3, &lv_font_montserrat_16, LV_PART_MAIN);

    battery_label_empty = lv_label_create(lv_scr_act());
    lv_label_set_text(battery_label_empty, LV_SYMBOL_BATTERY_EMPTY);
    lv_obj_set_style_text_color(battery_label_empty, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(battery_label_empty, &lv_font_montserrat_16, LV_PART_MAIN);

    battery_percent_label = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_color(battery_percent_label, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(battery_percent_label, &lv_font_montserrat_14, LV_PART_MAIN);
    lv_label_set_text(battery_percent_label, "30%");

    my_time_label = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_color(my_time_label, lv_color_hex(0xF4F0EC), LV_PART_MAIN);
    lv_obj_set_style_text_font(my_time_label, &ui_font_aliean_25, LV_PART_MAIN);

    short_time_label = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_color(short_time_label, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(short_time_label, &lv_font_montserrat_16, LV_PART_MAIN);
    lv_obj_align(short_time_label, LV_ALIGN_CENTER, 0,-90);

    my_date_label = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_color(my_date_label, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(my_date_label, &lv_font_montserrat_12, LV_PART_MAIN);

    heart_img = lv_img_create(lv_scr_act());
    lv_img_set_src(heart_img, &heart_beat);
    lv_obj_align(heart_img, LV_ALIGN_CENTER, 15, 50);
    lv_obj_add_flag(heart_img, LV_OBJ_FLAG_HIDDEN);

    cardiogram_img = lv_img_create(lv_scr_act());
    lv_img_set_src(cardiogram_img, &cardiogram);
    lv_obj_align(cardiogram_img, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_flag(cardiogram_img, LV_OBJ_FLAG_HIDDEN);

    heart_label = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_color(heart_label, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(heart_label, &lv_font_montserrat_16, LV_PART_MAIN);
    lv_label_set_text(heart_label, "00");
    lv_obj_add_flag(heart_label, LV_OBJ_FLAG_HIDDEN);

    steps_img = lv_img_create(lv_scr_act());
    lv_img_set_src(steps_img, &walk);
    lv_obj_align(steps_img, LV_ALIGN_CENTER, -55, 50);
    lv_obj_add_flag(steps_img, LV_OBJ_FLAG_HIDDEN);

    shoesw1_img = lv_img_create(lv_scr_act());
    lv_img_set_src(shoesw1_img, &shoesw1);
    lv_obj_align(shoesw1_img, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_flag(shoesw1_img, LV_OBJ_FLAG_HIDDEN);

    steps_label = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_color(steps_label, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(steps_label, &lv_font_montserrat_16, LV_PART_MAIN);
    lv_label_set_text(steps_label, "0");
    lv_obj_add_flag(steps_label, LV_OBJ_FLAG_HIDDEN);

    charging_img1 = lv_label_create(lv_scr_act());
    lv_label_set_text(charging_img1, LV_SYMBOL_CHARGE);
    lv_obj_set_style_text_color(charging_img1, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(charging_img1, &lv_font_montserrat_16, LV_PART_MAIN);
    lv_obj_align(charging_img1, LV_ALIGN_CENTER, 80, -90);
    lv_obj_add_flag(charging_img1, LV_OBJ_FLAG_HIDDEN);



}

void show_battery_status(int percentage, bool is_charging)

{
    if (is_charging) {
        lv_obj_clear_flag(charging_img1, LV_OBJ_FLAG_HIDDEN);
        printk("Charging status: Punjenje\n");
    }
    else {
        lv_obj_add_flag(charging_img1, LV_OBJ_FLAG_HIDDEN);
    }
    
    if (percentage >= 85) {
        lv_obj_clear_flag(battery_label, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(battery_label1, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(battery_label2, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(battery_label3, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(battery_label_empty, LV_OBJ_FLAG_HIDDEN);
    } else if (percentage >= 55) {
        lv_obj_clear_flag(battery_label1, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(battery_label, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(battery_label2, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(battery_label3, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(battery_label_empty, LV_OBJ_FLAG_HIDDEN);
    } else if (percentage >= 30) {
        lv_obj_clear_flag(battery_label2, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(battery_label, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(battery_label1, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(battery_label3, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(battery_label_empty, LV_OBJ_FLAG_HIDDEN);
    } else if (percentage >= 10) {
        lv_obj_clear_flag(battery_label3, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(battery_label, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(battery_label1, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(battery_label2, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(battery_label_empty, LV_OBJ_FLAG_HIDDEN);
    } else if (percentage >= 0) {
        lv_obj_clear_flag(battery_label_empty, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(battery_label, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(battery_label1, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(battery_label2, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(battery_label3, LV_OBJ_FLAG_HIDDEN);
    }
}


void hide_all_views(void)
{
    lv_obj_add_flag(image, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(image1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(wachface1bg_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(bluetooth_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(bt_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(my_time_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(my_date_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(heart_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(heart_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(steps_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(steps_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(shoesw1_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(cardiogram_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(short_time_label, LV_OBJ_FLAG_HIDDEN);

}

void watchface1(void)
{
    k_msleep(100);
    hide_all_views();
    k_msleep(100);

    lv_obj_clear_flag(image1, LV_OBJ_FLAG_HIDDEN);

    lv_obj_clear_flag(steps_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_align(steps_label, LV_ALIGN_CENTER, -45, 80);
    lv_obj_set_style_text_font(steps_label, &lv_font_montserrat_16, LV_PART_MAIN);
    lv_obj_set_style_text_font(heart_label, &lv_font_montserrat_16, LV_PART_MAIN);


    lv_obj_clear_flag(heart_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_align(heart_label, LV_ALIGN_CENTER, 42, 80);

    lv_obj_clear_flag(my_time_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_align(my_time_label, LV_ALIGN_CENTER, 0, -40);
    lv_obj_set_style_text_font(my_time_label, &ui_font_aliean_25, LV_PART_MAIN);

    lv_obj_clear_flag(my_date_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_align(my_date_label, LV_ALIGN_CENTER, 0, -20);

    lv_obj_align(battery_label, LV_ALIGN_CENTER, 80, -90);
    lv_obj_align(battery_label1, LV_ALIGN_CENTER, 80, -90);
    lv_obj_align(battery_label2, LV_ALIGN_CENTER, 80, -90);
    lv_obj_align(battery_label3, LV_ALIGN_CENTER, 80, -90);
    lv_obj_align(battery_label_empty, LV_ALIGN_CENTER, 80, -90);
    lv_obj_align_to(battery_percent_label, battery_label, LV_ALIGN_OUT_RIGHT_MID, -52, 0);


}

void watchfacesteps(void)
{
    k_msleep(100);
    hide_all_views();
    k_msleep(100);

    lv_obj_clear_flag(short_time_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(wachface1bg_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(steps_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_align(steps_label, LV_ALIGN_CENTER, 0, 40);
    lv_obj_clear_flag(shoesw1_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_align(shoesw1_img, LV_ALIGN_CENTER, 0, -15);
    lv_obj_set_style_text_font(steps_label, &ui_font_aliean_25, LV_PART_MAIN);

}


void watchfacehr(void)
{
    k_msleep(100);
    hide_all_views();
    k_msleep(100);



    lv_obj_clear_flag(short_time_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(wachface1bg_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(heart_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_align(heart_label, LV_ALIGN_CENTER, 0, 40);
    lv_obj_clear_flag(cardiogram_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_align(cardiogram_img, LV_ALIGN_CENTER, 0, -15);
    lv_obj_set_style_text_font(heart_label, &ui_font_aliean_25, LV_PART_MAIN);

}




void watchface2(void)
{
    k_msleep(100);
    hide_all_views();
    k_msleep(100);

    lv_obj_clear_flag(image, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(bluetooth_img, LV_OBJ_FLAG_HIDDEN);

    lv_obj_clear_flag(steps_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_align_to(steps_label, steps_img, LV_ALIGN_OUT_RIGHT_MID, 10, 0);

    lv_obj_clear_flag(heart_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_align_to(heart_label, heart_img, LV_ALIGN_OUT_RIGHT_MID, 7, 0);

    lv_obj_clear_flag(heart_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(steps_img, LV_OBJ_FLAG_HIDDEN);

    lv_obj_clear_flag(my_time_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_align(my_time_label, LV_ALIGN_CENTER, 0, -30);

    lv_obj_clear_flag(my_date_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_align(my_date_label, LV_ALIGN_CENTER, 0, -10);

    lv_obj_align(battery_label, LV_ALIGN_CENTER, 65, -65);
    lv_obj_align_to(battery_percent_label, battery_label, LV_ALIGN_OUT_RIGHT_MID, -59, 0);
}





void update_lcd_display(uint32_t heart_rate, uint32_t steps)
{
    if(heart_rate!= 0) {
        lv_label_set_text_fmt(heart_label, "%d", heart_rate);
    }
    if(steps != 0) {
        lv_label_set_text_fmt(steps_label, "%d", steps);
    }
}
