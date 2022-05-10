#include "main.h"
#include "pros/imu.hpp"
#include "pros/motors.h"

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

//sensors
pros::Imu inertial(9);
pros::Gps gps(10);
