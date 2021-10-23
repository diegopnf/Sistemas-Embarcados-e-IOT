#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define DHTPIN D4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
LiquidCrystal_I2C lcd(0x27, 16, 2);

float h = dht.readHumidity();
float t = dht.readTemperature(false); 

char auth[] = "Codigo de autenticacao";
char ssid[] = "rede wifi";
char pass[] = "senha";   


void sendSensor()
{
  h = dht.readHumidity();
  t = dht.readTemperature(); 
  if (isnan(h) || isnan(t)) {
    Serial.println("Falha ao conectar com o sensor!");
    return;
  }
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}

void setup()
{
  Serial.begin(115200);
  dht.begin();
  lcd.begin();
  lcd.backlight();
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  h = dht.readHumidity();
  t = dht.readTemperature();
  Blynk.run();
  timer.run();
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(t);
  lcd.setCursor(11, 0);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Humi:");
  lcd.print(h);
  lcd.setCursor(11, 1);
  lcd.print("%");
}
