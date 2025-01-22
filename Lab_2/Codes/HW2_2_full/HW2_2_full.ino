#include <TimerOne.h>
volatile bool ledState=HIGH;    // defining ledState boolean to keep the record of LED's state

int start_stop = 2;             // digital pin 2 has a pushbutton attached to it.
int reset_button = 3;           // digital pin 2 has a pushbutton attached to it.
volatile bool state = false;    // defining state boolean as a global variable 
volatile long t = 0;            // defining t as long to keep the time
int debouncingTime = 200;       // defining debouncing time as milliseconds
volatile long f = 0;            // cumulative time
volatile long d = 0;            // used for debouncing
volatile long s = 0;            // save starting point of the current window
int second = 0;                 // save passed seconds
int milli = 0;                  // save passed miliseconds
int mins = 0;                   // save passed minutes


void setup() {
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  // use built-in LED
  pinMode(LED_BUILTIN, OUTPUT);

  // initialize timer1 with a period of 1s
  Timer1.initialize(1000000);

  // blinkLED to run once overy seconds
  Timer1.attachInterrupt(blinkLED);

  // declaring start_stop pin as digital input
  pinMode (start_stop, INPUT_PULLUP);

  // declaring reset pin as digital input
  pinMode (reset_button, INPUT_PULLUP);

  // declaring start_stop pin as hardware interrupt
  attachInterrupt (digitalPinToInterrupt(start_stop), start_stopISR, FALLING);

  // declaring reset pin as hardware interrupt
  attachInterrupt (digitalPinToInterrupt(reset_button), ResetISR, FALLING);
}

void loop() {

  // calculate passed time in the currrent window
  t = millis() - s;

}


/****** start_stopISR ******/
void start_stopISR() {
  if (millis()-d > debouncingTime) { 

    // toggling state boolean in case button is pushed
    state = !state;
    if (state) {

      // set new starting point each time the chronometer starts
      s = millis();  
    }

  else if (state == false) {

      // sum up total passed time each time the chronometer stops
      f = f + t;

      // change from miliseconds to "mins:seconds:miliseconds"
      mins = (f/(60000))%60;
      second = (f/1000)%60;
      milli = f % 1000;

      // print elapsed time
      Serial.print(mins);
      Serial.print(" : ");
      Serial.print(second);
      Serial.print(" : ");
      Serial.println(milli);
    }

    // used foe debouncing
    d = millis();
  }
}

/****** ResetISR ******/
void ResetISR() {
  if (millis()-d>debouncingTime) { 

    // set elapsed time to zero
    f = 0;

    // start new time window
    s = millis();

    // used foe debouncing
    d = millis();
  }
}


/****** blinkLED ******/
void blinkLED() {

  // toggle LED
  digitalWrite(LED_BUILTIN, ledState);

  // keep the record of LED's state
  ledState=!ledState;
}
 
