#include <avr/io.h>
#include <util/delay.h>

#define FAN_PIN PB1 // Pin 9 op Arduino Uno

void set_pwm(uint8_t duty)
{
    // Timer1 Fast PWM, 8-bit, non-inverting
    // duty 0-255
    OCR1A = duty;
}

void pwm_init(void)
{
    // Pin als output
    DDRB |= (1 << FAN_PIN);

    // Timer1 8-bit Fast PWM op PB1 (OC1A)
    TCCR1A = (1 << COM1A1) | (1 << WGM10);
    TCCR1B = (1 << WGM12) | (1 << CS10); // geen prescaler
}

int main(void)
{
    pwm_init();

    while(1)
    {
        // Ventilator uit voor 15 seconden
        set_pwm(0);
        for (uint8_t t = 0; t < 15; t++) _delay_ms(1000);

        // Ventilator aan voor 5 seconden, soft start
        uint8_t duty = 0;
        while(duty <= 255)
        {
            set_pwm(duty);
            _delay_ms(1000);
            duty += 51; // 5 stappen tot max
        }

        // Ventilator uit na 5 seconden
        set_pwm(0);
    }
}
