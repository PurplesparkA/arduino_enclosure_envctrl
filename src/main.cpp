#include <Arduino.h>
#include "DHT.h"
#include <LiquidCrystal.h>

// Min temperature inside the enclosure
#define MIN_TEMP 19.00
// Max temperature inside the enclosure
#define MAX_TEMP 24.00

// DHT sensor configuration
#define DHTPIN 2
#define DHTTYPE DHT11

// Create DHT object
DHT dht(DHTPIN, DHTTYPE);

// Create LiquidCrystal object
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Declare functions
void displayTempHumi(float, float);

void setup() {
  dht.begin();
  lcd.begin(16,2);
}

void loop() {
  delay(2000);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  displayTempHumi(temperature, humidity);
}

void displayTempHumi(float temp, float humi) {
  lcd.setCursor(0,0);
  lcd.print("Humi: ");
  lcd.print(humi);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print("C");
}