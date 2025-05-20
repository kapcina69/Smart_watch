#ifndef BLE_NUS_H
#define BLE_NUS_H

#include <zephyr/kernel.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <bluetooth/services/nus.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Callback function to handle Bluetooth events.
 * 
 * @param err 
 */
void bt_ready(int err);

/**
 * @brief Callback function for connection events.
 * 
 * @param conn 
 * @param err 
 */
void connected(struct bt_conn *conn, uint8_t err);

/**
 * @brief Callback function for disconnection events.
 * 
 * @param conn 
 * @param reason 
 */
void disconnected(struct bt_conn *conn, uint8_t reason);

/**
 * @brief Initializes the Bluetooth Low Energy (BLE) NUS service.
 * 
 * @return int 
 */
int ble_nus_init(void);

/**
 * @brief Sends heart rate and step data over BLE.
 * 
 * @param heart_rate 
 * @param steps 
 * @return int 
 */
int ble_nus_send_data(int heart_rate, uint32_t steps);

#ifdef __cplusplus
}
#endif

#endif /* BLE_NUS_H */