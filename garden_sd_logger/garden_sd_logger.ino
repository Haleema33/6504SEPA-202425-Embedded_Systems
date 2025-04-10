#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal.h>

// LCD (update pins according to your wiring)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// SD card
const int chipSelect = 10;
const char* logFileName = "log.txt";
bool sdAvailable = false;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  
  Serial.print("Initializing SD...");
  if (!SD.begin(chipSelect)) {
    Serial.println("SD Card init failed!");
    lcd.setCursor(0, 1);
    lcd.print("SD init fail!");
    delay(1500);
  } else {
    sdAvailable = true;
    Serial.println("SD Card init success.");
  }
}

void loop() {
  int moisture = analogRead(A0); // Replace A0 if your sensor is on a different pin
  logData(moisture);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moisture: ");
  lcd.print(moisture);

  delay(5000); // log every 5 seconds
}

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
