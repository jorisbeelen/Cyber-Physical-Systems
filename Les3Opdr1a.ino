#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

volatile uint8_t wakeFlag = 0;  // Flag that indicates the MCU was woken by the timer interrupt

// Interrupt Service Routine for Timer1 Compare Match A
ISR(TIMER1_COMPA_vect)
{
    wakeFlag = 1;  // Set the flag when the timer interrupt occurs
}

int main(void)
{
    DDRB |= (1 << DDB5);   // Configure PB5 (LED pin) as output

    // --- Timer1 configuration ---
    TCCR1B |= (1 << WGM12);              // Set CTC mode (Clear Timer on Compare Match)
    OCR1A = 15624;                       // 1 second at 16 MHz / 1024 prescaler
    TCCR1B |= (1 << CS12) | (1 << CS10); // Set prescaler to 1024
    TIMSK1 |= (1 << OCIE1A);             // Enable Timer1 Compare Match A interrupt

    sei(); // Enable global interrupts

    set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Set the deepest sleep mode (Power-down)

    while (1)
    {
        sleep_enable();   // Allow the MCU to enter sleep
        sleep_cpu();      // MCU goes to sleep and waits for interrupt

        sleep_disable();  // MCU wakes up after the interrupt

        // Check if the wake-up flag was set by the interrupt
        if (wakeFlag)
        {
            PORTB |= (1 << PORTB5);   // Turn ON the LED
            _delay_ms(100);           // Keep the LED ON for 100 milliseconds
            PORTB &= ~(1 << PORTB5);  // Turn OFF the LED
            wakeFlag = 0;             // Clear the flag
        }
    }
}
