
---

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

- **📶 Wireless Connectivity**  
  - BLE data sync via **Nordic UART Service (NUS)**  
  - Time synchronization from mobile app to MCU  

- **⚙️ System Reliability**  
  - Watchdog timer for crash recovery  
  - Modular firmware design for scalability  

---

## 🛠 Hardware Setup  

| Component         | Protocol/Interface  | Details                      |  
|-------------------|---------------------|------------------------------|  
| **MCU**           | nRF52840 DK         | ARM Cortex-M4F, BLE 5.0      |  
| **Display**       | I²C (GC9A01)        | TFT LCD Round RGB 240 * 240  |  
| **Motion Sensor** | I²C (BMI160/LSM6DSO)| 6-axis accelerometer + gyro  |  
| **Pulse Sensor**  | I²C (MAX30102)      | Heart rate + SpO² (future)   |  
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

### Compatibility:  
1. **nRF Toolbox** (UART mode)  
2. **MIT App Inventor** (custom BLE app)  
3. **Native Android App** (WIP, uses BLE API)  

---

## 🖼️ Screenshots  

(![Preview](./images/background1.png)
)  
 *(Example: Live heart rate and step counter display)*  

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
- [ ] **Battery Monitoring**  
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

---

### Key Improvements:  
1. **Structured Sections**: Clearer separation of features, hardware, and software.  
2. **Concise Tables**: Hardware details in an easy-to-read format.  
3. **Future Plans**: Moved to a dedicated section for better visibility.  
4. **Build Instructions**: Added quick-start commands.  
5. **Consistent Formatting**: Emojis for visual cues, bullet points for readability.  