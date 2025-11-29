#include <SPI.h>

const int SS_PIN = 4;   // SS naar Uno pin 10

void setup() {
  Serial.begin(9600);

  pinMode(SS_PIN, OUTPUT);
  digitalWrite(SS_PIN, HIGH);

  SPI.begin();

  SPI.beginTransaction(SPISettings(
    1000000,      // 1 MHz
    MSBFIRST,     
    SPI_MODE0
  ));
}

void loop() {
  byte dataToSend = 0x55;
  
  digitalWrite(SS_PIN, LOW);          // select Uno
  byte received = SPI.transfer(dataToSend);  // send + receive tegelijk
  digitalWrite(SS_PIN, HIGH);         // deselect Uno

  Serial.print("Sent: 0x");
  Serial.print(dataToSend, HEX);
  Serial.print("   Received: 0x");
  Serial.println(received, HEX);

  delay(500);
}
