// Zephyr and device-related includes
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/display.h>
#include <zephyr/drivers/sensor.h>
#include <lvgl.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/timeutil.h>

// Custom headers for graphics, Bluetooth, fonts, drivers, etc.
#include "background.h"
#include "steps_img.h"
#include "heart.h"
#include "bluetooth.h"
#include "font1.h"
#include "background1.h"
#include "rtc_driver.h"
#include "display_ili9341.h"
#include "max30101.h"
#include "bmi160.h"
#include "bluetooth.h"
#include "ble_hrs.h"
#include "ble_nus.h"
#include "ble_service.h"
#include "watchdog.h"
#include "battery_monitor.h"

// ---------------------------------
// Constants and global variables
// ---------------------------------

#define BUFFER_SIZE 500 // Size of the IR buffer for HR signal processing

static uint32_t ir_buffer[BUFFER_SIZE]; // Buffer for storing raw IR samples
static int buffer_index = 0; // Index for buffer

char *received_data_from_bluetooth; // Pointer to hold received Bluetooth commands
bool value_nrf_connect = false;     // Flag indicating Bluetooth command received
bool value_nrf_connect2 = false;    // Secondary flag (may be used elsewhere)

// ------------------------------
// Thread stack definitions
// ------------------------------
K_THREAD_STACK_DEFINE(max30101_thread_stack, 5000);
K_THREAD_STACK_DEFINE(bmi160_thread_stack, 5000);
K_THREAD_STACK_DEFINE(display_thread_stack, 4096);
K_THREAD_STACK_DEFINE(bluetooth_thread_stack, 4096);

// Thread control structures
static struct k_thread max30101_thread_data;
static struct k_thread bmi160_thread_data;
static struct k_thread display_thread_data;
static struct k_thread bluetooth_thread_data;

// ------------------------------
// Message queue definitions
// ------------------------------

// Queue for heart rate values
K_MSGQ_DEFINE(hr_msgq, sizeof(int), 10, 4);

// Structure to store step data and accelerometer values
struct step_data {
    uint16_t steps;
    struct sensor_value accel[3];
};
K_MSGQ_DEFINE(step_msgq, sizeof(struct step_data), 10, 4);

// Queue for display data (HR and steps)
struct display_data {
    uint32_t hr;
    uint32_t steps;
};
K_MSGQ_DEFINE(display_msgq, sizeof(struct display_data), 10, 4);

// Queue for Bluetooth data (HR and steps)
struct bluetooth_data {
    uint32_t hr;
    uint32_t steps;
};
K_MSGQ_DEFINE(bluetooth_msgq, sizeof(struct bluetooth_data), 10, 4);

// ------------------------------
// Function prototypes for threads
// ------------------------------
void max30101_thread(void *arg1, void *arg2, void *arg3);   // HR sensor processing
void bmi160_thread(void *arg1, void *arg2, void *arg3);     // Step counter sensor
void display_thread(void *arg1, void *arg2, void *arg3);    // UI rendering
void bluetooth_thread(void *arg1, void *arg2, void *arg3);  // BLE communication

// Callback function when data is received over BLE
void handle_received_data(const char *data)
{
    printk("App received: %s\n", data);
    received_data_from_bluetooth = data;
    value_nrf_connect = true;
    value_nrf_connect2 = true;
}

// ------------------------------
// Main application entry point
// ------------------------------
void main(void) 
{
    // Get display device
    const struct device *display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
    if (!device_is_ready(display_dev)) {
        printk("Display not ready\n");
        return;
    }

    // Get I2C device for MAX30101
    const struct device *i2c_dev = DEVICE_DT_GET(DT_NODELABEL(i2c0));
    if (!device_is_ready(i2c_dev)) {
        printk("I2C for MAX not ready!\n");
        return;
    }

    // Initialize MAX30101 heart rate sensor
    if (max30101_init(i2c_dev) != 0) {
        printk("Sensor init failed!\n");
        return;
    }

    // Set RTC to a default time
    rtc_set_initial_time("2023-10-01 12:00:00");

    // Initialize BLE and set callback
    ble_init(handle_received_data);

    // Setup display and UI
    display_blanking_off(display_dev);
    lv_obj_clean(lv_scr_act());
    initialize_ui();
    watchface1(); // Default watchface

    // Initialize watchdog timer
    watchdog_init();

    //Initialize battery monitor
    battery_monitor_init();

    // Variables for local use (not used in the shown code)
    uint32_t step_count = 0;
    uint32_t last_update = k_uptime_get_32();
    uint32_t seed = k_cycle_get_32();
    uint8_t heart_rate = 80;

    // ----------------------
    // Create and start threads
    // ----------------------
    k_thread_create(&max30101_thread_data, max30101_thread_stack,
                    K_THREAD_STACK_SIZEOF(max30101_thread_stack),
                    max30101_thread, NULL, NULL, NULL, 5, 0, K_NO_WAIT);

    k_thread_create(&bmi160_thread_data, bmi160_thread_stack,
                    K_THREAD_STACK_SIZEOF(bmi160_thread_stack),
                    bmi160_thread, NULL, NULL, NULL, 5, 0, K_NO_WAIT);

    k_thread_create(&display_thread_data, display_thread_stack,
                    K_THREAD_STACK_SIZEOF(display_thread_stack),
                    display_thread, NULL, NULL, NULL, 4, 0, K_NO_WAIT); // Higher priority

    k_thread_create(&bluetooth_thread_data, bluetooth_thread_stack,
                    K_THREAD_STACK_SIZEOF(bluetooth_thread_stack),
                    bluetooth_thread, NULL, NULL, NULL, 3, 0, K_NO_WAIT); // Lower than display

    // ----------------------
    // Main application loop
    // ----------------------
    while (1) {
        int heart_rate;
        struct step_data step_data;
        struct display_data display_data = {0};
        struct bluetooth_data bt_data = {0};


        battery_monitor_process();
        
        // Check if Bluetooth command received
        if(value_nrf_connect) {
            if(received_data_from_bluetooth > 0){
                // Switch between different watchfaces or set RTC
                if(strcmp(received_data_from_bluetooth, "watchface1") == 0) {
                    watchface1();
                } else if(strcmp(received_data_from_bluetooth, "watchface2") == 0) {
                    watchface2();
                } else if(strcmp(received_data_from_bluetooth, "w1steps") == 0) {
                    watchfacesteps();
                } else if(strcmp(received_data_from_bluetooth, "w1hr") == 0) {
                    watchfacehr();
                } else if(strcmp(received_data_from_bluetooth, "enablecd") == 0) {
                    enable_change_display_by_accel = true;
                } else if(strcmp(received_data_from_bluetooth, "disablecd") == 0) {
                    enable_change_display_by_accel = false;
                
                }else {
                    rtc_set_initial_time(received_data_from_bluetooth); // Parse date/time
                }
                received_data_from_bluetooth = NULL; // Clear command
            }
            value_nrf_connect = false; // Reset flag
        }

        // Read HR data from queue
        if (k_msgq_get(&hr_msgq, &heart_rate, K_NO_WAIT) == 0) {
            printk("HR: %d bpm\n", heart_rate);
            display_data.hr = heart_rate;
            bt_data.hr = heart_rate;
        }

        // Read step data from queue
        if (k_msgq_get(&step_msgq, &step_data, K_NO_WAIT) == 0) {
            printk("Steps: %u\n", step_data.steps);
            display_data.steps = step_data.steps;
            bt_data.steps = step_data.steps;
        }
        
        // Send data to display and Bluetooth threads if available
        if (display_data.hr != 0 || display_data.steps != 0) {
            k_msgq_put(&display_msgq, &display_data, K_NO_WAIT);
            k_msgq_put(&bluetooth_msgq, &bt_data, K_NO_WAIT);
        }

        // Update time and UI
        rtc_update_time_label(my_time_label, my_date_label, short_time_label);
        lv_task_handler(); // Update GUI
        k_msleep(1000);    // Sleep for 1 second
    }
}







void max30101_thread(void *arg1, void *arg2, void *arg3)
{
    ARG_UNUSED(arg1);
    ARG_UNUSED(arg2);
    ARG_UNUSED(arg3);

    #define HR_HISTORY_SIZE 10
    static uint16_t hr_history[HR_HISTORY_SIZE];
    static uint8_t hr_index = 0;
    static bool hr_history_full = false;
    static uint16_t avg_hr = 0;

    while (1) {
        uint32_t ir;
        if (max30101_read_ir_sample(&ir) == 0) {
            ir_buffer[buffer_index++] = ir;

            if (buffer_index >= BUFFER_SIZE) {
                int delta = count_peaks(ir_buffer, BUFFER_SIZE);
                int heart_rate = 0;

                if (delta <= 0) {
                    printk("Finger removed\n");

                } else {
                    heart_rate = (60 * 100) / delta;
                    
                    if(heart_rate > 40 && heart_rate < 200) {  // Valid HR range
                        // Store HR in history
                        hr_history[hr_index++] = heart_rate;
                        
                        // Check if history is full
                        if (hr_index >= HR_HISTORY_SIZE) {
                            hr_index = 0;
                            hr_history_full = true;
                        }
                        
                        // Calculate average HR
                        if (hr_history_full) {
                            uint16_t temp_array[HR_HISTORY_SIZE];
                            memcpy(temp_array, hr_history, sizeof(hr_history));
                            
                            // Sort the array to easily find min/max values
                            for (int i = 0; i < HR_HISTORY_SIZE-1; i++) {
                                for (int j = i+1; j < HR_HISTORY_SIZE; j++) {
                                    if (temp_array[i] > temp_array[j]) {
                                        uint16_t temp = temp_array[i];
                                        temp_array[i] = temp_array[j];
                                        temp_array[j] = temp;
                                    }
                                }
                            }
                            uint32_t sum = 0;
                            for (int i = 0; i < HR_HISTORY_SIZE; i++) {
                                sum += hr_history[i];
                            }
                            avg_hr = sum / HR_HISTORY_SIZE;
                            
                            // Send both current and average HR
                            struct hr_data {
                                uint16_t current_hr;
                                uint16_t average_hr;
                            } hr_msg;
                            
                            hr_msg.current_hr = heart_rate;
                            hr_msg.average_hr = avg_hr;
                            
                            k_msgq_put(&hr_msgq, &hr_msg.average_hr, K_NO_WAIT);
                            
                            printk("HR: %d (avg: %d)\n", heart_rate, avg_hr);
                        } else {
                            // Send only current HR until we have enough samples
                            struct hr_data {
                                uint16_t current_hr;
                                uint16_t average_hr;
                            } hr_msg;
                            
                            hr_msg.current_hr = heart_rate;
                            hr_msg.average_hr = 0;  // Not available yet
                            
                            k_msgq_put(&hr_msgq, &hr_msg.current_hr, K_NO_WAIT);
                            
                            printk("HR: %d (collecting samples)\n", heart_rate);
                        }
                    }
                }
                buffer_index = 0;
            }
        }
        k_sleep(K_MSEC(10));
    }
}





void bmi160_thread(void *arg1, void *arg2, void *arg3)
{
    ARG_UNUSED(arg1);
    ARG_UNUSED(arg2);
    ARG_UNUSED(arg3);
    
    const struct device *sensor = DEVICE_DT_GET_ONE(bosch_bmi160);
    if (!device_is_ready(sensor)) {
        printk("BMI160 device not ready\n");
        return;
    }

    if (bmi160_enable_step_counter() != 0) {
        printk("Failed to enable step counter\n");
        return;
    }
    int16_t ax, ay, az;
    
    
    while (1) {
        uint16_t steps = 0;
        struct sensor_value accel[3];
        struct step_data step_data;
        if (bmi160_read_accel(&ax, &ay, &az) == 0) {
            printk("Accel X: %d, Y: %d, Z: %d\n", ax, ay, az);
        }
        if (sensor_sample_fetch(sensor) == 0) {
            if (sensor_channel_get(sensor, SENSOR_CHAN_ACCEL_XYZ, accel) == 0) {
                if (bmi160_read_step_count(&steps) == 0) {
                    step_data.steps = steps;
                    memcpy(step_data.accel, accel, sizeof(accel));
                    k_msgq_put(&step_msgq, &step_data, K_NO_WAIT);
                }
            }
        }
        k_sleep(K_MSEC(100));
    }
}

void display_thread(void *arg1, void *arg2, void *arg3)
{
    ARG_UNUSED(arg1);
    ARG_UNUSED(arg2);
    ARG_UNUSED(arg3);


    
    struct display_data data = {0};
    
    while (1) {
        // Get new data from queue with timeout
        if (k_msgq_get(&display_msgq, &data, K_MSEC(100)) == 0) {
            update_lcd_display(data.hr, data.steps);
        }
        
        // Always refresh the display periodically
        lv_task_handler();
        k_sleep(K_MSEC(50));  // Refresh at ~20Hz
    }
}

void bluetooth_thread(void *arg1, void *arg2, void *arg3)
{
    ARG_UNUSED(arg1);
    ARG_UNUSED(arg2);
    ARG_UNUSED(arg3);

    struct bluetooth_data data;
    static uint32_t last_hr = 0;
    static uint32_t last_steps = 0;

    while (1) {
        if (k_msgq_get(&bluetooth_msgq, &data, K_MSEC(100)) == 0) {
            // Only send data if it has changed
            if (data.hr != last_hr || data.steps != last_steps) {
                ble_nus_send_data(data.hr, data.steps);
                ble_hrs_update(data.hr);
                last_hr = data.hr;
                last_steps = data.steps;
            }
        }
        k_sleep(K_MSEC(100));
    }
}
