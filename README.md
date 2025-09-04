# 2DoFarmgripper
2025/2026 UGMURO Practical Work Assignment for 2 DOF Robot Arm Control Project

---

## Arduino Uno

### Pinouts

**Joystick**
- X axis                   : A0
- Y axis                   : A1
- Button (Record and Save) : D2

**Button**
- Play                     : D3

**Servo Data Pins**
- Base                     : D9
- Shoulder                 : D10

---

## ESP32 (with LittleFS)

### Pinouts

**Joystick**
- X axis                   : A0
- Y axis                   : A1
- Button (Record and Save) : D2

**Button**
- Play                     : D3

**Servo Data Pins**
- Base                     : D9
- Shoulder                 : D10

---

## Features
- 2 DOF Robot Arm (Base + Shoulder)
- Joystick control (Arduino Uno or ESP32)
- Record and Playback functionality
- ESP32 version hosts a web control interface using LittleFS
- Servo movement smoothing for realistic motion

---

## Notes
- Use an external 5V supply for servos (do not power directly from the board).
- Always connect servo GND with board GND (common ground).
- ESP32 requires LittleFS plugin to upload HTML files for web control.
