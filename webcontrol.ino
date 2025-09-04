#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <ESP32Servo.h>
#define BASE_PIN 18
#define SHOULDER_PIN 19


// ====== Wi-Fi Config ======
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASS";

// ====== Web Server ======
AsyncWebServer server(80);

// ====== Servo Setup ======
Servo baseServo;
Servo shoulderServo;

int basePos = 90;    
int shoulderPos = 90;

void setup() {
  Serial.begin(115200);

  // Mount LittleFS
  if(!LittleFS.begin(true)){
    Serial.println("LittleFS Mount Failed!");
    return;
  }

  // Attach servos
  baseServo.attach(BASE_PIN);
  shoulderServo.attach(SHOULDER_PIN);
  baseServo.write(basePos);
  shoulderServo.write(shoulderPos);

  // Connect WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected. IP: " + WiFi.localIP().toString());

  // Serve HTML page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/index.html", "text/html");
  });

  // Handle slider requests
  server.on("/set", HTTP_GET, [](AsyncWebServerRequest *request){
    if(request->hasParam("base")){
      basePos = request->getParam("base")->value().toInt();
      baseServo.write(basePos);
      Serial.printf("Base: %d\n", basePos);
    }
    if(request->hasParam("shoulder")){
      shoulderPos = request->getParam("shoulder")->value().toInt();
      shoulderServo.write(shoulderPos);
      Serial.printf("Shoulder: %d\n", shoulderPos);
    }
    request->send(200, "text/plain", "OK");
  });

  server.begin();
}

void loop() {
}
