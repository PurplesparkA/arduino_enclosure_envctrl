#include <Arduino.h>
#include "DHT.h"
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Min temperature inside the enclosure
#define MIN_TEMP 19.00
// Max temperature inside the enclosure
#define MAX_TEMP 24.00

// Define the fan relay pins
#define RELAY_PIN_COLD_FAN 10
#define RELAY_PIN_HEAT_FAN 11
#define RELAY_PIN_EXHAUST_FAN 12

// Define the temperature probe pin
#define ONEWIRE_BUS_PIN 5

// DHT sensor configuration
#define DHTPIN 2
#define DHTTYPE DHT11

// Create DHT object
DHT dht(DHTPIN, DHTTYPE);

// Create LiquidCrystal object
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Create the sensor object
OneWire oneWire(ONEWIRE_BUS_PIN);
DallasTemperature sensors(&oneWire);
float celsius = 0.00;
float farenheit = 0.00;

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