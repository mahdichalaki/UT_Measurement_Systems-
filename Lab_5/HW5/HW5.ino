#include <Arduino.h>
#include <Wire.h>
#include <BMx280I2C.h>
#define I2C_ADDRESS 0x76

//create a BMx280I2C object using the I2C interface with I2C Address 0x76
BMx280I2C bmx280(I2C_ADDRESS);

/****** Initialization ******/
void setup() {
  Serial.begin(9600);
  while (!Serial);
  Wire.begin();

  if (!bmx280.begin())
  {
    Serial.println("begin() failed. check your BMx280 Interface and I2C Address.");
    while (1);
  }

  bmx280.resetToDefaults();
  bmx280.writeOversamplingPressure(BMx280MI::OSRS_P_x16);
  bmx280.writeOversamplingTemperature(BMx280MI::OSRS_T_x16);
}

/****** main task ******/
void loop() {
  delay(1000);

  //start a measurement
  if (!bmx280.measure())
  {
    Serial.println("could not start measurement, is a measurement already running?");
    return;
  }

  //waits for the measurement to finish
  do
  {
    delay(100);
  } while (!bmx280.hasValue());

  Serial.print("Pressure: "); Serial.print(bmx280.getPressure64());
  Serial.print("  Temperature: "); Serial.println(bmx280.getTemperature());
}
