#include <Arduino.h>


void setup() {
  Serial.begin(115200);   // xem trên PC
  Serial1.begin(9600);    // nhận từ ESP32


}

void loop() {
  if(Serial1.available() > 0){
    String data = Serial1.readStringUntil('\n');    // Đọc dữ liệu được gửi sang và gán vào data
    Serial.print("Nhan Du Lieu Tu ESP32: ");
    Serial.println(data);   // In giá trị gửi sang
    delay(1000);
    Serial.println("=>An Da an Thong Tin");
    delay(1000);
  }
}
/*
  Arduino sử dụng Serial1 để đọc dữ liệu từ esp32 gửi sang ( chân rx1 và tx1 trên mega2560) 
    và phải đồng bộ baudrate với bên esp32 gửi sang
  Để in ra thì chỉ cần sử dụng Serial không cần 1 hay 2
*/
