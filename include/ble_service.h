#ifndef BLE_SERVICE_H
#define BLE_SERVICE_H

#include <zephyr/types.h>



/**
 * @brief Initializes the Bluetooth Low Energy (BLE) service.
 * 
 * @param callback 
 */
void ble_init(void (*callback)(const char *));


/**
 * @brief Sends heart rate and step data over BLE.
 * 
 * @param heart_rate 
 * @param steps 
 */
void ble_send_data(int heart_rate, uint32_t steps);


/**
 * @brief Sends a string message over BLE.
 * 
 * @param message 
 */
void ble_send_string(const char *message);
#endif // BLE_SERVICE_H