#include <SPI.h>
#include <WiFiNINA.h>

const int D6 = 6;
const int Analog = A1;
int SensorValue =0;

void setup() {

pinMode(D6, OUTPUT);
pinMode(Analog, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

digitalWrite(D6, HIGH);
delay(500);
digitalWrite(D6, LOW);
SensorValue = analogRead(Analog);
Serial.println(SensorValue);
delay(500);
}
