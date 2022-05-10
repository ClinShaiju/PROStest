#include "main.h"

void runBackLift() {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) && !backPressed){
      backPressed = true; 
      if (isBackOut) {
        backIn();
      }
      else if (!isBackOut){
        backOut();
      }
      isBackOut = !isBackOut;

    }
    else if (!controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){ //If and only if the A button isn't pressed, we set latchPressed to false
      backPressed = false;
    }
}

void backOut() {
    BackMOGO.move_absolute(BACKOUT, 200);
    BackLatch.move_absolute(LATCHOUT, 200);
}
 
void backIn() {
    BackMOGO.move_absolute(BACKIN, 200);
    BackLatch.move_absolute(LATCHIN, 200);
}

