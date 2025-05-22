#include "bmi160.h"
#include "display_ili9341.h"
#include <zephyr/drivers/i2c.h>
#include <zephyr/sys/printk.h>
#include <zephyr/devicetree.h>

/* BMI160 Step Counter Registers */
#define BMI160_REG_STEP_CNT0      0x78
#define BMI160_REG_STEP_CNT1      0x79
#define BMI160_REG_STEP_CONF0     0x7A
#define BMI160_REG_STEP_CONF1     0x7B
#define BMI160_REG_CMD            0x7E
#define BMI160_CMD_FIFO_FLUSH     0xB0

bool change_display_by_accel = false;
bool enable_change_display_by_accel = true; // Flag to enable/disable display change by accelerometer
uint16_t display_state = 0; // Default watchface state


/* I2C device node - prilagodi ako koristiš drugi i2c kontroler */
#define i2c_dev_NODE DT_NODELABEL(i2c0)
const struct device *const i2c_dev2 = DEVICE_DT_GET(i2c_dev_NODE);
int bmi160_read_step_count(uint16_t *steps)
{
    uint8_t buf[2];
    int ret;

    if (!device_is_ready(i2c_dev2)) {
        printk("I2C device not ready!\n");
        return -ENODEV;
    }

    ret = i2c_burst_read(i2c_dev2, BMI160_I2C_ADDR,
                         BMI160_REG_STEP_CNT0, buf, sizeof(buf));
    if (ret) {
        printk("Failed to read step count (err %d)\n", ret);
        return ret;
    }

    *steps = (buf[1] << 8) | buf[0];
    return 0;
}

int bmi160_enable_step_counter(void)
{
    uint8_t step_conf0 = 0x15;  // Default config
    uint8_t step_conf1 = 0x0b;  // Enable step counter

    if (!device_is_ready(i2c_dev2)) {
        printk("I2C device not ready!\n");
        return -ENODEV;
    }

    int ret = i2c_reg_write_byte(i2c_dev2, BMI160_I2C_ADDR,
                                 BMI160_REG_STEP_CONF0, step_conf0);
    if (ret) {
        printk("Failed to write STEP_CONF0 (err %d)\n", ret);
        return ret;
    }

    ret = i2c_reg_write_byte(i2c_dev2, BMI160_I2C_ADDR,
                             BMI160_REG_STEP_CONF1, step_conf1);
    if (ret) {
        printk("Failed to write STEP_CONF1 (err %d)\n", ret);
        return ret;
    }

    printk("Step counter enabled and configured\n");
    return 0;
}


int bmi160_reset_step_counter(void)
{
    uint8_t step_conf1 = 0x0b;  // Enable step counter
    if (!device_is_ready(i2c_dev2)) {
        printk("I2C device not ready!\n");
        return -ENODEV;
    }

    int ret = i2c_reg_write_byte(i2c_dev2, BMI160_I2C_ADDR,
                                 BMI160_REG_STEP_CONF1, 0x03);
    if (ret) {
        printk("Failed to reset step counter (err %d)\n", ret);
        return ret;
    }
    ret = i2c_reg_write_byte(i2c_dev2, BMI160_I2C_ADDR,
        BMI160_REG_STEP_CONF1, step_conf1);
    if (ret) {
    printk("Failed to write STEP_CONF1 (err %d)\n", ret);
    return ret;
    }

    printk("Step counter reset (FIFO flushed)\n");

    return 0;
}


#include <math.h>  // Dodaj ovo za sqrtf()


int bmi160_read_accel(int16_t *x, int16_t *y, int16_t *z)
{
    uint8_t buf[6];
    int ret;

    if (!device_is_ready(i2c_dev2)) {
        printk("I2C device not ready!\n");
        return -ENODEV;
    }

    ret = i2c_burst_read(i2c_dev2, BMI160_I2C_ADDR,
                         BMI160_REG_ACC_X_LSB, buf, sizeof(buf));
    if (ret) {
        printk("Failed to read accel data (err %d)\n", ret);
        return ret;
    }

    *x = (int16_t)((buf[1] << 8) | buf[0]);
    *y = (int16_t)((buf[3] << 8) | buf[2]);
    *z = (int16_t)((buf[5] << 8) | buf[4]);

    int total = (int)sqrtf((*x) * (*x) + (*y) * (*y) + (*z) * (*z));
    if(enable_change_display_by_accel){
        
        if (total > 25000) {
            change_display_by_accel = true;
            printk("Change display by accel\n");
            
            
        } else {
            change_display_by_accel = false;
            printk("Don't change display by accel\n");
        }
        printk("Accel X: %d, Y: %d, Z: %d, Total: %d\n", *x, *y, *z, total);
        if(display_state==0 && change_display_by_accel){
            display_state = 1;
            change_display_by_accel = false;
            watchfacehr();
            printk("Display state: w1hr\n");
        }
        else if(display_state==1 && change_display_by_accel){
            display_state = 2;
            change_display_by_accel = false;
            watchfacesteps();
            printk("Display state: w1steps\n");
        }else if(display_state==2 && change_display_by_accel){
            display_state = 0;
            change_display_by_accel = false;
            watchface1();
            printk("Display state: watchface1\n");
        }
    }


    return 0;
}


