# Measurement Systems - Lab 6

This repository contains the sixth laboratory experiment for the **Measurement Systems** course at the **University of Tehran**, focusing on designing a temperature measurement system using an **NTC thermistor** and data acquisition via **Arduino Uno**.

---

## 📖 Objectives

1. **Design and Implementation of a Temperature Measurement System:**
   - Develop a system using a 10kΩ NTC thermistor for temperature sensing.
   - Calculate thermistor resistance at various temperatures.
   - Use the Steinhart-Hart equation to determine temperature from resistance.

2. **Analog Signal Processing:**
   - Implement an amplifier circuit to condition the sensor's output.
   - Utilize an external voltage reference for better ADC accuracy.
   - Design a voltage divider circuit for accurate resistance measurement.

3. **Data Acquisition and Processing:**
   - Read the thermistor resistance via Arduino's ADC.
   - Process temperature values and display them via the serial monitor.
   - Compare measured values with a reference BMP280 sensor.

---

## 🛠️ Components Used

- **Microcontroller:**  
  - Arduino Uno  

- **Electronic Components:**  
  - NTC Thermistor (10kΩ)  
  - Resistors (various values for voltage divider)  
  - Operational Amplifier (for signal conditioning)  
  - External voltage reference (3.23V)  
  - Breadboard and jumper wires  

- **Software:**  
  - Arduino IDE (for programming)  
  - MATLAB (for data analysis and curve fitting)  

