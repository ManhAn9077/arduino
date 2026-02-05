#include<Arduino.h>
int trai1 = 10;
int phai1 = 9;
int trai2 = 6;
int phai2 = 7;
int nut1 = 8;
int nut3 = 11;
void setup(){
  pinMode(trai1,OUTPUT);
  pinMode(phai1,OUTPUT);
  pinMode(trai2,OUTPUT);
  pinMode(phai2,OUTPUT);
  pinMode(nut1,INPUT_PULLUP);
  pinMode(nut3,INPUT_PULLUP);
  Serial.begin(9600);
}
void loop(){
  Serial.println(digitalRead(nut3));
  
if (digitalRead(nut1) == 0 && digitalRead(nut3) == 1) {
  // ===== CHẠY =====
  analogWrite(trai1, 0);
  analogWrite(phai1, 200);
  analogWrite(trai2, 0);
  analogWrite(phai2, 200);
} 
else if (digitalRead(nut1) == 1 && digitalRead(nut3) == 0) {
  // ===== CHẠY =====
  analogWrite(trai1, 200);
  analogWrite(phai1, 0);
  analogWrite(trai2, 200);
  analogWrite(phai2, 0);
} 
else {
  // ===== DỪNG =====
  analogWrite(trai1, 0);
  analogWrite(phai1, 0);
  analogWrite(trai2, 0);
  analogWrite(phai2, 0);
}

  



}