#2DoFarmgripper

Practical Work Assignment 2025/2026 — UGMURO
A 2-DOF robot arm project with record & playback functionality.
Supports both Arduino Uno (joystick-based control) and ESP32 (web-based control using LittleFS).

🔹 Features

2 Degrees of Freedom (DOF):

Base rotation

Shoulder movement

Joystick control (Arduino Uno or ESP32)

Record & Playback system:

Press joystick button → start/stop recording

Press Play button → replay saved motion

Web control (ESP32 only):

Slider-based interface via Wi-Fi

HTML interface hosted with LittleFS

🔹 Hardware Requirements

Arduino Uno or ESP32

2x Servo motors (Base + Shoulder)

Joystick module (X, Y, Button)

Push button (Play control)

External 5V power supply for servos (recommended)

Breadboard & jumper wires

🔹 Pinout Reference
Arduino Uno
Component	Pin
Joystick X-axis	A0
Joystick Y-axis	A1
Joystick Button	D2
Play Button	D3
Servo Base	D9
Servo Shoulder	D10
ESP32 (with LittleFS)
Component	Pin
Joystick X-axis	A0
Joystick Y-axis	A1
Joystick Button	D2
Play Button	D3
Servo Base	D9
Servo Shoulder	D10
🔹 Software Setup
Arduino Uno

Install Arduino IDE
.

Select Arduino Uno board.

Upload the Arduino sketch (uno_2dof.ino).

Connect joystick + buttons + servos as per pinout.

ESP32 (Web Control with LittleFS)

Install Arduino IDE
.

Install ESP32 board support via Board Manager.

Install ESP32 LittleFS plugin:

LittleFS plugin installation guide

Create data/ folder in sketch directory.

Place index.html inside data/.

Upload filesystem (Tools → ESP32 Data Upload).

Upload esp32_2dof.ino.

Open Serial Monitor to find ESP32 IP.

Access ESP32 IP in browser → control robot arm via sliders.

🔹 Project Demo

🎮 Joystick control (record & playback)

🌐 Web sliders on ESP32 (hosted via LittleFS)

💾 Record motion and replay anytime

🔹 Notes

Use a separate 5V supply for servos (not from Arduino/ESP32 board) to avoid resets.

Always connect GND of servo power and board together (common ground).

Adjust servo range in code if your servos don’t rotate properly.

📜 License

MIT License — feel free to use and modify.
