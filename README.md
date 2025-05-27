
# 💪 Fitness Tracker with BLE & Real-Time LVGL GUI

A real-time fitness tracker application for the **nRF52840 DK**, leveraging **Zephyr RTOS**, **LVGL**, and multiple sensors to monitor heart rate, steps, and sync data via BLE. Features a responsive embedded GUI with live data visualization and Bluetooth communication to a mobile app.

---

## 🚀 Key Features

- **📊 Live Health Monitoring**
  - Heart rate tracking via **MAX30102** optical sensor
  - Step counting using **BMI160** 6-axis motion sensor

- **🖥️ Interactive GUI**
  - Real-time display on **RGB TFT LCD (GC9A01, 240×240)**
  - Built with **LVGL** for smooth animations and widgets
  - 🔄 **Display Switching on Wrist Flick** *(optional feature)*

- **📶 Wireless Connectivity**
  - BLE data sync via **Nordic UART Service (NUS)**
  - Time and date synchronization from mobile app to MCU
  - BLE commands to control UI and features remotely

- **🔔 Haptic Feedback**
  - Vibration motor feedback when:
    - Charging is connected
    - Bluetooth is enabled
    - Screen is changed

- **⚙️ System Reliability**
  - Watchdog timer for crash recovery
  - Modular firmware design for scalability

---

## 🛠 Hardware Setup

| Component         | Protocol/Interface  | Details                      |
|------------------|---------------------|------------------------------|
| **MCU**           | nRF52840 DK         | ARM Cortex-M4F, BLE 5.0      |
| **Display**       | I²C (GC9A01)        | TFT LCD Round RGB 240×240    |
| **Motion Sensor** | I²C (BMI160/LSM6DSO)| 6-axis accelerometer + gyro  |
| **Pulse Sensor**  | I²C (MAX30102)      | Heart rate + SpO² (future)   |
| **Vibration Motor**| GPIO               | Haptic feedback events       |
| **Power**         | USB / Battery       | 3.7V **LiPo 402025** via DK headers |

---

## 📦 Software Stack

- **OS**: Zephyr RTOS (v3.7)
- **GUI**: LVGL (embedded graphics library)
- **BLE**: Nordic UART Service (NUS)
- **Drivers**:
  - I²C for sensors (MAX30102, BMI160)
  - Custom LVGL widgets for data visualization

---

## 🔄 BLE Communication

### 📱 Mobile App Integration
- **Data Stream**: Heart rate and steps sent periodically via NUS.
- **Time Sync**: Mobile app sends `TIME:HH:MM:SS` to update MCU clock.
- **Date-Time Sync**: New command `DATETIME:DD-MM-YYYY HH:MM:SS` sets both date and time.

### 🧭 BLE Commands

| Command               | Description                                       |
|------------------------|---------------------------------------------------|
| `watchface1`          | Switch to default watchface                      |
| `w1hr`                | Watchface 1 with heart rate monitor              |
| `w1steps`             | Watchface 1 with steps monitor                   |
| `enablecd`            | Enable **wrist flick gesture** to change screen  |
| `disablecd`           | Disable wrist-based display switching            |
| `DD-MM-YYYY HH:MM:SS` | Set date and time on device             |

### Compatibility:
1. **nRF Toolbox** (UART mode)
2. **MIT App Inventor** (custom BLE app)
3. **Native Android App** (WIP, uses BLE API)

---

## ✋ Display Change on Wrist Flick

This feature allows changing the display screen by flicking your wrist, using the onboard accelerometer to detect motion.

- **Enable via BLE**: `enablecd`
- **Disable via BLE**: `disablecd`
- Internally uses accelerometer interrupt/motion threshold to trigger screen transitions.

---

## 🖼️ Screenshots

![Preview](./images/watchface1.jpg)

 *(Live heart rate and step counter display)*

 ![Preview](./images/heart_rate_monitor.jpg)

 *(Heart rate monitor)*

 ![Preview](./images/step_counter_monitor.jpg)

*(Step counter monitor)*


---

## 🔧 Build & Deployment

### Prerequisites:
- Zephyr SDK (v3.7) + nRF Connect SDK (v2.9.1)
- West build system
- Python dependencies (`requirements.txt`)

### Flashing:
```sh
west build -b nrf52840dk_nrf52840
west flash
```

---

## 🧠 Future Roadmap

- [ ] **SpO² Estimation** (MAX30102)
- [ ] **Data Logging** (Flash storage)
- [ ] **Enhanced UI** (Graphs, history view)
- [ ] **Secure BLE Pairing**

---

## 👨‍💻 Author & Contributions

**Luka Smolović**
- School of Electrical Engineering (ETF), University of Belgrade
- GitHub: [@kapcina69](https://github.com/kapcina69)

**🤝 Open for Collaborations!**
PRs welcome! For major changes, open an issue first.