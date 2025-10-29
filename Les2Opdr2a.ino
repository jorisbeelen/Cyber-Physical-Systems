#include <avr/io.h>
#include <avr/interrupt.h>

volatile bool ledState = false;

ISR(PCINT0_vect) {

  if (digitalRead(8) == LOW) {
    ledState = !ledState;
    digitalWrite(13, ledState);
  }
}

void setup() {
  pinMode(13, OUTPUT);
  pinMode(8, INPUT_PULLUP);

  PCICR |= (1 << PCIE0);
  PCMSK0 |= (1 << PCINT0);

  sei();

void loop() {
  
}
