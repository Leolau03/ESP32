#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <WebSocketsClient.h>

const char* WIFI_SSID = "iPhone (94)"; // Change with wifi name
const char* WIFI_PASSWORD = "leoESP32"; // Change with wifi password
const char* serverAddress = "053f-2620-101-f000-700-3fff-fffb-2b56-fd40.ngrok-free.app"; // Replace with your computer's IP address or hostname

WebSocketsClient webSocket;

int sensorPin = 32;   // select the input pin for the potentiometer      
int sensorValue = 0;  // variable to store the value coming from the sensor
float volt;



void handleWebSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("WebSocket client %u disconnected\n");
      break;
    case WStype_CONNECTED:
      Serial.printf("WebSocket client %u connected\n");
      break;
    case WStype_TEXT:
      // Handle data received from the WebSocket client
      // 'payload' is a char array containing the received data
      // 'length' is the length of the received data
      break;
    case WStype_BIN:
      // Handle binary data received from the WebSocket client (if needed)
      break;
    case WStype_PING:
      // Handle PING messages (if desired)
      break;
    case WStype_PONG:
      // Handle PONG messages (if desired)
      break;
    case WStype_ERROR:
      // Handle errors (if desired)
      break;
  }
}

void sendValue(int value) {
  String jsonPayload = "{\"value\": " + String(value) + "}";
  webSocket.sendTXT(0, jsonPayload);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(921600);
  
  // Connects to wifi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Connect to WebSocket server
  webSocket.begin(serverAddress);
  webSocket.onEvent(onWebSocketEvent);
  
  Serial.println("Connecting to WebSocket server...");
  }


void loop() {

  webSocket.loop();
  sensorValue = analogRead(sensorPin);
  volt = sensorValue*5/1023.0;
  sendValue(volt);
  Serial.println( volt );

}

