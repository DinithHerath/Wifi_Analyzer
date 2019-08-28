void InitServer()
{
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
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