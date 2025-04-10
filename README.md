# 6504SEPA-202425-Embedded_Systems
#  Group Haleema, Fatima, Manahil. 
# Smart Irrigation System

An Arduino-based automated irrigation system designed to monitor soil moisture and automatically control a water pump to keep your plants hydrated and healthy. The system logs moisture levels to an SD card and displays real-time moisture data on an LCD.

## Key Features
- **Real-time soil moisture monitoring**
- **Automatic irrigation control using a relay module**
- **LCD Display**: Shows current moisture percentage and moisture state (Dry, Moist, Wet).
- **Data Logging**: Saves moisture data to an SD card for tracking and analysis.
- **Visual Indicators**: LED lights indicate soil moisture status clearly.

## Hardware Components
- Arduino Uno (or compatible board)
- Moisture Sensor (Analog)
- Relay Module (Active LOW)
- DC Water Pump
- 16x2 LCD Display
- SD Card Module
- Red and Green LEDs
- Power source (e.g., battery matching the pump’s voltage)

## Circuit Connections

| Arduino Pin | Component             |
|-------------|-----------------------|
| A0          | Soil Moisture Sensor  |
| 8           | Relay Module Input    |
| 7,6,5,4,3,2 | 16x2 LCD Display      |
| 10          | SD Card Module (CS)   |
| A1          | Red LED               |
| A2          | Green LED             |

**Power Wiring:**
- Battery (+) → Relay COM
- Relay NO → Pump (+)
- Pump (–) → Battery (–)

## Moisture Levels

| Mode  | Moisture Range (%) |
|-------|--------------------|
| Dry   | 10% - 20%          |
| Moist | 30% - 50%          |
| Wet   | 60% - 80%          |

## How It Works
1. **Reads moisture data** from the sensor every 5 seconds.
2. **Automatically classifies** the moisture level into Dry, Moist, or Wet modes.
3. **Activates the water pump** if moisture drops below the minimum threshold.
4. **Displays real-time status** on an LCD and LEDs.
5. **Logs data** onto an SD card if available.

## Getting Started
1. Clone or download the repository.
2. Upload the Arduino sketch (`.ino` file) using Arduino IDE.
3. Connect the hardware according to the schematic provided.
4. Ensure the SD card is properly formatted and inserted.

## Contributing
Feel free to submit pull requests, raise issues, or contribute by improving the project documentation and code.


