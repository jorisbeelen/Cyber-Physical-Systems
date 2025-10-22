#include <SPI.h>              // Include SPI library
#include <WiFiNINA.h>         // Include WiFiNINA library

void setup() {
  Serial.begin(9600);         // Start communication at 9600 baud
  while (!Serial);            // Wait for serial monitor
}

void loop() {
  if (WiFi.status() == WL_NO_MODULE) {    // Check if WiFi module is detected
    Serial.println("WiFi module not found!");  // Print error if no module
    while (true);                       // Stop running if WiFi module is missing
  }

  Serial.println("Scanning available networks...");  // Tell the user that were scanning
  int numNetworks = WiFi.scanNetworks();              // Scan for nearby WiFi networks

  Serial.print("Number of networks found: ");         // Print number of networks found
  Serial.println(numNetworks);

  for (uint8_t i = 0; i < numNetworks; i++) {         // Loop through each found network
    Serial.print("Network: ");
    Serial.print(WiFi.SSID(i));                       // Print the SSID
    Serial.print(" | Signal Strength: ");
    Serial.print(WiFi.RSSI(i));                       // Print the signal strength
    Serial.print(" dBm | Encryption: ");
    Serial.println(WiFi.encryptionType(i));           // Print encryption type
  }

  delay(30000);   // Wait 30 seconds before scanning again
}

