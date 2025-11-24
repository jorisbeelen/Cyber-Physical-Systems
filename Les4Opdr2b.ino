#include <avr/io.h>
#include <util/delay.h>

#define FAN_PIN PB1     // Pin 9 on Arduino Uno
#define POT_PIN PC0     // A0 on Arduino Uno

// Initialize ADC (Analog-to-Digital Converter)
void adc_init(void) {
    ADMUX = (1 << REFS0);           // AVcc as reference, ADC0 as input
    ADCSRA = (1 << ADEN) |          // Enable ADC
             (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler 128
}

// Read ADC value (0-1023)
uint16_t adc_read(void) {
    ADCSRA |= (1 << ADSC);          // Start conversion
    while(ADCSRA & (1 << ADSC));    // Wait until conversion completes
    return ADC;
}

// Initialize hardware PWM (Timer1, 8-bit Fast PWM on PB1/OC1A)
void pwm_init(void) {
    DDRB |= (1 << FAN_PIN);                     // Set pin as output
    TCCR1A = (1 << COM1A1) | (1 << WGM10);     // Fast PWM 8-bit, non-inverting
    TCCR1B = (1 << WGM12) | (1 << CS10);       // No prescaler
}

// Set PWM duty cycle (0-255)
void set_pwm(uint8_t duty) {
    OCR1A = duty;
}

int main(void) {
    pwm_init();
    adc_init();

    while(1) {
        // Fan off for 15 seconds
        set_pwm(0);
        for(uint8_t t = 0; t < 15; t++) _delay_ms(1000);

        // Fan on for 5 seconds, speed controlled by potentiometer
        for(uint8_t t = 0; t < 5; t++) {
            uint16_t pot_value = adc_read();   // Read potentiometer (0-1023)
            uint8_t pwm_value = pot_value / 4; // Map to PWM range (0-255)
            set_pwm(pwm_value);
            _delay_ms(1000);
        }

        // Fan off
        set_pwm(0);
    }
}
