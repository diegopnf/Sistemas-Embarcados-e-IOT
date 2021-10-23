#include <ESP8266WiFi.h>
#include <DHT.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define DHTPIN D4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

int umidade = dht.readHumidity();
int temperatura = dht.readTemperature(false);

char ssid[] = "AP@net";  //Enter your WIFI Name
char pass[] = "";  //Enter your WIFI Password

void setup()
{
  Serial.begin(9600);
  dht.begin();
  lcd.begin();
  lcd.backlight(); 
}

void loop()
{
  temperatura = dht.readTemperature();
  umidade = dht.readHumidity();
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(temperatura);
  lcd.setCursor(11, 0);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Humi:");
  lcd.print(umidade);
  lcd.setCursor(11, 1);
  lcd.print("%");
}
