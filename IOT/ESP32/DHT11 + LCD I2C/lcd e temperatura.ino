#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#define DHT_SENSOR_PIN  23 // GPIO 23 ESP32
#define DHT_SENSOR_TYPE DHT11

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

void setup() {
  dht_sensor.begin(); // Inicializa sensor DHT
  lcd.init();         // Inicializa LCD I2C
  lcd.backlight();
}

void loop() {
  float humi  = dht_sensor.readHumidity();
  float tempC = dht_sensor.readTemperature();
  lcd.clear();
  if (isnan(tempC) || isnan(humi)) {
    lcd.setCursor(0, 0);
    lcd.print("Failed");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(tempC);
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("Humi: ");
    lcd.print(humi);
    lcd.print("%");
  }
  delay(2000);
}
