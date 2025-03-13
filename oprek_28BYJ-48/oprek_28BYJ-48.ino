// Include the AccelStepper Library
#include <AccelStepper.h>

// Define step constant
#define MotorInterfaceType 4

// Creates an instance
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
AccelStepper myStepper1(MotorInterfaceType, 8, 10, 9, 11);
AccelStepper myStepper2(MotorInterfaceType, 4, 6, 5, 7);

void setup() {
  // set the maximum speed, acceleration factor,
  // initial speed and the target position
  myStepper1.setMaxSpeed(600.0);
  myStepper1.setAcceleration(100.0);
  myStepper1.setSpeed(200);
  myStepper1.moveTo(2048);  //1 revolution
  
  myStepper2.setMaxSpeed(600.0);
  myStepper2.setAcceleration(100.0);
  myStepper2.setSpeed(200);
  myStepper2.moveTo(2048);  //1 revolution
}

void loop() {
  // Change direction once the motor reaches target position
  if (myStepper1.distanceToGo() == 0) 
    myStepper1.moveTo(-myStepper1.currentPosition());
    
  if (myStepper2.distanceToGo() == 0) 
    myStepper2.moveTo(-myStepper2.currentPosition());

  // Move the motor one step
  myStepper1.run();
  myStepper2.run();
}
