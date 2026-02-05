#include <Arduino.h>

void setup() {
  Serial2.begin(9600, SERIAL_8N1, 16, 17);  // RX2, TX2 , khai báo cổng sử dụng
}

void loop() {
    Serial2.println("Chào An");      // 👈 GỬI SANG ARDUINO     
}
/*
  Sử dụng Serial2 để gửi dữ liệu từ esp32 sang arduino ( Chân Rx2 , Tx2) và cùng boudrate với bên nhận
*/