#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t ledState = 0;

ISR(PCINT0_vect) {

  if (!(PINB & (1 << PINB0))) {
    ledState ^= (1 << PORTB5);
    PORTB = (PORTB & ~(1 << PORTB5)) | ledState;
  }
}

int main(void) {
  DDRB |= (1 << DDB5);

  DDRB &= ~(1 << DDB0);
  PORTB |= (1 << PORTB0);

  PCICR |= (1 << PCIE0);
  PCMSK0 |= (1 << PCINT0);

  sei();

  while (1) {

  }

  return 0;
}
