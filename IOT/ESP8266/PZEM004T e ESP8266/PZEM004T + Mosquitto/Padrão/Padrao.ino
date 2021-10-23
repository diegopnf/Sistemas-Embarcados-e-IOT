// --- WIFI ---
#include <ESP8266WiFi.h>     
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>      
WiFiClient nodemcuClient;

// --- MQTT ---
#include <PubSubClient.h>
const char* mqtt_Broker = "192.168.0.24";
const char* mqtt_ClientID = "pzem004tdiegopnf";
PubSubClient client(nodemcuClient);
const char* topicoTensao = "pzem/tensao";

// --- PZEM004T ---
#include <PZEM004Tv30.h>
PZEM004Tv30 pzem(D5, D6);
float tensao;

void setup() {
  Serial.begin(115200);
  WiFiManager wifiManager;
  wifiManager.autoConnect("Medidor de Energia");
  client.setServer(mqtt_Broker, 1883);
}

void loop() {
  reconectarMQTT();
  medirEnergia();
  publicarTensaoNoTopico();
}

void reconectarMQTT() {
  while (!client.connected()) {
    client.connect(mqtt_ClientID);
  }
}

void publicarTensaoNoTopico() {
  client.publish(topicoTensao, String(tensao).c_str(), true);
}

void medirEnergia(){
  tensao = pzem.voltage();
  Serial.print("Tensao (V): ");
  Serial.println(tensao);  
}
