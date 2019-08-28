#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "__def.h"
#include "wifi_functions.h"
#include "mqtt.h"

void setup()
{
  pinMode(BUILTIN_LED, OUTPUT); // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  InitWiFi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop()
{
  WiFiScan();
  PublishData();
  delay(1000);
}

void PublishData()
{
  if (!client.connected())
  {
    ReconnectSilent();
  }
  client.loop();
  if (client.publish("ENTC/Wifi_Outgoing", JSONmessageBuffer) == true)
  {
    Serial.println("Success sending message");
  }
  else
  {
    Serial.println("Error sending message");
  }
}
