#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

#define WIFI_SSID "iPhone (94)"
#define WIFI_PASSWORD "leoESP32"

WiFiMulti wifiMulti;

// WiFi connect timeout per AP. Increase when connecting takes longer.

const uint32_t connectTimeoutMs = 10000;
int sensorPin = 32;   // select the input pin for the potentiometer      
int sensorValue = 0;  // variable to store the value coming from the sensor
float volt;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(921600);
  WiFi.mode(WIFI_STA);
  
  // Add list of wifi networks
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
      Serial.println("no networks found");
  } 
  else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
      delay(10);
    }
  }

  // Connect to Wi-Fi using wifiMulti (connects to the SSID with strongest connection)
  Serial.println("Connecting Wifi...");
  if(wifiMulti.run() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
}

void loop() {
  //if the connection to the stongest hotstop is lost, it will connect to the next network on the list
  if (wifiMulti.run(connectTimeoutMs) == WL_CONNECTED) {
    Serial.print("WiFi connected: ");
    Serial.print(WiFi.SSID());
    Serial.print(" ");
    Serial.println(WiFi.RSSI());
  }
  else {
    Serial.println("WiFi not connected!");
  }
  delay(1000);

  sensorValue = analogRead(sensorPin);
  volt = sensorValue*5/1023.0;
  Serial.println( volt );
}

