#include "main.h"

//Settings
double kP = 0.2;
double kI = 0.0;
double kD = 0.02;
double turnkP = .25;
double turnkI = 0.0;
double turnkD = .1;
int maxTurnIntegral = 300; // These cap the integrals
int maxIntegral = 300;
int integralBound = 1; //If error is outside the bounds, then apply the integral. This is a buffer with +-integralBound degrees

//Autonomous Settings
int desiredValue = 0;
int desiredHeading = 0;

int error; //SensorValue - DesiredValue : Position
int prevError = 0; //Position 20 miliseconds ago
int derivative; // error - prevError : Speed
int totalError = 0; //totalError = totalError + error

int turnError; //SensorValue - DesiredValue : Position
int turnPrevError = 0; //Position 20 miliseconds ago
int turnDerivative; // error - prevError : Speed
int turnTotalError = 0; //totalError = totalError + error

bool resetDriveSensors = false;

//Variables modified for use
bool enableDrivePID = true;


int leftPos() {
    return (FL.get_position() + BL.get_position())/2;
}

int rightPos() {
    return (FR.get_position() + BR.get_position())/2;
}

int drivePID(){
  stopTypeBrake();
  
  while(enableDrivePID){

    if (resetDriveSensors) {
      resetDriveSensors = false;
      resetDrive();
      inertial.tare();
    }


    //Get the position of both motors
    int leftMotorPosition = leftPos();
    int rightMotorPosition = rightPos();

    ///////////////////////////////////////////
    //Lateral movement PID
    /////////////////////////////////////////////////////////////////////
    //Get average of the two motors
    int averagePosition = (leftMotorPosition + rightMotorPosition)/2;

    //Potential
    error = desiredValue - averagePosition;

    //Derivative
    derivative = error - prevError;

    //Integral
    if(abs(error) < integralBound){
    totalError+=error; 
    }  else {
    totalError = 0; 
    }
    //totalError += error;

    //This would cap the integral
    totalError = abs(totalError) > maxIntegral ? signnum_c(totalError) * maxIntegral : totalError;

    double lateralMotorPower = error * kP + derivative * kD + totalError * kI;
    lateralMotorPower = 0;
    /////////////////////////////////////////////////////////////////////


    ///////////////////////////////////////////
    //Turning movement PID
    /////////////////////////////////////////////////////////////////////
    //Get average of the two motors
    int currentHeading = inertial.get_heading();

    if (currentHeading > 180) {
      currentHeading -= 360;
    }

    //Potential
    turnError =  currentHeading - desiredHeading;

    //Derivative
    turnDerivative = turnError - turnPrevError;

    //Integral
    /*
    if(abs(error) < integralBound){
    turnTotalError+=turnError; 
    }  else {
    turnTotalError = 0; 
    }*/
    turnTotalError += turnError;

    //This would cap the integral
    turnTotalError = abs(turnTotalError) > maxIntegral ? signnum_c(turnTotalError) * maxIntegral : turnTotalError;

    double turnMotorPower = turnError * turnkP + turnDerivative * turnkD + turnTotalError * turnkI;
    /////////////////////////////////////////////////////////////////////

    FL.move_velocity(lateralMotorPower + turnMotorPower);
    BL.move_velocity(lateralMotorPower + turnMotorPower);
    FR.move_velocity(lateralMotorPower - turnMotorPower);
    BR.move_velocity(lateralMotorPower - turnMotorPower);
    prevError = error;
    turnPrevError = turnError;

    pros::delay(20);

  }

  return 1;
}