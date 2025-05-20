#ifndef MAX30101_H
#define MAX30101_H

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>

#define MAX30101_I2C_ADDR 0x57

// Essential registers
enum {
    REG_INTR_STATUS_1 = 0x00,
    REG_FIFO_WR_PTR = 0x04,
    REG_FIFO_RD_PTR = 0x06,
    REG_FIFO_DATA = 0x07,
    REG_FIFO_CONFIG = 0x08,
    REG_MODE_CONFIG = 0x09,
    REG_SPO2_CONFIG = 0x0A,
    REG_LED1_PA = 0x0C,
    REG_LED2_PA = 0x0D,
    REG_MULTI_LED_CTRL1 = 0x11,
    REG_REV_ID = 0xFE,
    REG_PART_ID = 0xFF
};

// Configuration constants
#define FIFO_ALMOST_FULL  0x0F
#define SPO2_MODE         0x03
#define SAMPLE_RATE_100HZ 0x07
#define LED_PULSE_WIDTH_16BIT 0x03
#define LED_CURRENT_37MA  0x24

#define BUFFER_SIZE 500

// Function prototypes


/**
 * @brief Initializes the MAX30101 sensor.
 * 
 * This function configures the MAX30101 sensor for operation.
 * It sets the mode, sample rate, LED current, and other parameters.
 * 
 * @param i2c_dev 
 * @return int 
 */
int max30101_init(const struct device *i2c_dev);



/**
 * @brief Reads a sample from the MAX30101 sensor.
 * 
 * This function reads a sample from the MAX30101 sensor and stores it in the provided buffer.
 * It also handles the FIFO buffer and ensures that the data is valid.
 * 
 * @param ir 
 * @return int 
 */
int max30101_read_ir_sample(uint32_t *ir);



/**
 * @brief Counts the number of peaks in the provided samples.
 * 
 * This function analyzes the provided samples and counts the number of peaks.
 * It uses a simple thresholding algorithm to identify peaks.
 * 
 * @param samples 
 * @param count 
 * @return int 
 */
int count_peaks(uint32_t *samples, int count);

#endif // MAX30101_H