#include <Arduino.h>
#include <PS4Controller.h>

void setup() {
  Serial.begin(115200);                     // debug
  Serial2.begin(9600, SERIAL_8N1, 16, 17);  // RX2, TX2

  PS4.begin("d8:bc:38:f7:b6:82"); // MAC ESP32
  Serial.println("Waiting for PS4...");
}

void loop() {
  if (PS4.isConnected()) {
    int speed = PS4.LStickY();   // -128 → 127

    Serial2.println(speed);      // 👈 GỬI SANG ARDUINO
    Serial.println(speed);       // debug

    delay(20);                   // ~50Hz
  }
}
