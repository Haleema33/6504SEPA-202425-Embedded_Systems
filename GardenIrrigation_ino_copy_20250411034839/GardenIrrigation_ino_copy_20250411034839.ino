// Define operating modes
enum Mode { DRY, MOIST, WET };
Mode currentMode;

// Moisture thresholds (in %)
int dryMin    = 10, dryMax    = 20;
int moistMin  = 30, moistMax  = 50;
int wetMin    = 60, wetMax    = 80;

// Global variables for current thresholds
int minMoisture, maxMoisture;

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

// -----------------------------------------------------------
// Arduino required functions

void setup() {
  // You can initialize Serial communication or pin modes here
  Serial.begin(9600);
  // Initialize sensor or any other hardware if needed
}

void loop() {
  // For example, read from the sensor and update mode:
  int sensorValue = analogRead(A0);   // Replace A0 with your actual sensor pin
  updateModeByMoisture(sensorValue);
  
  // Print to Serial Monitor for debugging:
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);
  
  // Add any other operation you need to do repeatedly.
  
  delay(2000); // Wait 2 seconds before next loop
}
