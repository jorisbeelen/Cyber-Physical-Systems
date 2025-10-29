#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t ledState = 0;

ISR(TIMER1_COMPA_vect) {
  ledState ^= (1 << PORTB5);
  PORTB = (PORTB & ~(1 << PORTB5)) | ledState;
}

int main(void) {
  DDRB |= (1 << DDB5);

  TCCR1B |= (1 << WGM12);


  OCR1A = 15624;

  TCCR1B |= (1 << CS12) | (1 << CS10);

  TIMSK1 |= (1 << OCIE1A);

  sei();

  while (1) {

  }

  return 0;
}
