#include "BluetoothSerial.h"
#include <ESP32Servo.h>

BluetoothSerial SerialBT;
Servo myservo;  // create servo object to control a servo

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); // Bluetooth device name
  Serial.println("The device started, now you can pair it with Bluetooth!");

  myservo.attach(13);  // attaches the servo on pin 13 to the servo object
}

void loop() {
  uint8_t recv_data;
  if (SerialBT.available()) {
    recv_data = SerialBT.read();

    if (recv_data != 'O' && recv_data != 'C') {
      Serial.println("Invalid data received!");
      return;
    }

    Serial.printf("Command: %c\n", recv_data);

    if (recv_data == 'O') {
      // Control the servo to open position
      myservo.write(90);  // Set servo to a specific angle (e.g., 90 degrees for open)
      delay(1000); // Add delay if needed
    } else if (recv_data == 'C') {
      // Control the servo to close position or another desired state
      myservo.write(0);  // Set servo to a specific angle (e.g., 0 degrees for close)
      delay(1000); // Add delay if needed
    }
  }
  delay(20);
}
