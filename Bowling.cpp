#include "Arduino.h"
#include <PRIZM.h>
#include "Bowling.h"

Bowling::Bowling(){
}
void Bowling::print(String msg){
  Serial.print(msg);
}
void Bowling::print(int msg){
  Serial.print(msg);
}
void Bowling::print(long msg){
  Serial.print(msg);
}
void Bowling::println(String msg){
  Serial.println(msg);
}
void Bowling::println(int msg){
  Serial.println(msg);
}
void Bowling::println(long msg){
  Serial.println(msg);
}
void Bowling::keep(){
  _prizm.setServoPosition(2,0);
  while(_prizm.readServoPosition(2) >= 5 ){}
}
void Bowling::release(){
  _prizm.setServoPosition(2,90);
  while(_prizm.readServoPosition(2) <= 85 || _prizm.readServoPosition(2) >= 95){}
}
void Bowling::armup(){
  _prizm.setServoPosition(1,0);
  while(_prizm.readServoPosition(1) >= 5 ){}
}
void Bowling::armdown(){
  _prizm.setServoPosition(1,170);
  while(_prizm.readServoPosition(1) <= 165 || _prizm.readServoPosition(1) >= 175){}
}
void Bowling::setup(long baudrate){
  Serial.begin(baudrate);
  _prizm.PrizmBegin();
  _prizm.setMotorSpeedPID(180,4,0);
  _exc.setMotorSpeedPID(2,180,4,0);
  _prizm.setServoSpeed(1,10);
  _prizm.setServoSpeed(2,10);
  this->armup();
  this->keep();
  delay(5000);
  _prizm.setServoSpeed(1,30);
  _prizm.setServoSpeed(2,30);
}
int Bowling::read_ir_rightback(){
  return _prizm.readLineSensor(4); //4
}
int Bowling::read_ir_leftback(){
  return _prizm.readLineSensor(2); //2
}
int Bowling::read_ir_rightfront(){
  return _prizm.readLineSensor(5); //5
}
int Bowling::read_ir_leftfront(){
  return _prizm.readLineSensor(3); //3
}
void Bowling::setMotoreSpeed(int channel,int speed){
  if(channel <= 2)
    _prizm.setMotorSpeed(channel,speed);
  else
    _exc.setMotorSpeed(2,channel-2,speed);
}
void Bowling::calibration(int speed){
  bool flag = true;
  bool flag2 = false;
  while (flag){
    if(!this->read_ir_leftfront())this->setMotoreSpeed(1,-abs(speed));else this->setMotoreSpeed(1,0);
    if(!this->read_ir_rightfront())this->setMotoreSpeed(2,abs(speed));else this->setMotoreSpeed(2,0);
    if (this->read_ir_leftfront() && this->read_ir_rightfront()) {flag = false;flag2 = true;this->setMotoreSpeed(1,0);this->setMotoreSpeed(2,0);}
    this->print(this->read_ir_leftfront());
    this->print(" ");
    this->println(this->read_ir_rightfront());
  }
  while (flag2){
    if(!this->read_ir_rightback()){this->setMotoreSpeed(3,-abs(speed));this->setMotoreSpeed(4,abs(speed));}
    if (this->read_ir_rightback() && this->read_ir_rightfront()) {flag = false;flag2 = false;this->setMotoreSpeed(3,0);this->setMotoreSpeed(4,0);}
    this->print(this->read_ir_rightback());
    this->print(" ");
    this->println(this->read_ir_rightfront());
  }
}
void Bowling::MoveForward(int counted,int speed1,int speed2){  
  _prizm.resetEncoders();
  _prizm.setMotorSpeeds(speed1,speed2);
  while(abs(_prizm.readEncoderCount(1)) < counted && abs(_prizm.readEncoderCount(2)) < counted){
    this->print(_prizm.readEncoderCount(1));
    this->print(" ");
    this->println(_prizm.readEncoderCount(2));
  }
  _prizm.setMotorSpeeds(0,0);
}
void Bowling::SlideWalk(int counted,int speed1, int speed2){
  _exc.resetEncoders(2);
  _exc.setMotorSpeeds(2,speed1,speed2);
  while(abs(_exc.readEncoderCount(2,1)) < counted && abs(_exc.readEncoderCount(2,2)) < counted){
    this->print(_exc.readEncoderCount(2,1));
    this->print(" ");
    this->println(_exc.readEncoderCount(2,2));
  }
  _exc.setMotorSpeeds(2,0,0);

}
void Bowling::RightWalk(int counted,int speed1, int speed2){
  this->SlideWalk(counted,-speed1,speed2);
}
void Bowling::LeftWalk(int counted,int speed1, int speed2){
  this->SlideWalk(counted,speed1,-speed2);
}
void Bowling::FrontWalk(int counted,int speed1, int speed2){
  this->MoveForward(counted,-speed1,speed2);
}
void Bowling::BackWalk(int counted,int speed1, int speed2){
  this->MoveForward(counted,speed1,-speed2);
}
void Bowling::ToFoulLine(int speed){
  bool flag = true;
  while (flag){
  if(!this->read_ir_leftfront())this->setMotoreSpeed(1,-abs(speed));
  if(!this->read_ir_rightfront())this->setMotoreSpeed(2,abs(speed));
  if (this->read_ir_leftfront() && this->read_ir_rightfront()) {flag = false;this->setMotoreSpeed(1,0);this->setMotoreSpeed(2,0);}
  }
}
struct Position Bowling::position(int number,int multiplicand){
  struct Position img;
  switch(number){
    case 1:
      img.pos = 'A';
      img.offset = multiplicand*6;
      break;
    case 2:
      img.pos = 'B';
      img.offset = multiplicand*5;
      break;
    case 3:
      img.pos = 'C';
      img.offset = multiplicand*4;
      break;
    case 4:
      img.pos = 'D';
      img.offset = multiplicand*3;
      break;
    case 5:
      img.pos = 'E';
      img.offset = multiplicand*2;
      break;
    case 6:
      img.pos = 'F';
      img.offset = multiplicand*1;
      break;
    case 7:
      img.pos = 'G';
      img.offset = multiplicand*0;
      break;
  }
  return img;
}
int Bowling::getImage(){
  return 7;
}
bool Bowling::isStrike(){
  return false;
}