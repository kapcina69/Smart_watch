#ifndef RTC_DRIVER_H
#define RTC_DRIVER_H

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/counter.h>
#include <lvgl.h>

/**
 * @brief Initializes the RTC (Real-Time Clock) module.
 * 
 * @return int 
 */
int rtc_init(void);

/**
 * @brief Set the initial time for the RTC.
 * 
 * This function sets the initial time for the RTC module.
 * 
 * @param data 
 */
void rtc_set_initial_time(const char *data);

/**
 * @brief Updates the time label and date label on the display.
 * 
 * This function retrieves the current time from the RTC and updates the
 * time and date labels on the display.
 * 
 * @param time_label 
 * @param date_label 
 */
void rtc_update_time_label(lv_obj_t *time_label, lv_obj_t *date_label);

#endif /* RTC_DRIVER_H */