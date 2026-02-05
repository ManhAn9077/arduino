#include <Arduino.h>
#define phai 10
#define trai 11


void setup() {
  Serial.begin(115200);   // xem trên PC
  Serial1.begin(9600);    // nhận từ ESP32

  pinMode(phai, OUTPUT);
  pinMode(trai, OUTPUT);

}

void loop() {
  if (Serial1.available()) {
    int speed = Serial1.parseInt(); // -128 → 127
    speed = constrain(speed, -127, 127);

    Serial.println(speed); // debug

    if (speed > 15) {
      analogWrite(phai, 200);
      analogWrite(trai, 0);
    
    }
    else if (speed < -15) {
      analogWrite(phai, 0);
      analogWrite(trai, 200);
      
    }
    else {
      analogWrite(phai, 0);
      analogWrite(trai, 0);
      
    }
  }
}
