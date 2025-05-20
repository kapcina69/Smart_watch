#ifndef BMI160_H_
#define BMI160_H_

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>

#define BMI160_I2C_ADDR 0x69

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

#endif // BMI160_H_