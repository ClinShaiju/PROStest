#include "main.h"

void moveMOGOLift(int velocity) {
    MOGOLiftR.move_velocity(velocity);
    MOGOLiftL.move_velocity(velocity);
}

void runMOGOLift() {
    moveMOGOLift(200 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)));
}