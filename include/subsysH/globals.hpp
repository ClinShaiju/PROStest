#include "main.h"

//definitions
#define VELOCITY 1.57480315
#define BACKOUT 550
#define BACKIN 175
#define LATCHIN 85
#define LATCHOUT 0

//global variables
extern bool isBackOut;
extern bool backPressed;

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

//set brake mode
void stopTypeBrake();

//exponential drive
double returnExponential(int axisValue);