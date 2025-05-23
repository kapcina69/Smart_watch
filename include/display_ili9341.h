#ifndef DISPLAY_ILI9341_H
#define DISPLAY_ILI9341_H

#include <lvgl.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

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
extern lv_obj_t *short_time_label;



/** @brief Initializes the UI components.
 *
 * This function creates and configures the UI components for the display.
 * It sets up images, labels, and their properties.
 */
void initialize_ui(void);



/**
 * @brief Hides all UI views.
 *
 * This function sets the visibility of all UI components to hidden.
 * It is used to clear the display before showing a new view.
 */
void hide_all_views(void);


/**
 * @brief Displays the main watch face.
 * 
 * This function sets up the main watch face with the background image,
 * heart rate label, steps label, and other UI elements.
 */
extern void watchface1(void);


/**
 * @brief Displays the watch face with other features.
 * 
 * This function sets up the watch face with a different background image
 * and shows the steps label and shoes image.
 * It is used for a specific watch face view.
 */
void watchface2(void);

/**
 * @brief Updates the LCD display with heart rate and steps.
 * 
 * This function updates the heart rate and steps labels on the LCD display.
 * It sets the text for the heart rate and steps labels and aligns them on the screen.
 * 
 * @param heart_rate The current heart rate value.
 * @param steps The current step count.
 * 
 */
void update_lcd_display(uint32_t heart_rate, uint32_t steps);

/**
 * @brief Set HR on watchface1
 * 
 * This function sets up the watch face with heart rate and cardiogram images.
 * It is used for a specific watch face view.
 */
extern void watchfacehr(void); 


/**
 * @brief Set steps on watchface1
 * 
 * This function sets up the watch face with steps and shoes images.
 * It is used for a specific watch face view.
 */
extern void watchfacesteps(void); 

/**
 * @brief Set battery status
 * 
 * This function updates the battery status on the display based on the percentage.
 * It shows or hides the battery label images according to the battery level.
 * 
 * @param percentage The current battery percentage (0-100).
 * @param is_charging Indicates if the device is charging (true/false).
 */
void show_battery_status(int percentage,bool is_charging);

#endif // UI_H
