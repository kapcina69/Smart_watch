# 📡 Sensor Integration: BMI160 & MAX30101 with Zephyr RTOS

This module provides driver integration and data acquisition for the **BMI160** (IMU sensor) and **MAX30101** (optical pulse sensor) on **nRF52840 DK**, using **Zephyr RTOS**.

---

## 🧠 Overview

### 🔷 BMI160
- **Manufacturer**: Bosch
- **Functionality**: 6-axis IMU (3-axis accelerometer + 3-axis gyroscope)
- **Interface**: I²C or SPI
- **Applications**: Step detection, motion tracking, gesture detection

### 🔷 MAX30101
- **Manufacturer**: Maxim Integrated
- **Functionality**: Optical heart-rate and SpO₂ sensor
- **Interface**: I²C
- **Applications**: Heart rate monitoring, SpO₂ measurement, wearable devices

---

## ⚙️ Hardware Connections

| Signal        | BMI160        | MAX30101     |
|---------------|---------------|--------------|
| VCC           | 3.3V          | 3.3V         |
| GND           | GND           | GND          |
| SDA (I²C)     | P0.26 (e.g.)  | P0.26 (e.g.) |
| SCL (I²C)     | P0.27 (e.g.)  | P0.27 (e.g.) |
| INT (optional)| Connected to GPIO for interrupts (optional)

---

## 🛠️ Zephyr Configuration

Make sure to enable and configure I²C and the required drivers in your Zephyr project's `prj.conf`:

```ini
# Enable I2C
CONFIG_I2C=y

# Enable BMI160 driver
CONFIG_SENSOR=y
CONFIG_BMI160=y
CONFIG_BMI160_TRIGGER_NONE=y  # or _THREAD/_OWN_THREAD if using interrupts

# Enable MAX30101 driver
CONFIG_MAX30101=y
CONFIG_MAX30101_TRIGGER_NONE=y
```

And add the devices to your `devicetree` (`overlay` file):

```dts
&i2c1 {
    status = "okay";

    bmi160@69 {
        compatible = "bosch,bmi160";
        reg = <0x69>;
        label = "BMI160";
        int-gpios = <&gpio0 14 GPIO_ACTIVE_HIGH>; // optional
    };

    max30101@57 {
        compatible = "maxim,max30101";
        reg = <0x57>;
        label = "MAX30101";
        int-gpios = <&gpio0 15 GPIO_ACTIVE_HIGH>; // optional
    };
};
```

---

## 📦 Usage Example

### BMI160 Sample
```c
const struct device *bmi = DEVICE_DT_GET_ONE(bosch_bmi160);

if (device_is_ready(bmi)) {
    struct sensor_value accel[3], gyro[3];

    sensor_sample_fetch(bmi);
    sensor_channel_get(bmi, SENSOR_CHAN_ACCEL_XYZ, accel);
    sensor_channel_get(bmi, SENSOR_CHAN_GYRO_XYZ, gyro);

    printk("Accel: X=%.2f Y=%.2f Z=%.2f\n", sensor_value_to_double(&accel[0]),
                                           sensor_value_to_double(&accel[1]),
                                           sensor_value_to_double(&accel[2]));
}
```

### MAX30101 Sample
```c
const struct device *pulse = DEVICE_DT_GET_ONE(maxim_max30101);

if (device_is_ready(pulse)) {
    struct sensor_value hr;

    sensor_sample_fetch(pulse);
    sensor_channel_get(pulse, SENSOR_CHAN_HEART_RATE, &hr);

    printk("Heart Rate: %.2f bpm\n", sensor_value_to_double(&hr));
}
```

---

## 📊 Output Format

Example serial output:
```
Accel: X=0.12 Y=-0.01 Z=9.80
Gyro:  X=0.05 Y=0.02 Z=0.01
Heart Rate: 72.00 bpm
```

---

## 🧩 Integration Notes

- Use appropriate `devicetree overlays` for your board.
- For best accuracy with MAX30101, place finger firmly over sensor, and use digital averaging.
- BMI160 can also be configured for step counting with additional logic.
- Power consumption optimization can be achieved by controlling sample rate and enabling low-power modes.

---

---

## 📚 References

- [Zephyr Sensor API Docs](https://docs.zephyrproject.org/latest/reference/peripherals/sensor.html)
- [BMI160 Datasheet – Bosch](https://www.bosch-sensortec.com/products/motion-sensors/imus/bmi160/)
- [MAX30101 Datasheet – Maxim Integrated](https://www.analog.com/media/en/technical-documentation/data-sheets/MAX30101.pdf)