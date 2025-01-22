#include <TimerOne.h>
int voltage = A0;
float Value, Res;       // Used for Output Voltage and Resistor
bool flag = 0;          // To make sure we print 5 values per second

void setup() {
  
  Serial.begin(9600);
  pinMode(voltage, INPUT);

  // ADC reference is determinded from an input signal
  analogReference(EXTERNAL);

  // initialize timer1 with a period of 1s
  Timer1.initialize(200000);
  Timer1.attachInterrupt(Read_Value);
}

void loop() {

// Checks to see if a new value is read
  if (flag == 1){
    flag = 0;

    // Convert output signal to 0-5 range
    Value = Value * 3.23/1023.00;

    // Termistor resistance value
    Res = 10000*(3.75 - Value)/(1.25 + Value);
    
    // Prints temperature in Celsius
    Serial.println(-273.15+1005659.95/(3373+298.15*log(Res/9801)));
  }
}


// Interrupt function

void Read_Value() {

  Value = analogRead(voltage);
  flag = 1;                     //Tells a new temperature is read.
}
