#include <Arduino.h>
#include "DHT.h"
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Display definition
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1


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

// Create display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Create DHT object
DHT dht(DHTPIN, DHTTYPE);

// Create LiquidCrystal object
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Create the sensor object
OneWire oneWire(ONEWIRE_BUS_PIN);
DallasTemperature sensors(&oneWire);
float Celsius = 0.00;

// Declare functions
void displayTempHumi(float, float);

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16,2);
  sensors.begin();

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x78)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds
}

void loop() {
  delay(2000);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  displayTempHumi(temperature, humidity);

  sensors.requestTemperatures();
  Celsius = sensors.getTempCByIndex(0);
  Serial.print("Temperature: ");
  Serial.print(Celsius);
  Serial.println(" C");
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