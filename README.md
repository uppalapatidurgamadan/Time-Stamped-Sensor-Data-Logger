🌡️ Time-Stamped Sensor Data Logger

⏱️ Real-Time Temperature Monitoring • RTC-Based Data Logging • UART Communication

---

🧠 Project Overview

**Time-Stamped Sensor Data Logger** is an intelligent embedded system that continuously monitors ambient temperature using an **LM35 sensor** and records it with accurate **date and time** using the **Real-Time Clock (RTC)**. By integrating **ADC, RTC, UART, LCD, and interrupt-based configuration**, the system enables real-time monitoring, timestamped data logging, and automatic over-temperature alerts, making it suitable for environmental and industrial monitoring applications.

---

🎯 AIM

To design an embedded system that accurately monitors temperature, records timestamped sensor data, and generates alerts when the temperature exceeds a predefined threshold.

---

⭐ Key Objectives

🔸 Monitor real-time temperature using the LM35 sensor

🔸 Display current date, time, and temperature on a 16×2 LCD

🔸 Log timestamped temperature data through UART

🔸 Generate an LED alert for over-temperature conditions

🔸 Configure date, time, and temperature threshold using a keypad

---

🔥 Features at a Glance

| 🚀 **Feature**             | 📝 **Description**                          |
| -------------------------- | ------------------------------------------- |
| 🌡️ Temperature Monitoring | Reads real-time temperature using LM35      |
| 🕒 RTC Display             | Displays current date and time continuously |
| 📺 LCD Display             | Shows temperature, date, and time           |
| 💻 UART Logging            | Sends timestamped data to Virtual Terminal  |
| 🚨 Over-Temperature Alert  | Turns ON LED when threshold is exceeded     |
| ⌨️ Keypad Configuration    | Edit RTC and threshold values               |
| ⚡ External Interrupt       | Opens configuration menu instantly          |

---

📌 Working Flow

**1️⃣ Power ON** → Initialize LCD, ADC, RTC, UART, and GPIO

**2️⃣ RTC continuously updates** current date and time 🕒

**3️⃣ LM35 measures** ambient temperature 🌡️

**4️⃣ ADC converts** analog temperature into digital data

**5️⃣ LCD displays** date, time, and temperature 📺

**6️⃣ UART logs** timestamped temperature readings 💻

**7️⃣ If temperature exceeds the preset threshold**

  ✔ LED turns ON 🚨

  ✔ Over-temperature alert is generated

**8️⃣ External Interrupt** opens the configuration menu 🔘

  ➤ Edit Date & Time

  ➤ Change Temperature Threshold

  ➤ Save Settings

  ➤ Exit

---

🧾 Configuration Menu

```
1. Edit RTC
2. Set Temperature Limit
3. Save Settings
4. Exit
```

---

🛠 Hardware Requirements

🔹 LPC2124 ARM7 Microcontroller

🔹 LM35 Temperature Sensor

🔹 16×2 LCD Display

🔹 4×4 Matrix Keypad

🔹 LED

🔹 Push Button (External Interrupt)

🔹 UART Virtual Terminal

---

💻 Software Requirements

🛠 Embedded C

🛠 Keil µVision

🛠 Proteus

---

📷 Project Output

https://github.com/user-attachments/assets/f9624b40-62b6-4226-bd46-7dab133c34a6

---

📌 Conclusion

The **Time-Stamped Sensor Data Logger** provides an efficient solution for real-time temperature monitoring and timestamped data logging. By combining **ADC-based sensing, RTC timekeeping, UART communication, and interrupt-driven configuration**, the system ensures accurate data acquisition, continuous monitoring, and timely over-temperature alerts. Its simple design and reliable operation make it suitable for laboratory experiments, industrial monitoring, environmental sensing, and embedded systems learning.

---

👨‍💻 Developed & Implemented By

🏆 **Uppalapati Durga Madan**

🆔 Vector ID: V25he4u2

🎓 Embedded Systems Trainee | Vector India
