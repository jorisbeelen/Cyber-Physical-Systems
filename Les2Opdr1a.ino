#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t ledState = 0;

ISR(INT0_vect) {
  ledState ^= (1 << PORTB5);
  PORTB = (PORTB & ~(1 << PORTB5)) | ledState;
}

int main(void) {

  DDRB |= (1 << DDB5);

  DDRD &= ~(1 << DDD2);
  PORTD |= (1 << PORTD2);

  EICRA |= (1 << ISC01);
  EICRA &= ~(1 << ISC00);

  EIMSK |= (1 << INT0);

  sei();

  while (1) {
  }

  return 0;
}
