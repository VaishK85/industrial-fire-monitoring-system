#include <ESP8266WiFi.h>

// Replace with your actual credentials before uploading
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// ThingSpeak API configuration
String apiKey = "VVEE88CFBKCQAPBA";
const char* server = "api.thingspeak.com";

WiFiClient client;
float Level;

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
}

void loop() {
  float reading = analogRead(A0); // Read MQ-2 analog value
  Level = ((reading / 1023.0) * 100); // Convert to percentage

  if (isnan(Level)) {
    Serial.println("Failed to read from MQ-2 sensor!");
    return;
  }

  if (client.connect(server, 80)) {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(Level);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n
