#ifndef BATTERY_MONITOR_H
#define BATTERY_MONITOR_H

#include <stdint.h>
#include <stdbool.h>



#ifdef __cplusplus
extern "C" {
#endif

/* Battery voltage calculation constants */
#define VOLTAGE_DIVIDER_RATIO 2.0f
#define ADC_REF_VOLTAGE_MV 3600
#define ADC_MAX_VALUE 4095
#define CHARGING_THRESHOLD_MV 1500

/* Battery voltage thresholds */
#define VOLTAGE_FULL 2100
#define VOLTAGE_GOOD 1850
#define VOLTAGE_LOW 1700
#define VOLTAGE_CRITICAL 1650

extern bool is_charging;
extern int percentage;



/**
 * @brief Converts battery voltage (in mV) to percentage using lookup table.
 *
 * Uses linear interpolation between voltage levels to determine battery percentage.
 *
 * @param battery_mv Battery voltage in millivolts.
 * @return int Battery level in percentage (0–100).
 */
int voltage_to_percent(int battery_mv);


/**
 * @brief Performs battery monitoring and updates display with battery status.
 *
 * - Samples battery voltage from ADC.
 * - Converts voltage to battery percentage.
 * - Checks charging status from second ADC channel.
 * - Updates global variables and display accordingly.
 */
void battery_monitor_process(void);


/**
 * @brief Initializes the ADC channels for battery monitoring.
 *
 * Verifies that each ADC channel is ready and configures them.
 * Prints error messages if initialization fails.
 */
void battery_monitor_init(void);



#ifdef __cplusplus
}
#endif

#endif // BATTERY_MONITOR_H
