#include "main.h"

void setDriveSpeed(int left, int right) {
    BL.move_velocity(left * VELOCITY);
    FL.move_velocity(left * VELOCITY);
    FR.move_velocity(right * VELOCITY);
    BR.move_velocity(right * VELOCITY);
}

void driveArcade() {
    //get controller inputs
    int leftForward = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightTurn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    
    //remove controller error
    if (abs(leftForward) < 10)
        leftForward = 0;

    if (abs(rightTurn) < 10) 
        rightTurn = 0;

    rightTurn = returnExponential(rightTurn);
    leftForward = returnExponential(leftForward);

    //run the motors
    setDriveSpeed(leftForward + rightTurn, leftForward - rightTurn);
}

void driveTank() {
     //get controller inputs
    int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

    //remove controller error
    if (abs(leftY) < 10)
        leftY = 0;

    if (abs(rightY) < 10) 
        rightY = 0;

    //run the motors
    setDriveSpeed(returnExponential(leftY), returnExponential(rightY));
}

void resetDrive() {
    BL.tare_position();
    BR.tare_position();
    FR.tare_position();
    FL.tare_position();
}