#include "sam.h"           // Include the SAMD21 hardware definitions

#define LED_PIN 10          // PB10 = D4 on the MKR1010
#define PORT_GROUP 1        // Group[1] corresponds to PORTB (Group[0] = PORTA)

void setup() {
  // Enable the clock for the PORT module (required for pin configuration)
  PM->APBBMASK.reg |= PM_APBBMASK_PORT;

  // Configure PB10 as OUTPUT by setting the bit in the DIRSET register
  PORT->Group[PORT_GROUP].DIRSET.reg = (1 << LED_PIN);
}

void loop() {
  // Turn LED ON
  PORT->Group[PORT_GROUP].OUTSET.reg = (1 << LED_PIN);
  delay(1000); // Wait 1 second

  // Turn LED OFF
  PORT->Group[PORT_GROUP].OUTCLR.reg = (1 << LED_PIN);
  delay(1000); // Wait 1 second
}
