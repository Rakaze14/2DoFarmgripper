#include <Servo.h>

// Servo objects
Servo servoBase, servoShoulder, servoElbow, servoClaw;

// Potentiometer pins
const int potBase = A0;
const int potShoulder = A1;
const int potElbow = A2;
const int potClaw = A3;

// Button pins
const int btnRecord = 4;
const int btnPlay   = 5;

// Servo control pins
const int servoBasePin = 9;
const int servoShoulderPin = 10;
const int servoElbowPin = 11;
const int servoClawPin = 12;

// Variables
int posBase, posShoulder, posElbow, posClaw;

// Recording
const int maxRecords = 1000;
int recordData[maxRecords][4];
int recordIndex = 0;
bool isRecording = false;
bool isPlaying = false;

void setup() {
  servoBase.attach(servoBasePin);
  servoShoulder.attach(servoShoulderPin);
  servoElbow.attach(servoElbowPin);
  servoClaw.attach(servoClawPin);

  pinMode(btnRecord, INPUT_PULLUP);
  pinMode(btnPlay, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  if (digitalRead(btnRecord) == LOW) {
    Serial.println("Recording started!");
    delay(300);  // Debounce
    isRecording = true;
    isPlaying = false;
    recordIndex = 0;
  }

  if (digitalRead(btnPlay) == LOW) {
    Serial.println("Playback started!");
    delay(300);  // Debounce
    isPlaying = true;
    isRecording = false;
    recordIndex = 0;
  }

  if (isRecording) {
    recordMovement();
  } else if (isPlaying) {
    playMovement();
  } else {
    manualControl();
  }
}

void manualControl() {
  posBase = map(analogRead(potBase), 0, 1023, 0, 180);
  posShoulder = map(analogRead(potShoulder), 0, 1023, 0, 180);
  posElbow = map(analogRead(potElbow), 0, 1023, 0, 180);
  posClaw = map(analogRead(potClaw), 0, 1023, 0, 180);

  servoBase.write(posBase);
  servoShoulder.write(posShoulder);
  servoElbow.write(posElbow);
  servoClaw.write(posClaw);
}

void recordMovement() {
  if (recordIndex < maxRecords) {
    recordData[recordIndex][0] = map(analogRead(potBase), 0, 1023, 0, 180);
    recordData[recordIndex][1] = map(analogRead(potShoulder), 0, 1023, 0, 180);
    recordData[recordIndex][2] = map(analogRead(potElbow), 0, 1023, 0, 180);
    recordData[recordIndex][3] = map(analogRead(potClaw), 0, 1023, 0, 180);

    recordIndex++;
    delay(100); 
  } else {
    Serial.println("Recording complete.");
    isRecording = false;
  }
}

void playMovement() {
  if (recordIndex < maxRecords && recordData[recordIndex][0] != -1) {
    servoBase.write(recordData[recordIndex][0]);
    servoShoulder.write(recordData[recordIndex][1]);
    servoElbow.write(recordData[recordIndex][2]);
    servoClaw.write(recordData[recordIndex][3]);

    recordIndex++;
    delay(100); 
  } else {
    Serial.println("Playback complete.");
    isPlaying = false;
  }
}
