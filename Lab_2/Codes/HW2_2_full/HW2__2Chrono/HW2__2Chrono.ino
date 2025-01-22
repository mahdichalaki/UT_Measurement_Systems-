int start_stop = 2;             // digital pin 2 has a pushbutton attached to it.
int reset_button = 3;           // digital pin 2 has a pushbutton attached to it.
volatile bool state = false;    // defining state boolean as a global variable 
volatile long t = 0;            // defining t as long to keep the time
int debouncingTime = 200;       // defining debouncing time as milliseconds
volatile long f = 0;


/****** Setup ******/
void setup() {
  Serial.begin(9600);
  pinMode (start_stop, INPUT_PULLUP);                                           // declaring start_stop pin as digital input
  pinMode (reset_button, INPUT_PULLUP);                                         // declaring start_stop pin as digital input
  attachInterrupt (digitalPinToInterrupt(reset_button), buttonISR, FALLING);    // declaring reset pin as hardware interrupt
}

/****** Main Loop ******/
void loop() {
  /*
  f = millis();
  Serial.println (millis());
  digitalWrite(LED_BUILTIN, HIGH);
  delay (1000);                         // waiting for 1s
  if (state) {                          // checking state boolean. If true, then turn off the LED for 1s, if false, do nothing
  digitalWrite(LED_BUILTIN, LOW);       // turning LED off
  delay (1000);                         // waiting for 1s
  */
  f = millis() - t;
  Serial.println (f);
  
  }
  


/****** ISR ******/
void buttonISR() {
  if (millis()-t>debouncingTime) { 
    //state=! state;                        // toggling state boolean in case button is pushed
    t = millis();
  }
}
 
