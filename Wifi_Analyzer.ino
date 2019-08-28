#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "__def.h"
#include "wifi_functions.h"
#include "mqtt.h"

void setup()
{
  Serial.begin(115200);
  InitWiFi();
  InitServer();
}

void loop()
{
  WiFiScan();
  PublishData();
  delay(1000);
}
