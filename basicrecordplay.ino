#include <Servo.h>

Servo baseServo;
Servo shoulderServo;

const int joyX = A0;    
const int joyY = A1;    
const int joyBtn = 2;   
const int playBtn = 3; 

const int baseServoPin = 9;
const int shoulderServoPin = 10;

const int MAX_STEPS = 200;
int basePos[MAX_STEPS];
int shoulderPos[MAX_STEPS];
int stepCount = 0;

// State
bool recording = false;
bool lastJoyBtnState = HIGH;

// Last Position
int currentBase = 90;
int currentShoulder = 90;

// smooth
void smoothMove(Servo &servo, int &currentPos, int target, int stepDelay) {
  if (target > currentPos) {
    for (int pos = currentPos; pos <= target; pos++) {
      servo.write(pos);
      delay(stepDelay);
    }
  } else if (target < currentPos) {
    for (int pos = currentPos; pos >= target; pos--) {
      servo.write(pos);
      delay(stepDelay);
    }
  }
  currentPos = target;
}

void setup() {
  baseServo.attach(baseServoPin);
  shoulderServo.attach(shoulderServoPin);

  pinMode(joyBtn, INPUT_PULLUP);
  pinMode(playBtn, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println("System Start");
}

void loop() {
  // --- Joystick input ---
  int joyValX = analogRead(joyX);
  int joyValY = analogRead(joyY);

  // Mapping
  int targetBase = map(joyValX, 0, 1023, 0, 180);
  int targetShoulder = map(joyValY, 0, 1023, 0, 180);

  // Smooth
  smoothMove(baseServo, currentBase, targetBase, 2);
  smoothMove(shoulderServo, currentShoulder, targetShoulder, 2);

  // Record Toogle
  bool joyBtnState = digitalRead(joyBtn);
  if (joyBtnState == HIGH && lastJoyBtnState == LOW) {
    recording = !recording;
    if (recording) {
      stepCount = 0;
      Serial.println("Recording started...");
    } else {
      Serial.print("Recording stopped. Steps saved: ");
      Serial.println(stepCount);
    }
    delay(300); // debounce
  }
  lastJoyBtnState = joyBtnState;

  // Record
  if (recording && stepCount < MAX_STEPS) {
    basePos[stepCount] = targetBase;
    shoulderPos[stepCount] = targetShoulder;
    stepCount++;
    delay(100);
  }

  // Playback
  if (digitalRead(playBtn) == LOW && stepCount > 0) {
    recording = false;
    Serial.println("Playing back...");
    for (int i = 1; i < stepCount; i++) {
      smoothMove(baseServo, currentBase, basePos[i], 5);     
      smoothMove(shoulderServo, currentShoulder, shoulderPos[i], 5);
    }
    Serial.println("Playback finished.");
  }
}
