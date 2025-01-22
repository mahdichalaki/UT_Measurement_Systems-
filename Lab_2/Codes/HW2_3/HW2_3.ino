int sensor = 2;              // Pin 2 has a sensor attached to it.
int v = 0;                   // voltage of the sensor
int slots = 40;              // nuber of slots on the encoder
int counter = 0;             // counts number of changes
int x = 0;                   // position
int res;                     // resolution of the encoder
volatile long t = 0;         // prevoius time
volatile long d = 0;         // current time
int debouncingTime = 5;      // used to avoid multiple output
float omega;                 // angular velocity of the disk


/****** Setup ******/

void setup() {

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // Define sensor as an input
  pinMode(sensor, INPUT);

  // Define builtin LED as an output
  pinMode(LED_BUILTIN, OUTPUT);

  // declaring sensor pin as hardware interrupt
  attachInterrupt (digitalPinToInterrupt(sensor), sensorISR, CHANGE);

  // reolution of the encoder
  res = 360 / slots;

}

/****** Main Loop ******/

void loop() {

}

/****** sensorISR ******/

void sensorISR() {
  if (millis()-t > debouncingTime) {

    // count state changes
    counter ++;

    // calculate and print position
    x = counter * res;
    Serial.print("Position: ");
    Serial.print(x);
    Serial.println(" Deg");

    // get current time
    d = millis();

    // calculate and print angular velocity
    omega = 1000 * res / (d - t);
    Serial.print("Ang Velocity: ");
    Serial.print(omega);
    Serial.println(" Deg/s");

    // save time for the next loop
    t = millis();

    // blink LED for every pulse
    digitalWrite(LED_BUILTIN, 1);
    delay(2);
    digitalWrite(LED_BUILTIN, 0);
  }
}
