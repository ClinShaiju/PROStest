#include "main.h"

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

double signnum_c(double x) {
  if (x > 0.0) return 1.0;
  if (x < 0.0) return -1.0;
  return x;
}
