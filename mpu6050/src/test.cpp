#include <Arduino.h>
#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

void setup() {
  Serial.begin(115200);
  Wire.begin();

  mpu6050.begin();
}

void loop() {
  mpu6050.update();

  Serial.print("AccX: ");
  Serial.print(mpu6050.getAccX());

  Serial.print(" | AccY: ");
  Serial.print(mpu6050.getAccY());

  Serial.print(" | AccZ: ");
  Serial.println(mpu6050.getAccZ());

  delay(200);
}