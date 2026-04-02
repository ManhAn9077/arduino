#include <Arduino.h>
#include <SoftwareSerial.h>
int left1 = 5;
int left2 = 6;
int right1 = 9;
int right2 = 10;

SoftwareSerial mySerial(2, 3); // RX, TX

void setup() {
  Serial.begin(115200);     // debug PC
  mySerial.begin(9600);     // nhận ESP32
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);
}

void loop() {
  if (mySerial.available()) {
    //Nhan du lieu esp32
    int left = mySerial.parseInt(); // -128 → 127
    int right = mySerial.parseInt();

    Serial.print("L: ");Serial.println(left);
    Serial.print("R: ");Serial.println(right);
    // Dieu khien dong co
    if (right > 10){
      int speedR = map(right,10,127,0,255);
      analogWrite(right1,speedR);
      analogWrite(right2,0);
      Serial.println(" >5 ");Serial.print("speedR : ");Serial.println(speedR);
    }
    else if (right < -10){
      int speedR = map(abs(right),10,127,0,255);
      analogWrite(right1,0);
      analogWrite(right2,speedR);
      Serial.println(" <-5 ");Serial.print("speedR : ");Serial.println(speedR);
    }
    else{
      int speedR = 0;
      analogWrite(right1,speedR);
      analogWrite(right2,0);
    }
    if ( left > 10){
      int speedL = map(left,10,127,0,255);
      analogWrite(left1,speedL);
      analogWrite(left2,0);
      Serial.println(" >5 ");Serial.print("speedL : ");Serial.println(speedL);
    }
    else if ( left < -10){
      int speedL = map(abs(left),10,127,0,255);
      analogWrite(left1,0);
      analogWrite(left2,speedL);
      Serial.println(" < -5 ");Serial.print("speedL : ");Serial.println(speedL);
    }
    else{
      int speedL = 0;
      analogWrite(left1,speedL);
      analogWrite(left2,0);
    }
  }
}