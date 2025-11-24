#include <avr/io.h>
#include <util/delay.h>

#define FAN_CTRL_PIN PB1  // Arduino pin connected to optocoupler LED

int main(void) {
    // Set pin as output
    DDRB |= (1 << FAN_CTRL_PIN);

    while(1) {
        // FAN ON for 3 seconds
        PORTB |= (1 << FAN_CTRL_PIN);
        for(uint8_t t = 0; t < 3; t++) _delay_ms(1000);

        // FAN OFF for 10 seconds
        PORTB &= ~(1 << FAN_CTRL_PIN);
        for(uint8_t t = 0; t < 10; t++) _delay_ms(1000);
    }
}
