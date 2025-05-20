#ifndef DISPLAY_ILI9341_H
#define DISPLAY_ILI9341_H

#include <lvgl.h>

// Extern LVGL objekti
extern lv_obj_t *battery_label;
extern lv_obj_t *heart_label;
extern lv_obj_t *steps_label;
extern lv_obj_t *my_time_label;
extern lv_obj_t *my_date_label;
extern lv_obj_t *battery_percent_label;
extern lv_obj_t *image;
extern lv_obj_t *image1;
extern lv_obj_t *bluetooth_img;
extern lv_obj_t *bluetooth_img1;
extern lv_obj_t *bt_label;
extern lv_obj_t *steps_img;
extern lv_obj_t *heart_img;

// Funkcije
void initialize_ui(void);
void hide_all_views(void);
void watchface1(void);
void watchface2(void);
void update_lcd_display(uint32_t heart_rate, uint32_t steps);

#endif // UI_H
