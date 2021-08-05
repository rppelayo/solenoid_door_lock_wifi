/// <summary>
/// Connect to MQTT Broker
/// </summary>
#if defined(ESP8266)
void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect(MQTT_CLIENT_ID, MQTT_USER_ID, MQTT_KEY)) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected to MQTT broker");

  client.subscribe(MQTT_TOPIC); 
}

/// <summary>
/// Event when message is received from MQTT Broker
/// </summary>
void messageReceived(String &topic, String &payload) {
  int caretLoc;
  String message;
  String device_id;
  
  Serial.println("incoming: " + topic + " - " + payload);

  if(topic != MQTT_TOPIC) return;   // read only config messages
  caretLoc = payload.indexOf('>'); 
  if(caretLoc > 0){
    device_id = payload.substring(0,caretLoc);
    if(device_id != MQTT_CLIENT_ID) return; // if device id's don't match, discontinue
    message = payload.substring(caretLoc+1);
  }else{
    return;
  }
  
  if(message.indexOf("ON") > 0){
    digitalWrite(BUZZER, HIGH);
    digitalWrite(LOCK, HIGH);
    delay(3000);
    digitalWrite(BUZZER, LOW);
    digitalWrite(LOCK, LOW);
  }
}

/// <summary>
/// Normal operation after setting up using Access Point
/// </summary>
void init_wifi(){  
  WiFi.mode(WIFI_STA);         // bug fix on AP still on after setup
  WiFi.begin(ssid, password);

  client.begin(MQTT_BROKER, net);
  client.onMessage(messageReceived);

  connect();
  delay(1000);

}
#endif
