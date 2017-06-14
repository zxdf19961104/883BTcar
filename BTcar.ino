#include <SoftwareSerial.h> 
const int MotorA1=7;
const int MotorA2=6;
const int MotorB1=5;
const int MotorB2=4;
const int trigPin=13;
const int echoPin=12;
const int Led=9;
char val='s';
SoftwareSerial BTSerial(10,11); //定義PIN10及PIN11分別為RX及TX腳位  藍芽用
long distance,duration;

void ping() 
{ // 超音波感測程式前方
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);  
  duration = pulseIn(echoPin, HIGH);
  distance = duration/58.2;
}

void setup() 
{ 
  Serial.begin(9600); //Arduino起始鮑率9600 
  BTSerial.begin(9600); //藍牙鮑率
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode (MotorA1, OUTPUT);
  pinMode (MotorA2, OUTPUT);
  pinMode (MotorB1, OUTPUT);
  pinMode (MotorB2, OUTPUT);  
  pinMode (Led,OUTPUT);
} 

void loop() 
{ 
    ping();
    if (BTSerial.available())
    {
      val=BTSerial.read();
      Serial.println(val);
      switch(val)
      {
      case 'a':  //Auto mode
          Auto();
          break;
      case 'f':  //forward 前後相反
          forward();
          break;
      case 'b':  //back
          back();
          break;
      case 'l':  //left
          left();
          break;
      case 'r':  //right
          right();
          break;
      case 's':  //Stop
          Stop();
          break;
      case 'o': //light on
           ledon();
           break;
      case 'u': //light off
           ledoff();
           break;         
      }
    }
    if (val=='a')
    {
      Auto();
    } 
  delay(50);
}
void Auto()
{    
    if(distance<25)
      {
          back();
          delay(1000);
          left();
          delay(500);
      }
    else
      {
        forward();
      }
  
}
void Stop()
{
  digitalWrite(MotorA1,LOW);
  digitalWrite(MotorA2,LOW);
  digitalWrite(MotorB1,LOW);
  digitalWrite(MotorB2,LOW);  
}
void back()
{
  digitalWrite(MotorA1,HIGH);
  digitalWrite(MotorA2,LOW);
  digitalWrite(MotorB1,HIGH);
  digitalWrite(MotorB2,LOW);
}
void forward()
{
  digitalWrite(MotorA1,LOW);
  digitalWrite(MotorA2,HIGH);
  digitalWrite(MotorB1,LOW);
  digitalWrite(MotorB2,HIGH);
}
void left()
{
  digitalWrite(MotorA1,HIGH);
  digitalWrite(MotorA2,LOW);
  digitalWrite(MotorB1,LOW);
  digitalWrite(MotorB2,HIGH);
}
void right()
{
  digitalWrite(MotorA1,LOW);
  digitalWrite(MotorA2,HIGH);
  digitalWrite(MotorB1,HIGH);
  digitalWrite(MotorB2,LOW);
}
void ledon()
{
  digitalWrite(Led,HIGH);
}
void ledoff()
{
  digitalWrite(Led,LOW);
}
