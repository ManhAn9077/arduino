#include <Arduino.h>
#define nutan 22 
#define trigTrai  12
#define echoTrai  13
#define trigCheoTrai 44
#define echoCheoTrai  46
#define trigTruoc 40
#define echoTruoc 42
#define trigSau 28
#define echoSau 26
#define trigPhai  32
#define echoPhai  34
#define trigCheoPhai  36
#define echoCheoPhai  38
#define hongngoaiTT  48
#define hongngoaiTP  52
#define hongngoaiS  50
#define Lui_Phai  2        // Lui - RPWM
#define Tien_Phai  3        // Tien - LPWM
#define Lui_Trai  4    // Lui - RPWM
#define Tien_Trai  5       // Tien - LPWM
bool phathienhongngoaiTT ;
bool phathienhongngoaiTP ;
bool phathienhongngoaiS ;
int distance[6];
int gocsieuam[5] = {-90 , -45 , 0 , 45 ,90 };
int m[5];
int lastgoc = 0;
unsigned long lasttarget = 0;
int lasthuongescape = 0;


//int distanceSau;
// int distancePhai;
// int distanceTruoc;
// int distanceCheoTrai;
// int distanceCheoPhai;
int TrangThaiHongNgoaiTT ;
int TrangThaiHongNgoaiTP ;
int TrangThaiHongNgoaiS ;
unsigned long phathien ;
float Kp = 10;
float Kd = 1.6;






int state = 0 ;     // 0 : Tim Kiem   \ 1 : Tan Cong  \   2 : Tron




void setup() {
  Serial.begin(9600);     // debug PC
  // Cam Bien Sieu Am
  pinMode(trigTrai,OUTPUT);
  pinMode(echoTrai,INPUT);
  pinMode(trigCheoTrai,OUTPUT);
  pinMode(echoCheoTrai,INPUT);
  pinMode(trigCheoPhai,OUTPUT);
  pinMode(echoCheoPhai,INPUT);
  pinMode(trigTruoc,OUTPUT);
  pinMode(echoTruoc,INPUT);
  pinMode(trigSau, OUTPUT); 
  pinMode(echoSau, INPUT);
  pinMode(trigPhai,OUTPUT);
  pinMode(echoPhai,INPUT);
  pinMode(nutan,INPUT_PULLUP);
  // Cam Bien Hong Ngoai
  pinMode(hongngoaiTT,INPUT_PULLUP);
  pinMode(hongngoaiTP,INPUT_PULLUP);
  pinMode(hongngoaiS,INPUT_PULLUP);
  // Driver BTS
  pinMode(Lui_Phai,OUTPUT);
  pinMode(Tien_Phai,OUTPUT);
  pinMode(Lui_Trai,OUTPUT);
  pinMode(Tien_Trai,OUTPUT);
  Serial.println("\nTrai\tTrai Cheo\tTruoc\tPhai Cheo\tPhai\tGoc");
}

//======================================================================================================================================================================
                                                                                   // SIEU AM
//======================================================================================================================================================================
int sieuamSau(){
  digitalWrite(trigSau,LOW);     // Xu ly Cam Bien Sieu Am 
  delayMicroseconds(2);
  digitalWrite(trigSau,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigSau,LOW);
  long time = pulseIn(echoSau,HIGH,30000);
  if(time == 0){    
    return 100;     //Neu khong thu duoc -> khoangcach = 100 cm
  }
  int khoangcachSau = time/2/29.412;
  khoangcachSau = constrain(khoangcachSau,0,100);
  return khoangcachSau;
}
// Doc Cam Bien Sieu Am Trai
int sieuamTrai(){
  digitalWrite(trigTrai,LOW);     // Xu ly Cam Bien Sieu Am 
  delayMicroseconds(2);
  digitalWrite(trigTrai,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigTrai,LOW);
  long time = pulseIn(echoTrai,HIGH,30000);
  if(time == 0){    
    return 100;     //Neu khong thu duoc -> khoangcach = 100 cm
  }
  int khoangcachTrai = time/2/29.412;
  khoangcachTrai = constrain(khoangcachTrai,0,100);
  return khoangcachTrai;
}
// Doc Cam Bien Sieu Am Phai
int sieuamPhai(){
  digitalWrite(trigPhai,LOW);     // Xu ly Cam Bien Sieu Am 
  delayMicroseconds(2);
  digitalWrite(trigPhai,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPhai,LOW);
  long time = pulseIn(echoPhai,HIGH,30000);
  if(time == 0){    
    return 100;     //Neu khong thu duoc -> khoangcach = 100 cm
  }
  int khoangcachPhai = time/2/29.412;
  khoangcachPhai = constrain(khoangcachPhai,0,100);
  return khoangcachPhai;
}
// Doc Cam Bien Sieu Am Truoc
int sieuamTruoc(){
  digitalWrite(trigTruoc,LOW);     // Xu ly Cam Bien Sieu Am 
  delayMicroseconds(2);
  digitalWrite(trigTruoc,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigTruoc,LOW);
  long time = pulseIn(echoTruoc,HIGH,30000);
  if(time == 0){    
    return 100;     //Neu khong thu duoc -> khoangcach = 100 cm
  }
  int khoangcachTruoc = time/2/29.412;
  khoangcachTruoc = constrain(khoangcachTruoc,0,100);
  return khoangcachTruoc;
}
// Doc Cam Bien Sieu Am Cheo Trai
int sieuamCheoTrai(){
  digitalWrite(trigCheoTrai,LOW);     // Xu ly Cam Bien Sieu Am 
  delayMicroseconds(2);
  digitalWrite(trigCheoTrai,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigCheoTrai,LOW);
  long time = pulseIn(echoCheoTrai,HIGH,30000);
  if(time == 0){    
    return 100;     //Neu khong thu duoc -> khoangcach = 100 cm
  }
  int khoangcachCheoTrai = time/2/29.412;
  khoangcachCheoTrai = constrain(khoangcachCheoTrai,0,100);
  return khoangcachCheoTrai;
}
// Doc Cam Bien Sieu Am Cheo Trai
int sieuamCheoPhai(){
  digitalWrite(trigCheoPhai,LOW);     // Xu ly Cam Bien Sieu Am 
  delayMicroseconds(2);
  digitalWrite(trigCheoPhai,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigCheoPhai,LOW);
  long time = pulseIn(echoCheoPhai,HIGH,30000);
  if(time == 0){    
    return 100;     //Neu khong thu duoc -> khoangcach = 100 cm
  }
  int khoangcachCheoPhai = time/2/29.412;
  khoangcachCheoPhai = constrain(khoangcachCheoPhai,0,100);
  return khoangcachCheoPhai;
}
//======================================================================================================================================================================
                                                                                   // KHOANG CACH
//======================================================================================================================================================================
void ReadDistance(){
  distance[5] = sieuamSau();
  delayMicroseconds(200);
  distance[0] = sieuamTrai();
  delayMicroseconds(200);
  distance[1] = sieuamCheoTrai();
  delayMicroseconds(200);
  distance[2] = sieuamTruoc();
  delayMicroseconds(200);
  distance[3] = sieuamCheoPhai();
  delayMicroseconds(200);
  distance[4] = sieuamPhai();
}
//======================================================================================================================================================================
                                                                                     // STOP MOTOR
//======================================================================================================================================================================
void stopMotor(){
  analogWrite(Tien_Trai,0);
  analogWrite(Lui_Trai,0);
  analogWrite(Tien_Phai,0);
  analogWrite(Lui_Phai,0);
}
//======================================================================================================================================================================
                                                                                   // HONG NGOAI
//======================================================================================================================================================================
// Doc Cam Bien Hong Ngoai
void detecthongngoai(){
  // phathienhongngoaiTT = false;
  // phathienhongngoaiTP = false;
  // phathienhongngoaiS  = false;
  TrangThaiHongNgoaiTT = digitalRead(hongngoaiTT);
  TrangThaiHongNgoaiTP = digitalRead(hongngoaiTP);
  TrangThaiHongNgoaiS = digitalRead(hongngoaiS);
  //Serial.print("DIGITAL : ");Serial.println(TrangThaiHongNgoaiS);
  // Phat Hien Ca 2 cam Bien O Phia Truoc
  if( TrangThaiHongNgoaiTT == 0 && TrangThaiHongNgoaiTP == 0){
    phathienhongngoaiTP = true;
    phathienhongngoaiTT = true;
    phathien = millis();
    stopMotor();
    delay(2);
    state = 2;
    return;
  }
  // Phat Hien Cam Bien Truoc Trai
  else if (TrangThaiHongNgoaiTT == 0){
    phathienhongngoaiTT = true;
    phathien = millis();
    stopMotor();
    delay(2);
    state = 2;
    return;
  }
  // Phat Hien Cam Bien Truoc Phai
  else if (TrangThaiHongNgoaiTP == 0){
    phathienhongngoaiTP = true;
    phathien = millis();
    stopMotor();
    delay(2);
    state = 2;
    return;
  }
  // Phat Hien Cam Bien Sau
  else if (TrangThaiHongNgoaiS == 0){
    phathienhongngoaiS = true;
    phathien = millis();
    stopMotor();
    delay(2);
    state = 2;
    return;
  }
}
//======================================================================================================================================================================
                                                                                   // ESCAPE  
//======================================================================================================================================================================
void escape(){
  detecthongngoai();
  if (phathienhongngoaiTP == true || phathienhongngoaiTT == true){
    if (TrangThaiHongNgoaiS == 0){
      phathienhongngoaiTP = false ;
      phathienhongngoaiTT = false ;
      phathienhongngoaiS = true ;
    }
  }
  if ( ( phathienhongngoaiTP == true || phathienhongngoaiTT == true ) && lasthuongescape == 1){
    stopMotor();
    delay(2);
  }
  else if (phathienhongngoaiS == true && lasthuongescape == 0){
    stopMotor();
    delay(2);
  }
  // Cam Bien Sau Phat Hien
  if (phathienhongngoaiS == true){
    if ( millis() - phathien < 500){
      analogWrite(Tien_Trai,250);
      analogWrite(Lui_Trai,0);
      analogWrite(Tien_Phai,250);
      analogWrite(Lui_Phai,0);
      lasthuongescape = 1;
      Serial.println("ESCAPE : Sau");
    }
    else{
      phathienhongngoaiTT = false ;
      phathienhongngoaiTP = false ;
      phathienhongngoaiS = false ;
      stopMotor();
      delay(5);
      state = 0;
      return;
    }
  }
  // Ca 2 Cam Bien Phia Truoc Phat Hien
  else if ( phathienhongngoaiTP == true && phathienhongngoaiTT == true){
    if ( millis() - phathien < 500){
    analogWrite(Tien_Trai,0);
    analogWrite(Lui_Trai,250);
    analogWrite(Tien_Phai,0);
    analogWrite(Lui_Phai,250);
    lasthuongescape = 0;
    Serial.println("ESCAPE : Ca 2");
    }
    else{
      phathienhongngoaiTT = false ;
      phathienhongngoaiTP = false ;
      phathienhongngoaiS = false ;
      stopMotor();
      delay(5);
      state = 0;
      return;
    }
  }
  // Cam Bien Trai Truoc Phat Hien
  else if ( phathienhongngoaiTT == true){
    if ( millis() - phathien < 500){
      analogWrite(Tien_Trai,0);
      analogWrite(Lui_Trai,250);
      analogWrite(Tien_Phai,0);
      analogWrite(Lui_Phai,170);
      lasthuongescape = 0;
      Serial.println("ESCAPE : Trai TRUOC");
    }
    else{
      phathienhongngoaiTT = false ;
      phathienhongngoaiTP = false ;
      phathienhongngoaiS = false ;
      stopMotor();
      delay(5);
      state = 0;
      return;
    }
  }
  // Cam Bien Phai Truoc Phai Hien
  else if (phathienhongngoaiTP == true){
    if ( millis() - phathien < 500){
      analogWrite(Tien_Trai,0);
      analogWrite(Lui_Trai,170);
      analogWrite(Tien_Phai,0);
      analogWrite(Lui_Phai,250);
      lasthuongescape = 0;
      Serial.println("ESCAPE : Phai TRUOC");
    }
    else{
      phathienhongngoaiTT = false ;
      phathienhongngoaiTP = false ;
      phathienhongngoaiS = false ;
      stopMotor();
      delay(5);
      state = 0;
      return;
    }
  }
  
  

}
//======================================================================================================================================================================
                                                                                   // FIND
//======================================================================================================================================================================
void find(){          // Tim Kiem Doi Thu
  //detecthongngoai();
  if (state == 2) return;
  ReadDistance();
  if(lastgoc >= 0){
    Serial.println("Ham Tim Kiem lastgoc >= 0");
    analogWrite(Tien_Phai,0);
    analogWrite(Lui_Phai,200);
    analogWrite(Tien_Trai,200);
    analogWrite(Lui_Trai,0);
    for(int i = 0 ; i < 6 ; i++){
      if (distance[i] < 20){
        state = 1 ;
        stopMotor();
        return;
      }
    }
  }
  else {
    Serial.println("Ham Tim Kiem lastgoc < 0");
    analogWrite(Tien_Phai,200);
    analogWrite(Lui_Phai,0);
    analogWrite(Tien_Trai,0);
    analogWrite(Lui_Trai,200);
    for(int i = 0 ; i < 6 ; i++){
      if (distance[i] < 20){
        state = 1 ;
        stopMotor();
        return;
      }
    }
  }
  

}
//======================================================================================================================================================================
                                                                                   // ATTACK
//======================================================================================================================================================================
void attack() {
  
  //detecthongngoai();
  if (state == 2) return;
  ReadDistance();
  static int lasthuongT = 0 ;
  static int lasthuongP = 0 ;
  int tongtren = 0;
  int tongduoi = 0;
  int nearest = 100;
  if (distance[5] < 20){
    Serial.print("ATTACK : DAM DANG SAU : ");Serial.println(distance[6]);
    if (lasthuongP == 0){
      analogWrite(Tien_Phai,0);
      analogWrite(Lui_Phai,0);
      delay(2);
    }
    if (lasthuongT == 0){
      analogWrite(Tien_Trai,0);
      analogWrite(Lui_Trai,0);
      delay(2);
    }
    analogWrite(Tien_Phai,0);
    analogWrite(Lui_Phai,255);
    analogWrite(Tien_Trai,0);
    analogWrite(Lui_Trai,255);
    lasthuongP = 1;
    lasthuongT = 1;
    lasttarget = millis();
    lastgoc = 90;

  }
  else {
    for (int i  = 0 ; i < 5 ; i++){
      if(distance[i] <= 25){
        m[i] = 55 - distance[i];
        tongtren = tongtren + ( m[i] * gocsieuam[i]);
        tongduoi = tongduoi + m[i];
        if (distance[i] < nearest){
          nearest = distance[i];
        }
      }
    }
    if( tongduoi > 0){

      lasttarget = millis();
      int goc = tongtren / tongduoi ;
      goc = constrain(goc,-90,90);
      //In Serial
      char b[80];
      snprintf(b, sizeof(b), "%d\t%d\t\t%d\t%d\t\t%d\t%d", distance[0], distance[1], distance[2], distance[3], distance[4], goc);
      Serial.println(b);
      

      //Serial.print("Goc : "); Serial.println(goc);
      // if (nearest >=25 && abs(goc) > 20){
      //   int cantru = 40;
      //   //cantru = map(nearest,20,45,10,45);
      //   //cantru = constrain(cantru, 0, 45);
      //   if (goc >= 0){
      //     goc = goc - cantru;
      //   }
      //   else {
      //     goc = goc + cantru ;
      //   }
      // }
      // goc = constrain(goc,-90,90);
      int phatluc ;
      int triettieu ;
      triettieu = goc - lastgoc;

    
      phatluc = (Kp * goc) + (Kd*triettieu);
      
      
      int speedP;
      int speedT ;
      int basespeed =  250;
      speedP = basespeed - phatluc;
      speedT = basespeed + phatluc;
      speedP = constrain(speedP,-255,255);
      speedT = constrain(speedT,-255,255);
      if ( speedP >= 0 && lasthuongP == 1){
        analogWrite(Tien_Phai,0);
        analogWrite(Lui_Phai,0);  
        delay(2);
      }
      else if (speedP < 0 && lasthuongP == 0){
        analogWrite(Tien_Phai,0);
        analogWrite(Lui_Phai,0);  
        delay(2);
      }
      //Stop Motor Trai
      if ( speedT >= 0 && lasthuongT == 1){
        analogWrite(Tien_Trai,0);
        analogWrite(Lui_Trai,0);  
        delay(2);
      }
      else if (speedT < 0 && lasthuongT == 0){
        analogWrite(Tien_Trai,0);
        analogWrite(Lui_Trai,0);  
        delay(2);
      }
      // Dieu Khien Dong Co
      if (speedP >= 0){
        analogWrite(Tien_Phai,speedP);
        analogWrite(Lui_Phai,0);  
        lasthuongP = 0 ;
      }
      else{
        analogWrite(Tien_Phai,0);
        analogWrite(Lui_Phai,abs(speedP));
        lasthuongP = 1 ;
      }
      if (speedT >= 0){
        analogWrite(Tien_Trai,speedT);
        analogWrite(Lui_Trai,0);
        lasthuongT = 0 ;
      }
      else{
        analogWrite(Tien_Trai,0);
        analogWrite(Lui_Trai,abs(speedT));
        lasthuongT = 1 ;
      }
      lastgoc = goc ;
    }
    else {
      if ( millis() - lasttarget < 200){
        if ( lastgoc >= 7 ){
          int speedP = map(lastgoc,90,0,0,255);
          //Serial.print("Quay Sang Phai Voi Toc Do : "),Serial.println(speed);
          analogWrite(Tien_Trai,255);
          analogWrite(Lui_Trai,0);
          analogWrite(Tien_Phai,speedP);
          analogWrite(Lui_Phai,0);
          lasthuongP = 0 ;
          lasthuongT = 0 ;
        }
        else if (lastgoc <= -7) {
          int speedT = map(abs(lastgoc),90,0,0,255);
          //Serial.print("Quay Sang Trai Voi Toc Do : "),Serial.println(speed);
          analogWrite(Tien_Trai,speedT);
          analogWrite(Lui_Trai,0);
          analogWrite(Tien_Phai,255);
          analogWrite(Lui_Phai,0);
          lasthuongP = 0 ;
          lasthuongT = 0 ;
        }
        else{
          analogWrite(Tien_Trai,100);
          analogWrite(Lui_Trai,0);
          analogWrite(Tien_Phai,100);
          analogWrite(Lui_Phai,0);
          lasthuongP = 0 ;
          lasthuongT = 0 ;
        }
      }
      else {
        state = 0 ;
        Serial.print("Tra Ve Ham Tim Kiem");
        stopMotor();
        delay(5);
        return;
      }
    }
    delay(10);
  }
}
void loop() {
  int pressing = digitalRead(nutan);
  if (pressing == 0){
    Serial.print("STATE : ");Serial.println(state);
    switch (state)
    {
      case 0:
        find();
        break;
      
      case 1:
        attack();
        break;
      case 2:
        escape();
        break;
    }
  }
  else {
    Serial.println("Khong An Nut An");
    stopMotor();
  }
}
