#include <TimerOne.h>
#define PWMOUT_1 11
#define ADC_CHANNEL A0

float SINE_FREQ_1 = 5.34;     // First signal Frequency
float SINE_FREQ_2 = 74.645;   // Second signal Frequency

float SINE_COEFF_1 = SINE_FREQ_1 * TWO_PI/1000.000 ,SINE_COEFF_2 = SINE_FREQ_2 * TWO_PI/1000.000;

// Output should be in 0-5 volt range
float Amp=1.25/5*255, Offset=2.5/5*255;

int DUTYCYCLE , SAMPLE;
long TIMESTAMP, counter = 0;

void setup() {
    
  TCCR2B = TCCR2B & B11111000 | B00000001;              // Sets Timer 2 PWM frequency to 31KHz
  pinMode(PWMOUT_1, OUTPUT);
  Serial.begin (57600);
  Timer1.initialize (1000);
  Timer1.attachInterrupt (PWM_DT);
  
}

void loop() {
  TIMESTAMP = micros();                                   // Timestamp for each sample to be analyzed later
  SAMPLE = analogRead(ADC_CHANNEL);                       // Using Arduino's ADC to read the PWM output voltage
  Serial.print (TIMESTAMP/100); Serial.print("\t");       // Printing timestamp
  Serial.println (SAMPLE/1023.00*5);
}

// Function for generating PWM signal
void PWM_DT(){
  // Adding two signals
  DUTYCYCLE = Amp * (sin(SINE_COEFF_1 * counter)+ sin(SINE_COEFF_2 * counter)) + Offset;
  analogWrite(PWMOUT_1, DUTYCYCLE);  
  counter++;
}
