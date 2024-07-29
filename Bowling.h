#ifndef Bowling_H
#define Bowling_H
#include "Arduino.h"
#include <PRIZM.h>

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
    void MoveForward(int counted,int speed1,int speed2);
    void SlideWalk(int counted,int speed1, int speed2);
    void RightWalk(int counted,int speed1, int speed2);
    void LeftWalk(int counted,int speed1, int speed2);
    void FrontWalk(int counted,int speed1, int speed2);
    void BackWalk(int counted,int speed1, int speed2);
};

#endif