#ifndef BMI160_H_
#define BMI160_H_

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>

#define BMI160_I2C_ADDR 0x69
#define BMI160_REG_ACC_X_LSB 0x12
#define BMI160_REG_ACC_X_MSB 0x13
#define BMI160_REG_ACC_Y_LSB 0x14
#define BMI160_REG_ACC_Y_MSB 0x15
#define BMI160_REG_ACC_Z_LSB 0x16
#define BMI160_REG_ACC_Z_MSB 0x17

extern bool change_display_by_accel;
extern bool enable_change_display_by_accel;
extern uint16_t display_state;


/**
 * @brief Enable the step counter.
 * 
 * This function initializes the BMI160 sensor and enables the step counter.
 * 
 * @return int 
 */
int bmi160_enable_step_counter(void);


/**
 * @brief Read the step count from the BMI160 sensor.
 * 
 * This function reads the step count from the BMI160 sensor and stores it in the provided pointer.
 * 
 * @param steps 
 * @return int 
 */
int bmi160_read_step_count(uint16_t *steps);

/**
 * @brief Reset the step counter.
 * 
 * This function resets the step counter on the BMI160 sensor.
 * Reset happens when new day starts.
 * 
 * @return int 
 */
int bmi160_reset_step_counter(void);
int bmi160_read_accel(int16_t *x, int16_t *y, int16_t *z);

#endif // BMI160_H_