#include <Arduino.h>
#include <PS4Controller.h>


void setup() {
  Serial.begin(115200);                     // debug
  Serial2.begin(9600, SERIAL_8N1, 17, 16); 

  PS4.begin("70:4b:ca:45:f4:26"); // MAC ESP32
  Serial.println("Waiting for PS4...");
}

void loop() {
  if (PS4.isConnected()) {
    //Lay Du Lieu Tu Tay Cam
    int y = PS4.LStickY();   
    int x = PS4.LStickX();
    //Serial.print("Gia Tri X : ");Serial.println(x);
    //Serial.print("Gia Tri Y : ");Serial.println(y);
    int left = y + x;
    left = constrain(left, -127, 127);
    int right = y - x ;
    right = constrain(right, -127, 127);
    Serial2.print(left);
    Serial2.print(",");
    Serial2.println(right);
    delay(20);
  }

}
