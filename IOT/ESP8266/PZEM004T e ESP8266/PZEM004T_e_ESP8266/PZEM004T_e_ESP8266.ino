#include <ESP8266WiFi.h>
#include <PZEM004Tv30.h>
#include <Wire.h> 

PZEM004Tv30 pzem(D5, D6);

char ssid[] = "AP@net";  //Enter your WIFI Name
char pass[] = "";  //Enter your WIFI Password

void setup()
{
  Serial.begin(115200);

  Serial.print("Reiniciar Energia");
  pzem.resetEnergy();
}

void loop() {
  //energymeter 2
  float tensao = pzem.voltage();
  Serial.print("Tensao (V): ");
  Serial.println(tensao);
  
  float corrente = pzem.current();
  Serial.print("Corrente (A): ");
  Serial.println(corrente);
  
  float potencia = pzem.power();
  Serial.print("Potencia (W): ");
  Serial.println(potencia);
  
  float potenciahora = pzem.energy();
  Serial.print("Potencia/hora (KWh): ");
  Serial.println(potenciahora);
  
  float frequencia = pzem.frequency();
  Serial.print("Frquencia (Hz): ");
  Serial.println(frequencia);
  
  float fatorpotencia = pzem.pf();
  Serial.print("Fator de potencia: ");
  Serial.println(fatorpotencia);
  Serial.println(" ");
  
  delay(10000); // 10 segundos
}
