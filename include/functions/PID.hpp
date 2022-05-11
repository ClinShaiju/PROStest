#include "main.h"

//global values for PID
extern int desiredValue;
extern int desiredHeading;
extern bool enableDrivePID;

//Settings
extern double kP;
extern double kI;
extern double kD;
extern double turnkP;
extern double turnkI;
extern double turnkD;

//get motor values
int rightPos();
int leftPos();

void drivePID(void*);