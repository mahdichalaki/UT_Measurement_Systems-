/* This is a program for setting Resistor*/

// Defining pins
int res = A1;

// Value is output voltage , R is for R1 in voltage divider circuit
float Value , R;  

void setup() {
  Serial.begin(9600);
  pinMode(res, INPUT);

}

void loop() {
  Value = analogRead(res);
  Value = Value*5.00/1023.00;   // measures output voltage
  R = 10000 - 2000 * Value;     // Measures R1 in voltage divider circuit
  //R = 50000 - 10000 * Value;     // Measures R1 in voltage divider circuit
  Serial.println(R);
  delay(100);
}
