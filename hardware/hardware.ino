#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <Airtrik.h>

char* mykey = "";
char* ssid = "";
char* pass = "";



void onReceive(char* deviceId, byte* message, unsigned int length){
  int i;
  String x ="";
  for(i=0; i < length; i++){
    x = x+ char(message[i]);
  }
  Serial.println("");
  Serial.println(x);
  if(x == "reset"){
  ESP.reset();  
  }
  // std::string input;

StaticJsonDocument<128> doc;

DeserializationError error = deserializeJson(doc, x);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
//    Serial.println(error);
    return;
  }

  bool socket2 = doc["socket2"]; // 0
  bool socket3 = doc["socket3"]; // 0
  bool socket4 = doc["socket4"]; // 0
  bool socket1 = doc["socket1"]; // true

  socket1 ? digitalWrite(D1,LOW):digitalWrite(D1,HIGH);
  socket2 ? digitalWrite(D2,LOW):digitalWrite(D2,HIGH);
  socket3 ? digitalWrite(D3,LOW):digitalWrite(D3,HIGH);
  socket4 ? digitalWrite(D4,LOW):digitalWrite(D4,HIGH);
  
}

Airtrik iot;

void setup() {
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
  digitalWrite(D1,HIGH);
  digitalWrite(D2,HIGH);
  digitalWrite(D3,HIGH);
  digitalWrite(D4,HIGH);
  iot.connect(ssid, pass, mykey);
  iot.subscribe(""); 
}

void loop() {
  iot.loop();
  delay(500);
}
