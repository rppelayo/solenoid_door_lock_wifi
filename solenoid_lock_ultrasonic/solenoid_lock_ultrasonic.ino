// pin definitions
#define BUZZER 3
#define LOCK 4
#define TRIGGER 5
#define ECHO 6

// added feature if ESP8266 board is used
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <MQTT.h>
  #define MQTT_BROKER "<INSERT MQTT BROKER HERE>"
  #define MQTT_CLIENT_ID "<INSERT MQTT CLIENT ID HERE>"
  #define MQTT_USER_ID "<INSERT USER ID HERE>"
  #define MQTT_KEY "<INSERT MQTT KEY HERE>"
  #define MQTT_TOPIC "<INSERT TOPIC HERE>"

  const char* ssid     = "<YOUR WIFI SSID>";
  const char* password = "<YOUR WIFI PASSWORD>";

  WiFiClient net;
  MQTTClient client;

  #include "MQTT_Functions.h"
#endif

// variables for reading obstacle distance
long duration;
int distance;

void setup() {
  Serial.begin(9600);
  pinMode(LOCK, OUTPUT);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  // make sure solenoid and buzzer is off at startup
  digitalWrite(LOCK, LOW);
  digitalWrite(BUZZER, LOW);
  // if ESP8266 is used, start WiFi connection
  #if defined(ESP8266)
    init_wifi();
  #endif
}

void loop() {
  // Clears the trigPin condition
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(ECHO, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  if(distance < 10){
    digitalWrite(BUZZER, HIGH);
    digitalWrite(LOCK, HIGH);
    delay(3000);
    digitalWrite(BUZZER, LOW);
    digitalWrite(LOCK, LOW);
  }
}
