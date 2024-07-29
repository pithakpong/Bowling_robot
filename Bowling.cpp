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
}
void Bowling::release(){
  _prizm.setServoPosition(2,90);
}
void Bowling::armup(){
  _prizm.setServoPosition(1,0);
}
void Bowling::armdown(){
  _prizm.setServoPosition(1,170);
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