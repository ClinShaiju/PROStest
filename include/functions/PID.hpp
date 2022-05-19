#include "main.h"

//global values for PID
extern int desiredValue;
extern int desiredHeading;
extern bool enableDrivePID;
extern bool resetDriveSensors;

//Settings
extern double kP;
extern double kI;
extern double kD;
extern double turnkP;
extern double turnkI;
extern double turnkD;

extern int error;
extern double averagePosition;

//get motor values
int rightPos();
int leftPos();

void drivePID(void*);