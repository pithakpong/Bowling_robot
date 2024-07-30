#include "Bowling.h"
Bowling bow;
int offset_position = 0;
int rounds = 0;
uint8_t FSM = 0;
void setup(){
  bow.setup(9600);
  bow.println("initialize successfully");
}
void loop(){
  switch(FSM){

    case 0: //calibration
      rounds++;
      if ((rounds < 3 ) || (rounds == 3 && bow.isStrike()))
        FSM = 1;
      bow.calibration(30);
      offset_position = 0;
      break;

    case 1: // slide to ball
      bow.RightWalk(2750,50,50);
      bow.FrontWalk(400,50,50);
      FSM = 2;
      break;

    case 2: // lay down arm
      bow.armdown();
      bow.release();
      bow.FrontWalk(500,50,50);
      FSM = 3;
      break;

    case 3: //keep ball
      bow.keep();
      bow.armup();
      FSM = 4;
      break;

    case 4: // go to foul line
      bow.ToFoulLine(50);
      FSM = 5;
      break;

    case 5: // go to position to shoot
      struct Position object = bow.position(bow.getImage(),500);
      offset_position = object.offset;
      bow.LeftWalk(offset_position,50,50);
      FSM = 6;
      break;
    
    case 6: //shoot
      bow.release();
      bow.keep();
      FSM = 7;
      break;

    case 7: // go to home
      bow.LeftWalk(3000-offset_position,50,50);
      bow.BackWalk(3500,50,50);
      FSM = 0;
      break;
    
    default:
      break;
  }
}
