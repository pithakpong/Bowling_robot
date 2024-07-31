#include "Bowling.h"
Bowling bow;
int offset_position = 0;
int rounds = 0;
uint8_t FSM = 0;
void setup(){
  bow.setup(9600);
  bow.println("initialize successfully");
}
void loop() {
  switch(FSM) {
    case 0: //calibration
      bow.println("In Case 0"); // Debug: Confirm entering case 0
      rounds++;
      if ((rounds < 3 ) || (rounds == 3 && bow.isStrike()))
        FSM = 1;
      bow.calibration(30);
      offset_position = 0;
    break;

    case 1: // slide to ball
      bow.println("In Case 1"); // Debug: Confirm entering case 1
      bow.RightWalk(2750,50,50);
      bow.FrontWalk(400,50,50);
      FSM = 2;
    break;

    case 2: // lay down arm
      bow.println("In Case 2"); // Debug: Confirm entering case 2
      bow.armdown();
      bow.release();
      bow.FrontWalk(500,50,50);
      FSM = 3;
    break;

    case 3: //keep ball
      bow.println("In Case 3"); // Debug: Confirm entering case 3
      bow.keep();
      bow.armup();
      FSM = 4;
    break;

    case 4: // go to foul line
      bow.println("In Case 4"); // Debug: Confirm entering case 4
      bow.ToFoulLine(50);
      bow.RightWalk(400,50,50);
      FSM = 5;
    break;

    case 5: // go to position to shoot && shoot && go home
      // go to position
      bow.println("In Case 5"); // Debug: Confirm entering case 5
      struct Position object = bow.position(bow.getImage(),300);
      offset_position = object.offset;
      bow.println(offset_position);
      // shoot
      bow.release();
      bow.keep();
      // go home
      bow.LeftWalk(3000-offset_position,50,50);
      bow.BackWalk(3400,50,50);
      FSM = 0;
    break;
  }
}
