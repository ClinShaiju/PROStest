#include "main.h"
#include "pros/imu.hpp"

//definitions
#define VELOCITY 1.57480315
#define BACKOUT 550
#define BACKIN 175
#define LATCHIN 85
#define LATCHOUT 0

//global variables
extern bool isBackOut;
extern bool backPressed;
extern bool isLatchOut;
extern bool latchPressed;

//controller
extern pros::Controller controller;

//drivetrain
extern pros::Motor BL;
extern pros::Motor BR;
extern pros::Motor FL;
extern pros::Motor FR;

//Back lift
extern pros::Motor BackMOGO;

//Main front lift
extern pros::Motor MOGOLiftL;
extern pros::Motor MOGOLiftR;

//Back latch
extern pros::Motor BackLatch;

//pneumatics
extern pros::ADIDigitalOut pistonLeft;
extern pros::ADIDigitalOut pistonRight;

//sensors
extern pros::Imu inertial;
extern pros::Gps gps;