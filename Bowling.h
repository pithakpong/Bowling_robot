#ifndef Bowling_H
#define Bowling_H
#include "Arduino.h"
#include <PRIZM.h>
struct Position{
  int offset;
  char pos;
};
class Bowling 
{
  private :
    PRIZM _prizm;
    EXPANSION _exc;

  public :
    Bowling();
    void setup(long baudrate);
    void print(String msg);
    void print(int msg);
    void print(long msg);
    void println(String msg);
    void println(int msg);
    void println(long msg);
    void release();
    void keep();
    void armup();
    void armdown();
    int read_ir_rightback();
    int read_ir_leftback();
    int read_ir_rightfront();
    int read_ir_leftfront();
    void setMotoreSpeed(int channel,int speed);
    void calibration(int speed);
    void MoveForward(int counted,int speed1,int speed2);
    void SlideWalk(int counted,int speed1, int speed2);
    void RightWalk(int counted,int speed1, int speed2);
    void LeftWalk(int counted,int speed1, int speed2);
    void FrontWalk(int counted,int speed1, int speed2);
    void BackWalk(int counted,int speed1, int speed2);
    void ToFoulLine(int speed);
    struct Position position(int number,int multiplicand);
    int getImage();
    bool isStrike();
};

#endif