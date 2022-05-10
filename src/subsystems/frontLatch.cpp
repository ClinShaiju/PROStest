#include "main.h"

void latchOut() {
    pistonRight.set_value(true);
    pistonLeft.set_value(true);
}
void latchIn() {
    pistonRight.set_value(false);
    pistonLeft.set_value(false);
}

void runFrontLatch() {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B) && !latchPressed){
      latchPressed = true; 
      if (isLatchOut) {
        latchIn();
      }
      else if (!isLatchOut){
        latchOut();
      }
      isLatchOut = !isLatchOut;

    }
    else if (!pros::E_CONTROLLER_DIGITAL_B){ //If and only if the A button isn't pressed, we set_value latchPressed to false
      latchPressed = false;
    }
}