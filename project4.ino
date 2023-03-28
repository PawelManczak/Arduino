#include <LiquidCrystal.h>
#include "i2c_BMP280.h"
#include "i2c.h"
#include "i2c_Sensor.h"
#include <Wire.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
BMP280 bmp;
float pressure;
float temperature;


void setup() {
  lcd.begin(16, 2);
  bmp.initialize();
  bmp.getTemperature(temperature);

}

void loop() {
  bmp.awaitMeasurement();
  bmp.getPressure(pressure);
  bmp.getTemperature(temperature);

  lcd.setCursor(0, 0);
  lcd.print("K:");
  lcd.print(temperature + 273.0f, 2);
  lcd.print(" C:");
  lcd.print(temperature, 2);
  lcd.setCursor(0, 1);

  lcd.print("P:");
  lcd.print(pressure/100, 0);
  int pressureInt = -((int)pressure)%100;
  lcd.print('.', 0);
  lcd.print(pressureInt);
  lcd.print("F:");
  lcd.print(temperature*2 + 32, 2);
  delay(1000);
}
