int res = A1;
float Value;
volatile long t = 0; 
int debouncingTime = 200;
#define record 2

void setup() {
  Serial.begin(9600);
  pinMode (record, INPUT_PULLUP);
  pinMode(res, INPUT);
  attachInterrupt (digitalPinToInterrupt(record), buttonISR, FALLING);

}

void loop() {
  Serial.println(Value/1023*175);
}

void buttonISR() {
  if (millis()-t>debouncingTime) {
  Value = analogRead(res);
  t = millis();
  }
}
