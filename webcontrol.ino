#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <ESP32Servo.h>

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASS";

AsyncWebServer server(80);

Servo baseServo;
Servo shoulderServo;

int basePos = 90;
int shoulderPos = 90;

void setup() {
  Serial.begin(115200);

  //LittleFS
  if(!LittleFS.begin(true)){
    Serial.println("LittleFS Mount Failed");
    return;
  }

  //Servos
  baseServo.attach(18);
  shoulderServo.attach(19);
  baseServo.write(basePos);
  shoulderServo.write(shoulderPos);

  // Connect WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected! IP: " + WiFi.localIP().toString());

  // Serve HTML page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/index.html", "text/html");
  });

  // Handle slider request
  server.on("/set", HTTP_GET, [](AsyncWebServerRequest *request){
    if(request->hasParam("base")){
      basePos = request->getParam("base")->value().toInt();
      baseServo.write(basePos);
    }
    if(request->hasParam("shoulder")){
      shoulderPos = request->getParam("shoulder")->value().toInt();
      shoulderServo.write(shoulderPos);
    }
    request->send(200, "text/plain", "OK");
  });

  server.begin();
}

void loop() {
  // Nothing needed, async server handles requests
}
