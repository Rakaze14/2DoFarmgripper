# 2DoFarmgripper  

Praktikum Robotika 2025/2026 — UGMURO 

A **2-DOF robot arm** project with record & playback functionality.  
Supports both **Arduino Uno** (joystick-based control) and **ESP32** (web-based control using LittleFS).  

---

## 🔹 Control
- **2 Degrees of Freedom (DOF):**
  - Base rotation  
  - Shoulder movement  
- **Joystick control** (Arduino Uno)  
- [**Record & Playback**](https://github.com/Rakaze14/2DoFarmgripper/blob/main/basicrecordplay.ino) system:
  - Press joystick button → start/stop recording  
  - Press Play button → replay saved motion  
- [**Web control (ESP32 only)](https://github.com/Rakaze14/2DoFarmgripper/blob/main/webcontrol.ino):**
  - Slider-based interface via Wi-Fi  
  - [HTML](https://github.com/Rakaze14/2DoFarmgripper/blob/main/data/index.html) interface hosted with LittleFS  

---

## 🔹 Hardware Requirements
- Arduino Uno **and** ESP32  
- 2x Servo motors (Base + Shoulder)  
- Joystick module (X, Y, Button) (for record & play)
- Push button (Play control) (for record & play) 
- External 5V power supply for servos (recommended)  
- Breadboard & jumper wires  

---

## 🔹 Pinout Reference

### Arduino Uno
| Component          | Pin  |
|--------------------|------|
| Joystick X-axis    | A0   |
| Joystick Y-axis    | A1   |
| Joystick Button    | D2   |
| Play Button        | D3   |
| Servo Base         | D9   |
| Servo Shoulder     | D10  |

### ESP32 (with LittleFS)
| Component          | Pin  |
|--------------------|------|
| Servo Base         | 18   |
| Servo Shoulder     | 19   |

---

## 🔹 Software Setup

### Arduino Uno
1. Install [Arduino IDE](https://www.arduino.cc/en/software)  
2. Select **Arduino Uno** board  
3. Upload the Arduino sketch [(`basicrecordplay.ino`)](https://github.com/Rakaze14/2DoFarmgripper/blob/main/basicrecordplay.ino)  
4. Connect joystick + buttons + servos as per pinout  

### ESP32 (Web Control with LittleFS)
1. Install [Arduino IDE](https://www.arduino.cc/en/software)  
2. Install ESP32 board support via Board Manager  
3. Install **ESP32 LittleFS plugin**:  
   - [LittleFS plugin installation guide](https://github.com/lorol/arduino-esp32fs-plugin)  
4. Create `data/` folder in sketch directory  
5. Place [`index.html`](https://github.com/Rakaze14/2DoFarmgripper/blob/main/data/index.html) inside `data/`  
6. Upload filesystem (Tools → ESP32 Data Upload)  
7. Upload the Arduino sketch [(`webcontrol.ino`)](https://github.com/Rakaze14/2DoFarmgripper/blob/main/webcontrol.ino)  
8. Open Serial Monitor to find ESP32 IP  
9. Access ESP32 IP in browser → control robot arm via sliders 🚀  

---

## 🔹 Notes
- Use a **separate 5V supply for servos** (not from Arduino/ESP32 board) to avoid resets.  
- Always connect **GND of servo power and board together** (common ground).  
- Adjust servo range in code if your servos don’t rotate properly.  

---

## 📜 License
MIT License — feel free to use and modify.  
