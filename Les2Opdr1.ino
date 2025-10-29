const int ledPin = 13;

const int switchPin = 2;

volatile bool ledState = false;

void toggleLED() {
  ledState = !ledState;           
  digitalWrite(ledPin, ledState);
}

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);


  attachInterrupt(digitalPinToInterrupt(switchPin), toggleLED, FALLING);
}

void loop() {
}
