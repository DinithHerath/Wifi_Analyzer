void InitWiFi()
{
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void InitWiFiSilent()
{
  delay(10);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(20);
  }
  delay(500);
  Serial.println("WiFi connected");
}

void WiFiScan()
{
  StaticJsonBuffer<300> JSONbuffer;
  JsonObject &JSONencoder = JSONbuffer.createObject();

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.println("Scanning started");
  int n = WiFi.scanNetworks();
  Serial.println("Scanning done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      if (WiFi.SSID(i) != ssid)
      {
        JSONencoder[String(WiFi.SSID(i)) + " " + String(WiFi.channel(i))] = int(WiFi.RSSI(i));
      }
      delay(10);
    }
  }
  Serial.println("");
  InitWiFiSilent();
  JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
  Serial.println("Sending message to MQTT topic..");
  Serial.println(JSONencoder.measureLength());
  Serial.println(JSONmessageBuffer);
}
