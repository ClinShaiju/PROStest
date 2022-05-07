#include "main.h"

//global variables
bool isBackOut = false;
bool backPressed = false;
bool isLatchOut = false;
bool latchPressed = false;

//controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

//drivetrain
pros::Motor BL(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor FL(2, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor BR(3, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor FR(4, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);

//Back lift
pros::Motor BackMOGO(5, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);

//Main front lift
pros::Motor MOGOLiftL(6, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor MOGOLiftR(7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);

//Back latch
pros::Motor BackLatch(8, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);

//pneumatics
pros::ADIDigitalOut pistonLeft('B', false);
pros::ADIDigitalOut pistonRight('A', false);

//set brake mode
void stopTypeBrake() {
    BackLatch.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    BackMOGO.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

    BL.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    FL.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    BR.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    FR.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

    MOGOLiftL.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    MOGOLiftR.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

}
//exponential drive
double returnExponential(int axisValue) {
  double percentage = axisValue;
  if (percentage > 0) {
    percentage = 1.2*pow(1.043, percentage) - 1.2 + 0.2 * percentage;
  }
  else {
    percentage = -percentage;

    percentage = 1.2*pow(1.043, percentage) - 1.2 + 0.2 * percentage;

    percentage = -percentage;
  }
  return percentage;
}