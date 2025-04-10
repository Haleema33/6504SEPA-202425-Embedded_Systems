#include <LiquidCrystal.h>
#include <SPI.h>
#include <SD.h>

// LCD setup: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// SD card chip select pin
const int chipSelect = 10;

// Pin assignments
const int sensorPin = A0;     // Moisture sensor input
const int relayPin  = 8;      // Relay output to control pump
const int redLEDPin = A1;     // Red LED (moisture issue)
const int greenLEDPin = A2;   // Green LED (moisture within range)

// Define operating modes
enum Mode { DRY, MOIST, WET };
Mode currentMode;

// Moisture thresholds (in %)
int dryMin    = 10, dryMax    = 20;
int moistMin  = 30, moistMax  = 50;
int wetMin    = 60, wetMax    = 80;

// Global variables for current thresholds
int minMoisture, maxMoisture;

// SD log file name and availability flag
const char* logFileName = "log.txt";
bool sdAvailable = false;

// Function to log data (only logs if SD is available)
void logData(int moisture) {
  if (!sdAvailable)
    return;
    
  File logFile = SD.open(logFileName, FILE_WRITE);
  if (logFile) {
    logFile.print("Moisture Level: ");
    logFile.print(moisture);
    logFile.println("%");
    logFile.close();
  } else {
    Serial.println("Error opening log file on SD Card");
  }
}

// Automatically set the operating mode based on the moisture level
void updateModeByMoisture(int moisture) {
  if (moisture >= wetMin && moisture <= wetMax) {
    currentMode = WET;
    minMoisture = wetMin;
    maxMoisture = wetMax;
  } else if (moisture >= moistMin && moisture <= moistMax) {
    currentMode = MOIST;
    minMoisture = moistMin;
    maxMoisture = moistMax;
  } else if (moisture >= dryMin && moisture <= dryMax) {
    currentMode = DRY;
    minMoisture = dryMin;
    maxMoisture = dryMax;
  } else {
    // If out of defined ranges, default to MOIST
    currentMode = MOIST;
    minMoisture = moistMin;
    maxMoisture = moistMax;
  }
}

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Irrigation Sys!");
  delay(2000);
  lcd.clear();

  pinMode(sensorPin, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Pump is off initially

  // Initialize SD card (continue even if it fails)
  Serial.print("Initializing SD...");
  if (!SD.begin(chipSelect)) {
    Serial.println("SD Card init failed!");
    lcd.setCursor(0, 1);
    lcd.print("SD init fail!");
    delay(1500);  // Show warning for a moment
  } else {
    sdAvailable = true;
    Serial.println("SD Card init success.");
  }
}

void loop() {
  // Read sensor and convert reading to a percentage
  int sensorValue = analogRead(sensorPin);
  int moisturePercent = map(sensorValue, 1023, 0, 0, 100);

  // Automatically update mode based on moisture percentage
  updateModeByMoisture(moisturePercent);

  // Update LCD display:
  // First line shows the current moisture level
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CurMoisture: ");
  lcd.print(moisturePercent);
  lcd.print("%");

  // Second line shows the detected mode and its threshold range
  lcd.setCursor(0, 1);
  switch (currentMode) {
    case DRY:
      lcd.print("Dry: ");
      lcd.print(dryMin);
      lcd.print("-");
      lcd.print(dryMax);
      lcd.print("%");
      break;
    case MOIST:
      lcd.print("Moist: ");
      lcd.print(moistMin);
      lcd.print("-");
      lcd.print(moistMax);
      lcd.print("%");
      break;
    case WET:
      lcd.print("Wet: ");
      lcd.print(wetMin);
      lcd.print("-");
      lcd.print(wetMax);
      lcd.print("%");
      break;
  }

  // Log moisture level to SD card (if available)
  logData(moisturePercent);


  // LED Indicators based on whether the moisture is within range
  if (moisturePercent > minMoisture && moisturePercent < maxMoisture) {
    digitalWrite(greenLEDPin, LOW);
    digitalWrite(redLEDPin, HIGH);
  } else {
    digitalWrite(greenLEDPin, HIGH);
    digitalWrite(redLEDPin, LOW);
  }

  // Pump control: Activate the pump if moisture is below the minimum threshold
  if (moisturePercent < minMoisture) {
    digitalWrite(relayPin, LOW);   // Turn pump ON (assumed active LOW)
    Serial.println("Pump ON: Soil is dry.");
  } else {
    digitalWrite(relayPin, HIGH);  // Turn pump OFF
    Serial.println("Pump OFF: Moisture OK.");
  }

  Serial.print("Moisture: ");
  Serial.print(moisturePercent);
  Serial.print("%  (Sensor: ");
  Serial.print(sensorValue);
  Serial.println(")");
  
  delay(5000); // Delay between sensor readings
}
