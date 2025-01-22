#include <TimerOne.h>
#define PWMOUT 11
#define ADC_CHANNEL A0

#define res A1
#define record 2

float Value;

// Debouncing variables
volatile long t = 0;
int debouncingTime = 200;

float SINE_FREQ = 10;
// Output should be in 0-5 volt range
float SINE_COEFF, Amp=2.5/5*255, Offset=2.5/5*255;

int DUTYCYCLE, SAMPLE;
long TIMESTAMP, counter = 0;

void setup() {
  pinMode(res, INPUT);
  pinMode (record, INPUT_PULLUP);
  
  TCCR2B = TCCR2B & B11111000 | B00000001;              // Sets Timer 2 PWM frequency to 31KHz
  pinMode(PWMOUT, OUTPUT);
  Serial.begin (57600);
  Timer1.initialize (1000);
  Timer1.attachInterrupt (PWM_DT);
  attachInterrupt (digitalPinToInterrupt(record), buttonISR, FALLING);
  
}

void loop() {
  SINE_COEFF = SINE_FREQ*TWO_PI/1000.000;
  TIMESTAMP = micros();                                   // Timestamp for each sample to be analyzed later
  SAMPLE = analogRead(ADC_CHANNEL);                       // Using Arduino's ADC to read the PWM output voltage
  Serial.print (TIMESTAMP/100); Serial.print("\t");       // Printing timestamp
  Serial.println (SAMPLE/1023.00*5);
}

// Function for generating PWM signal
void PWM_DT(){
  DUTYCYCLE = Amp * sin(SINE_COEFF * counter) + Offset;
  analogWrite(PWMOUT, DUTYCYCLE);
  counter++;
}

// Reading signal everytime the button is pushed
void buttonISR() {
  //  Debouncing 
  if (millis()-t>debouncingTime) {
  SINE_FREQ = analogRead(res);
  SINE_FREQ = SINE_FREQ/1023*175;
  t = millis();
  }
}
