/*
 * Lab 4 - Actuators
 * Exercise 1A: Bare metal LED control
 * Hardware:
 * - LED connected to transistor base through 1k resistor (Arduino pin 9)
 * - Transistor emitter to GND
 * - LED or fan powered from +5V through diode
 */

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB |= (1 << PB1);

    while (1)
    {
        // LED on
        PORTB |= (1 << PB1);
        _delay_ms(3000);

        // LED off
        PORTB &= ~(1 << PB1);
        _delay_ms(1000);
    }

    return 0;
}
