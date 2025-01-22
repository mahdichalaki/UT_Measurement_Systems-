int pushbutton = 2;             // digital pin 2 has a pushbutton attached to it.
volatile bool state = false;    // defining state boolean as a global variable 
volatile long t = 0;            // defining t as long to keep the time
int debouncingTime = 200;       // defining debouncing time as milliseconds
float f;

/****** Setup ******/
void setup() {

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // declaring pushButton pin as digital input
  pinMode (pushbutton, INPUT_PULLUP);

  // declaring led as digital output
  pinMode(LED_BUILTIN, OUTPUT);

  // declaring pin 2 as hardware interrupt
  attachInterrupt (digitalPinToInterrupt(2), buttonISR, FALLING);
}

/****** Main Loop ******/
void loop() {

  // get current time and print it
  f = millis();
  Serial.println (millis());
  digitalWrite(LED_BUILTIN, HIGH);
  delay (1000);                         // waiting for 1s
  if (state) {                          // checking state boolean. If true, then turn off the LED for 1s, if false, do nothing
  digitalWrite(LED_BUILTIN, LOW);       // turning LED off
  delay (1000);                         // waiting for 1s
  }
  
}


/****** ISR ******/
void buttonISR() {
  if (millis()-t>debouncingTime) {
    state=! state;                        // toggling state boolean in case button is pushed
    t = millis();
  }
}
 
