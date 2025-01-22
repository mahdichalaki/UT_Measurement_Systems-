#include <TimerOne.h>
volatile bool ledState=HIGH;      // defining ledState boolean to keep the record of LED's state


/********* LDR *********/
#define NUM_SAMPLES 20            // Number of samples used for averaging

int LDR = A0;                     // Pin A0 has an LDR attached to it.
int led_pin = 6;                  // Digital pin 6 has an LED attached to it.

int sum = 0;                      // sum of samples taken
unsigned char sample_count = 0;   // current sample number
float V_out = 0.0;                // calculated V_out
float Resistance = 0.0;           // calculated Resistance
float Illumination = 0.0;         // calculated Illumination
float LED;                        // output to be sent to the LED


/********* Setup *********/
void setup() {

  // using built-in LED
  pinMode(LED_BUILTIN, OUTPUT);

  // initialize timer1 with a period of 1s
  Timer1.initialize(1000000);

  // blinkLED to run once overy seconds
  Timer1.attachInterrupt(blinkLED);

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // Define led_pin as an output
  pinMode(led_pin, OUTPUT);           
}


/********* Main Loop *********/
void loop() {

  // This loop is used for averaging and decreasing the noise
while (sample_count < NUM_SAMPLES) {
        sum += analogRead(LDR);
        sample_count++;
        delay(10);
}

// Map output voltage  to 0-5 scale
V_out = ((float)sum / (float)NUM_SAMPLES) * (5.0 / 1024.0);

// Calculate Resistance of the LDR
Resistance = (((float)V_out*220.0)/(5.0-V_out));

// Map output voltage to 0-255 scale to control LED light
LED = ((float)sum / (float)NUM_SAMPLES) * 255.0 / 1023.0;

analogWrite(led_pin, LED);

// Reset values
sample_count = 0;
sum = 0;


// Look up for the right category
if (Resistance<1.5e7 && Resistance>1e6) {
  Illumination = interp(1e6,1.5e7,0.1,0.001,Resistance);
  Serial.print(Illumination);
  Serial.println (" LUX");
}

else if (Resistance<1e6 && Resistance>7.5e4) {
  Illumination = interp(7.5e4,1e6,35,0.1,Resistance);
  Serial.print(Illumination);
  Serial.println (" LUX");
}

else if (Resistance<7.5e4 && Resistance>3e4) {
  Illumination = interp(3e4,7.5e4,72,35,Resistance);
  Serial.print(Illumination);
  Serial.println (" LUX");
}

else if (Resistance<3e4 && Resistance>1.7e4) {
  Illumination = interp(1.7e4,3e4,157,72,Resistance);
  Serial.print(Illumination);
  Serial.println (" LUX");
}

else if (Resistance<1.7e4 && Resistance>1.5e4) {
  Illumination = interp(1.5e4,1.7e4,200,157,Resistance);
  Serial.print(Illumination);
  Serial.println (" LUX");
}

else if (Resistance<1.5e4 && Resistance>3.8e3) {
  Illumination = interp(3.8e3,1.5e4,1380,200,Resistance);
  Serial.print(Illumination);
  Serial.println (" LUX");
}

else if (Resistance<3.8e3 && Resistance>2.8e3) {
  Illumination = interp(2.8e3,3.8e3,3700,1380,Resistance);
  Serial.print(Illumination);
  Serial.println (" LUX");
}

else if (Resistance<2.8e3 && Resistance>1.4e3) {
  Illumination = interp(1.4e3,2.8e3,7300,3700,Resistance);
  Serial.print(Illumination);
  Serial.println (" LUX");
}

else if (Resistance<1.4e3 && Resistance>47) {
  Illumination = interp(47,1.4e3,2.3e4,7300,Resistance);
  Serial.print(Illumination);
  Serial.println (" LUX");
}

else if (Resistance<47 && Resistance>10) {
  Illumination = interp(10,47,1e5,2.3e4,Resistance);
  Serial.print(Illumination);
  Serial.println (" LUX");
}

else {
  Illumination = 0;
  Serial.print(Illumination);
  Serial.println (" LUX");
}


}


/********* ISR *********/
void blinkLED() {
  digitalWrite(LED_BUILTIN, ledState);    // toggle LED
  ledState=!ledState;                     // keep the record of LED's state
}


// Float interpolation function
float interp(float A_1, float A_2, float B_1, float B_2, float x){
  return (((x-A_1)/(A_2-A_1))*(B_2-B_1))+B_1;
}
