# 💪 Fitness Tracker With BLE & Real-Time LVGL GUI

A real-time fitness tracker application developed for the **nRF52840 DK**, utilizing **Zephyr RTOS**, **LVGL**, and multiple sensors to track heart rate, steps, and synchronize data over BLE. The project showcases a fully embedded graphical application with live sensor data visualization and Bluetooth communication to a mobile app.

---

## 🚀 Features

- ✅ **Live heart rate monitoring** via **MAX30102** optical sensor
- ✅ **Step counting** using **BMI160** 6-axis motion sensor
- ✅ **Real-time GUI** with **LVGL** on 0.91" OLED display (SSD1306, 128x32)
- ✅ **BLE communication** using **Nordic UART Service (NUS)**
- ✅ **Time synchronization** from mobile phone to MCU
- ✅ **Watchdog timer** for system reliability
- ✅ Modular code structure for easy scaling

---

## 🛠 Hardware

| Component           | Description                                     |
|---------------------|-------------------------------------------------|
| **MCU**             | Nordic nRF52840 DK                              |
| **Display**         | OLED 0.91", SSD1306, 128x32                     |
| **Accelerometer**   | BMI160 (I2C) or LSM6DSO                          |
| **Pulse Sensor**    | MAX30102 (I2C)                                   |
| **Power**           | USB or battery (optional, via DK's headers)     |

---

## 📷 Screenshots

![LVGL GUI Example](https://user-images.githubusercontent.com/your_screenshot_placeholder)

---

## 📦 Software Stack

- **Zephyr RTOS**
- **LVGL** (GUI library)
- **Nordic UART Service (NUS)** for BLE
- **I2C drivers** for BMI160 and MAX30102
- **Custom LVGL UI** for displaying live data

---

## 🔄 BLE Communication

- Uses **Nordic UART Service** (NUS)
- Sends heart rate and step data periodically to a mobile app
- Receives **time synchronization** commands (e.g., from nRF Toolbox or custom app)
- Compatible with **MIT App Inventor apps** and **custom Android apps**

### 🖥 Requirements

- Zephyr SDK (version 3.7)
- ncs (2.9.1)
- West build system
- Python dependencies (requirements.txt from Zephyr)
- OLED connected via I2C
- Sensors connected on appropriate I2C bus (check overlay)

📱 Android App (BLE Sync)
A companion Android app (optional) receives HR and step data and can send the current time to synchronize the MCU clock.

Option 1: nRF Toolbox → UART → send TIME:...

Option 2: Your own app made in MIT App Inventor

Option 3: Native Android App with BLE API (WIP)



🧠 Future Improvements
 Add SpO2 calculation from MAX30102

 Add battery monitoring

 Extend UI to include graph view of HR data

 Store data in flash memory for history view

 Add BLE pairing and authentication



🙋‍♂️ Author
Luka Smolović
School of Electrical Engineering (ETF), University of Belgrade
GitHub: @kapcina69


🤝 Contributions
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change or improve.
