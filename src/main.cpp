#include <Arduino.h>
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

// Create display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Create the sensor object
OneWire oneWire(ONEWIRE_BUS_PIN);
DallasTemperature sensors(&oneWire);
float Celsius = 0.00;
float insideTemp = 0.00;
float outsideTemp = 0.00;

// Addresses of the sensors
uint8_t insideSensor[8] = {0x28, 0x48, 0xE2, 0x75, 0xD0, 0x01, 0x3C, 0x7A};
uint8_t outsideSensor[8] = {0x28, 0xF8, 0x0E, 0x75, 0xD0, 0x01, 0x3C, 0x86};

// Fan activation
bool coolFan = false;
bool heatFan = false;
bool exhaustFan = false;

// Declare functions
void displayTemp();

void setup() {
  Serial.begin(9600);
  sensors.begin();

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds
}

void loop() {
  delay(1000);
  sensors.requestTemperatures();
  // Celsius = sensors.getTempCByIndex(0);
  outsideTemp = sensors.getTempC(outsideSensor);
  insideTemp = sensors.getTempC(insideSensor);
  displayTemp();
  if(insideTemp <= MIN_TEMP) {
    heatFan = true;
    exhaustFan = true;
    coolFan = false;
    Serial.print("Heating Fan: on");
    Serial.print(" -- ");
    Serial.println("Exhaust Fan: on");
  } else if (insideTemp >= MAX_TEMP) {
    heatFan = false;
    exhaustFan = true;
    coolFan = true;
    Serial.print("Cooling Fan: on");
    Serial.print(" -- ");
    Serial.println("Exhaust Fan: on");
  } else {
    heatFan = false;
    exhaustFan = false;
    coolFan = false;
    Serial.println("All Fans: off");
  }
}

void displayTemp() {
  // Clear the display
  display.clearDisplay();
  //Set the color - always use white despite actual display color
  display.setTextColor(WHITE);
  //Set the font size
  display.setTextSize(1);
  //Set the cursor coordinates
  display.setCursor(0,0);
  display.print("Purplespark Enclosure");
  display.setCursor(0,10); 
  display.print("Inside: "); 
  display.print(insideTemp);
  display.print(" C");
  display.setCursor(0,20);
  display.print("Outside: ");
  display.print(outsideTemp);
  display.print(" C");
  // Fan logic
  // Heating fan
  display.setCursor(0,30);
  display.print("Heating fan: ");
  if(heatFan) {
    display.print("on");
  } else {
    display.print("off");
  }
  // Cooling fan
  display.setCursor(0,40);
  display.print("Cooling fan: ");
  if(coolFan) {
    display.print("on");
  } else {
    display.print("off");
  }
  // Exhaust fan
  display.setCursor(0,50);
  display.print("Exhaust fan: ");
  if(exhaustFan) {
    display.print("on");
  } else {
    display.print("off");
  }

  // Display
  display.display();
}
