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
#define MAX_TEMP 25.00

// Define the fan relay pins
#define RELAY_PIN_COLD_FAN 8     // Relay IN1
#define RELAY_PIN_HEAT_HEAD 9    // Relay IN2
#define RELAY_PIN_HEAT_FAN 10     // Relay IN3
#define RELAY_PIN_EXHAUST_FAN 11  // Relay IN4

// Define the temperature probe pin
#define ONEWIRE_BUS_PIN 5

// Create display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Create the sensor object
OneWire oneWire(ONEWIRE_BUS_PIN);
DallasTemperature sensors(&oneWire);

// Variables to store values from the sensors
float insideTemp = 0.00;
float outsideTemp = 0.00;

// Addresses of the sensors
uint8_t insideSensor[8] = {0x28, 0x48, 0xE2, 0x75, 0xD0, 0x01, 0x3C, 0x7A};
uint8_t outsideSensor[8] = {0x28, 0xF8, 0x0E, 0x75, 0xD0, 0x01, 0x3C, 0x86};

// Fan activation
bool coolFan = false;
bool heatFan = false;
bool exhaustFan = false;

// Fan icon
const unsigned char fanBMP [] PROGMEM = {
	0x03, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x1f, 0x8e, 0x00, 0x3f, 0x9f, 0x80, 0x3f, 0x3f, 0x80, 0x1f, 
	0x3f, 0x80, 0x1f, 0xff, 0xc0, 0x07, 0xff, 0x80, 0x21, 0x20, 0x00, 0x7f, 0xfc, 0x00, 0x7f, 0xbe, 
	0x00, 0x7f, 0x3f, 0x00, 0x7f, 0x3f, 0x00, 0x3e, 0x7f, 0x00, 0x1c, 0x7e, 0x00, 0x00, 0x7c, 0x00, 
	0x00, 0x10, 0x00
};

#define FAN_HEIGHT 24
#define FAN_WIDTH 24


// Declare functions
void displayTemp();
void setFans();

// Setup the arduino
void setup() {
  sensors.begin();

  // Set the relays to HIGH to turn them off
  digitalWrite(RELAY_PIN_COLD_FAN,HIGH);
  digitalWrite(RELAY_PIN_HEAT_HEAD, HIGH);
  digitalWrite(RELAY_PIN_HEAT_FAN, HIGH);
  digitalWrite(RELAY_PIN_EXHAUST_FAN, HIGH);

  // Fan relay pins as output
  pinMode(RELAY_PIN_COLD_FAN, OUTPUT);
  pinMode(RELAY_PIN_HEAT_HEAD, OUTPUT);
  pinMode(RELAY_PIN_HEAT_FAN, OUTPUT);
  pinMode(RELAY_PIN_EXHAUST_FAN, OUTPUT);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(1000); // Pause for 1 second
}

// Endless loop
void loop() {
  delay(1000);

  // Interrogate the sensors
  sensors.requestTemperatures();

  // Get the temperatures
  outsideTemp = sensors.getTempC(outsideSensor);
  insideTemp = sensors.getTempC(insideSensor);

  if(insideTemp <= MIN_TEMP) {
    heatFan = true;
    exhaustFan = true;
    coolFan = false;
  } else if (insideTemp >= MAX_TEMP) {
    heatFan = false;
    exhaustFan = true;
    coolFan = true;
  } else {
    heatFan = false;
    exhaustFan = false;
    coolFan = false;
  }
  
  // Set the fan status
  setFans();

  // Display the temperatures
  displayTemp();
}

// Display function
void displayTemp() {
  // Clear the display
  display.clearDisplay();
  //Set the color - always use white despite actual display color
  display.setTextColor(WHITE);
  //Set the font size
  display.setTextSize(1);
  // Draw a rectangle across the whole perimeter of the screen
  display.drawRect(0, 0, display.width(), display.height(), SSD1306_WHITE);

  // Temperatures title
  display.setCursor(display.width()/2 - 36, 2);
  display.drawRect(0, 0, display.width(), 12, SSD1306_WHITE);
  display.fillRect(0, 0, display.width(), 12, WHITE);
  display.setTextColor(BLACK, WHITE);
  display.print("TEMPERATURES");
  display.setTextColor(WHITE);

  // Draw 2 rectangles for the temperatures
  display.drawRect(0,11, display.width()/2, 12, SSD1306_WHITE);
  display.drawRect(display.width()/2 - 1, 11, display.width(), 12, SSD1306_WHITE);
  //Set the cursor coordinates
  display.setCursor(2,14);
  display.print("I: ");
  display.print(insideTemp);
  display.print(" C");
  display.setCursor(display.width()/2 + 2, 14);
  display.print("O: ");
  display.print(outsideTemp);
  display.print(" C");

  // Fans title
  display.drawRect(0, 22, display.width(), 12, SSD1306_WHITE);
  display.fillRect(0, 22, display.width(), 12, WHITE);
  display.setCursor(display.width()/2 - 12, 24);
  display.setTextColor(BLACK, WHITE);
  display.print("FANS");
  display.setTextColor(WHITE);
  
  // Fan logic
  // Draw saparations
  display.drawRect(0, 33, 42, display.height(), SSD1306_WHITE);
  display.drawRect(41, 33, 42, display.height(), SSD1306_WHITE);
  display.drawLine(0, 44, display.width(), 44, SSD1306_WHITE);

  // Heating
  display.setCursor(10,35);
  display.print("HEAT");
  display.setCursor(14, 52);
  if(heatFan) {
    //display.print("ON");
    display.drawBitmap(14, 45, fanBMP, 18, 17, WHITE);
  } else {
    display.print("OFF");
  }
  
  // Cooling
  display.setCursor(50,35);
  display.print("COOL");
  display.setCursor(54, 52);
  if(coolFan) {
    display.drawBitmap(54, 45, fanBMP, 18, 17, WHITE);
    //display.print("ON");
  } else {
    display.print("OFF");
  }
  
  // Exhaust
  display.setCursor(96,35);
  display.print("EXH");
  display.setCursor(96, 52);
  if(exhaustFan) {
    display.drawBitmap(96, 45, fanBMP, 18, 17, WHITE);
    //display.print("ON");
  } else {
    display.print("OFF");
  }
  
  // Display
  display.display();
}

// Set the fans on/off status
void setFans() {
  // Manage cooling
  if(coolFan)
    digitalWrite(RELAY_PIN_COLD_FAN, LOW);
  else
    digitalWrite(RELAY_PIN_COLD_FAN, HIGH);

  // Manage heating
  if(heatFan) {
    digitalWrite(RELAY_PIN_HEAT_FAN, LOW);
    digitalWrite(RELAY_PIN_HEAT_HEAD, LOW);
  } else {
    digitalWrite(RELAY_PIN_HEAT_FAN, HIGH);
    digitalWrite(RELAY_PIN_HEAT_HEAD, HIGH);
  }

  // Manage exhaust
  if(exhaustFan)
    digitalWrite(RELAY_PIN_EXHAUST_FAN, LOW);
  else
    digitalWrite(RELAY_PIN_EXHAUST_FAN, HIGH);
}