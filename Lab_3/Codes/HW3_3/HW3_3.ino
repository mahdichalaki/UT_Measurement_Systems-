#include <TimerOne.h>
#define PWMOUT 11
#define ADC_CHANNEL A0

float SINE_FREQ;
float SINE_COEFF;

// Output should be in 0-5 volt range
float Amp = 2.5 /5*255, Offset = 2.5/5*255;

int DUTYCYCLE , SAMPLE;
long TIMESTAMP, counter = 0;

void setup() {
    
  TCCR2B = TCCR2B & B11111000 | B00000001;              // Sets Timer 2 PWM frequency to 31KHz
  
  pinMode(PWMOUT, OUTPUT);
  Serial.begin (57600);
  Timer1.initialize (1000);
  Timer1.attachInterrupt (PWM_DT); 
}

void loop() {

  // For 1-15 Hz, generates 1000 data points for each
  for (int i = 1 ; i <= 15 ; i++)
  {
    SINE_FREQ = i;
    SINE_COEFF = SINE_FREQ * TWO_PI/1000.000;
    for (int j = 0 ; j < 1000 ; j++)
    {
      // Timestamp for each sample to be analyzed later
      TIMESTAMP = micros();     

      // Using Arduino's ADC to read the PWM output voltage
      SAMPLE = analogRead(ADC_CHANNEL);
      Serial.print (TIMESTAMP/100); Serial.print("\t");
      Serial.println (SAMPLE/1023.00*5);
    }
  }

  // For 20:10:170 Hz, generates 100 data points for each
    for (int i = 20 ; i < 171 ; i+=10)
  {
    SINE_FREQ = i;
    SINE_COEFF = SINE_FREQ * TWO_PI/1000.000;
    for (int j = 0 ; j < 100 ; j++)
    {
      TIMESTAMP = micros(); 
      SAMPLE = analogRead(ADC_CHANNEL);
      Serial.print (TIMESTAMP/100); Serial.print("\t");
      Serial.println (SAMPLE/1023.00*5);
    }
  }
}

// Function for generating PWM signal
void PWM_DT(){
  DUTYCYCLE = Amp * sin(SINE_COEFF * counter) + Offset;
  analogWrite(PWMOUT, DUTYCYCLE);
  counter++;
}
