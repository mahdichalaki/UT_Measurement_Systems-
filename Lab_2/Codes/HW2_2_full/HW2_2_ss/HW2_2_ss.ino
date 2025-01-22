int start_stop = 2;             // digital pin 2 has a pushbutton attached to it.
int reset_button = 3;           // digital pin 2 has a pushbutton attached to it.
volatile bool state = false;    // defining state boolean as a global variable 
volatile long t = 0;            // defining t as long to keep the time
int debouncingTime = 200;       // defining debouncing time as milliseconds
volatile long f = 0;
volatile long d = 0;
volatile long s = 0;


void setup() {
  Serial.begin(9600);
  pinMode (start_stop, INPUT_PULLUP);                                           // declaring start_stop pin as digital input
  pinMode (reset_button, INPUT_PULLUP);                                         // declaring start_stop pin as digital input
  attachInterrupt (digitalPinToInterrupt(start_stop), buttonISR, FALLING);    // declaring reset pin as hardware interrupt

}

void loop() {

  t = millis() - s;

}



/****** ISR ******/
void buttonISR() {
  if (millis()-d > debouncingTime) { 
    state = !state;                        // toggling state boolean in case button is pushed
    if (state) {
      s = millis();  
    }

  else if (state == false) {
      f = f + t;
      Serial.println (f);
    }
    
    d = millis();
  }
}
