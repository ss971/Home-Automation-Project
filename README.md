# Home Automation System

## Overview

This project is a **Home Automation System** designed to enhance comfort and safety by automating responses to environmental changes. It consists of three main functionalities:

1. **Motion Sensing** - Detects movement and triggers an LED indicator.
2. **Temperature-Based Fan Control** - Turns on a motor (acting as a fan) when the temperature exceeds a set threshold.
3. **CO2 Monitoring and Alarm System** - Activates a buzzer when CO2 levels surpass a predefined safe limit.

## Components Used

- **DHT11 Sensor** - Measures temperature.
- **PIR Sensor** - Detects motion.
- **MQ135 Sensor** - Monitors air quality (CO2 levels).
- **Buzzer** - Sounds an alert for high CO2 levels.
- **LED** - Indicates motion detection.
- **Microcontroller** - Arduino-compatible board to control the system.
- **Motor (Fan Substitute)** - Switches on when the temperature rises above a threshold.

## Functionalities

### 1. Motion Detection

- Uses a PIR sensor to detect movement.
- Activates an LED when motion is detected.
- LED turns off when no motion is detected for a set time.

### 2. Temperature-Based Fan Control

- Uses a DHT11 sensor to monitor temperature.
- If the temperature exceeds a predefined threshold, the system turns on the motor (simulating a fan).
- The motor turns off when the temperature returns to a safe level.

### 3. CO2 Monitoring and Alarm System

- Uses an MQ135 sensor to measure air quality.
- If CO2 levels exceed a predefined threshold, a buzzer sounds an alarm.
- The buzzer turns off when CO2 levels return to normal.

## Setup and Installation

1. Connect the sensors and actuators to the Arduino as per the circuit diagram.
2. Upload the provided code to the Arduino.
3. Open the serial monitor to observe sensor readings and system status.
4. Power the system and observe automation responses based on environmental conditions.

## Code Explanation

### **Setup Function (********`setup()`********)**

- Initializes serial communication.
- Configures sensor and actuator pins.
- Provides time for sensor calibration.

### **Loop Function (********`loop()`********)**

- Reads temperature and activates the fan if needed.
- Checks PIR sensor status and toggles LED accordingly.
- Measures air quality and triggers the buzzer if CO2 levels are high.

## Applications

- **Home Automation** - Enhancing convenience and safety.
- **Smart Environment Monitoring** - Detecting temperature and air quality changes.
- **Industrial Safety Systems** - Monitoring hazardous gas levels.

## Future Enhancements

- **Remote Monitoring** - Implement WiFi/Bluetooth connectivity for mobile alerts.
- **Data Logging** - Store sensor readings for trend analysis.
- **Display Integration** - Add an LCD screen for real-time status updates.

## Contributing

Feel free to fork this repository, submit issues, or create pull requests for improvements.

