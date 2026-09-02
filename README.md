# 🌡️ Time-Stamped Sensor Data Logger

---

## 📌 Project Overview

The **Time-Stamped Sensor Data Logger** is an intelligent embedded system designed using the LPC2129 ARM7 microcontroller. It continuously monitors ambient temperature using an LM35 temperature sensor and obtains accurate timestamp information—including time, date, day, month, and year—from the on-chip Real-Time Clock (RTC). 

The system displays live temperature and RTC information on a 16×2 LCD. When the measured temperature exceeds a user-configured limit, the system activates an LED alert and transmits the temperature data along with complete RTC details to a PC through the UART protocol. The received data is stored in a text file using the HyperTerminal application. 

A keypad and external interrupt button are used to configure the RTC values and temperature threshold.

---

## 🎯 Objectives
| Objective | Description |
|---|---|
| 🌡 Temperature Monitoring | Measure real-time ambient temperature using LM35 |
| 🕒 RTC Monitoring | Read and display time, date, day, month, and year |
| 📺 LCD Display | Display temperature and RTC information |
| 🚨 Over-Temperature Detection | Detect when temperature exceeds a configured limit |
| 💻 UART Data Transmission | Send alert data to a PC through UART |
| 📄 Text File Logging | Store received alert data using HyperTerminal |
| ⌨️ User Configuration | Set RTC values and temperature limit using keypad |
| ⚡ Interrupt-Based Menu | Open the configuration menu using external interrupt |
---

## 🧰 Hardware Components

| Component | Quantity | Purpose |
|---|---:|---|
| LPC2129 ARM7 MCU | 1 | controller |
| LM35 Temperature Sensor | 1 | Measures ambient temperature |
| 16×2 LCD | 1 | Displays temperature and RTC values |
| 4×4 Matrix Keypad | 1 | Configures time, date, and threshold |
| LED | 1 | Over-temperature indication |
| Push Button | 1 | External interrupt trigger |
| UART-to-PC Interface | 1 | Serial communication with PC |
| Crystal Oscillator | 1 | Provides MCU clock |
| 5 V / 3.3 V Power Supply | 1 | System power |

---

## 💻 Software Requirements

| Software | Purpose |
|---|---|
| Keil µVision | Embedded C firmware development |
| Proteus | Circuit simulation |
| Flash Magic | Program download to LPC2129 |
| HyperTerminal | UART monitoring and text-file logging |
| Embedded C | Programming language |

---

## Block Diagram

<img width="1536" height="1024" alt="image" src="https://github.com/user-attachments/assets/42a2c60c-501a-4f88-8252-23c1ac85958f" />

---

## 🔄 System Working Flow

<img width="1024" height="1536" alt="image" src="https://github.com/user-attachments/assets/32923b85-dded-4a17-a7f7-945407c0094b" />

---

## 🧾 Configuration Menu

```
1. Edit RTC
2. Set Temperature Limit
3. Save Settings
4. Exit
```
---

## 📷 Project Output

| Module | Output |
|---|---|
| LM35 Sensor | Measures ambient temperature |
| RTC | Provides time, date, day, month, and year |
| LCD | Displays temperature and RTC data |
| LED | Turns ON when temperature exceeds the limit |
| UART | Sends over-temperature alert data to PC |
| HyperTerminal | Receives and stores data in a text file |
| Keypad | Configures RTC and temperature threshold |
| External Interrupt | Opens configuration menu |

https://github.com/user-attachments/assets/f9624b40-62b6-4226-bd46-7dab133c34a6

---

## ⭐ Key Features

| Feature | Description |
|---|---|
| Real-Time Temperature Monitoring | Continuous LM35-based temperature sensing |
| Complete RTC Timestamp | Logs time, date, day, month, and year |
| Conditional UART Logging | Sends data to PC only during over-temperature condition |
| HyperTerminal File Storage | Saves received UART alerts as a text file |
| LCD | Displays live temperature and RTC details |
| LED Warning | Provides local visual alert |
| Adjustable Temperature Limit | User-configurable alert threshold |
| Interrupt-Based Configuration | Fast access to system settings |

---

## 🚀 Advantages

| Benefit | Description |
|---|---|
| Accurate Monitoring | Continuously measures ambient temperature using LM35. |
| Time-Stamped Logging | Records temperature with RTC time, date, day, month, and year. |
| Automatic Alert | LED activates when temperature exceeds the configured limit. |
| PC Data Storage | UART sends alert data to HyperTerminal, which stores it in a text file. |
| Configurable System | Temperature limit and RTC values can be set using the keypad. |

---
## 🚀 Applications
- 🏭 Industrial machine temperature monitoring
- 🧪 Laboratory equipment monitoring
- 🌱 Environmental monitoring
- ❄️ Cold-storage temperature monitoring
- 🔥 Overheat detection systems
- 📦 Warehouse condition monitoring
- 🎓 Embedded systems education
  
## 🔮 Future Enhancements
- 💾 SD-card data logging
- 🌐 IoT cloud dashboard integration
- 📱 Mobile alert notifications
- 🔔 Buzzer-based alarm
- 📈 PC-based graphical temperature analysis
- 🌡️ Multi-sensor monitoring
- 📧 Email or SMS warning system
- 🔋 RTC battery backup

---

📂 Project Folder Structure
Time-Stamped-Sensor-Data-Logger/\
│\
├── main.c\
├── adc.c\
├── rtc.c\
├── uart.c\
├── lcd.c\
├── keypad.c\
├── interrupt.c\
├── gpio.c\
│\
├── include/\
│   ├── adc.h\
│   ├── rtc.h\
│   ├── uart.h\
│   ├── lcd.h\
│   ├── keypad.h\
│   └── gpio.h\
│\
├── README.md\
└── LICENSE\

---

## 📌 Conclusion

The Time-Stamped Sensor Data Logger provides an efficient solution for temperature monitoring and over-temperature event logging. When the temperature crosses the configured limit, the system captures temperature and complete RTC data, sends it to a PC using UART, and stores it as a text file through HyperTerminal. This makes the project useful for temperature-sensitive industrial, laboratory, environmental, and educational applications.

---

👨‍💻 Developed & Implemented By

🏆 **Uppalapati Durga Madan**

🆔 Vector ID: V25he4u2

🎓 Embedded Systems Trainee | Vector India
