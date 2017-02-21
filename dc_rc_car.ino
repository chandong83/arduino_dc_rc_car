#include <SoftwareSerial.h>


//모터 PIN 설정
#define IN1 9
#define IN2 8

#define IN3 7
#define IN4 6

#define ENA 10
#define ENB 5

//모터 번호
#define CH1 0
#define CH2 1
#define ALL_CH 2

#define BT_TXD 2
#define BT_RXD 3

SoftwareSerial BTSerial(BT_TXD, BT_RXD);

void setup() {
  //핀 설정
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
  BTSerial.begin(9600);


  setMotorSpeed(ALL_CH, 150);
}

//
// 속도 설정
// mode : 각 모터를 선택적으로 변경 가능
// CH1, CH2, ALL_CH
// speed : 0 ~ 255 까지 가능
// 60 이하로는 모터가 거의 동작안함.
void setMotorSpeed(unsigned char mode, unsigned char speed){
  if(mode == CH1){
    analogWrite(ENA, speed);
  }else if(mode == CH2){
    analogWrite(ENB, speed);
  }else{
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
  }
}

//앞으로
void forward(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

//뒤로
void backward(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

//왼쪽
void turnLeft(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

//오른쪽
void turnRight(){

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

//스톱
void stopMotor(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}

void loop() {
  if(BTSerial.available()){
    char rx = BTSerial.read();
    switch(rx){
      case 'w': //forward
      forward();
        break;
      case 'a': //left
      turnLeft();
        break;
      case 'd': //right
      turnRight();
        break;
      case 's': //backward
       backward();
        break;
      case '1': //Stop
      stopMotor();
        break;
    }
   }
}
