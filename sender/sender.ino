#include "BluetoothSerial.h"

#define SWITCH_PIN 2  // Replace with the actual pin connected to your switch

BluetoothSerial SerialBT;

String MACadd = "AC:67:B2:59:5C:4E"; // Write Drone side MAC address
uint8_t address[6] = {0xAC, 0x67, 0xB2, 0x59, 0x5C, 0x4E};

bool connected;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32SwitchController", true);
  Serial.println("Device started in master mode. Ensure the remote BT device is on!");

  connected = SerialBT.connect(address);

  if (connected) {
    Serial.println("Connected Successfully!");
  } else {
    while (!SerialBT.connected(10000)) {
      Serial.println("Failed to connect. Ensure the remote device is available and in range, then restart the app.");
    }
  }

  pinMode(SWITCH_PIN, INPUT);
}

void loop() {
  // Check if the switch is pressed
  if (digitalRead(SWITCH_PIN) == HIGH) {
    // Your switch logic goes here
    // For example, send the command only when the switch is pressed
    char command = 'O'; // Default command (for example, 'O' for Open)
    
    SerialBT.write(command); // Send the command over Bluetooth
    
    delay(1000); // Adjust delay as needed based on your application
  }
}
