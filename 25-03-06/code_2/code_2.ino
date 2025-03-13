/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-joystick
 */
#include <ezButton.h>
#include <AccelStepper.h>
#include <Stepper.h>

#define MotorInterfaceType 4

#define VRX_PIN  A1 // Arduino pin connected to VRX pin
#define VRY_PIN  A0 // Arduino pin connected to VRY pin

#define LEFT_THRESHOLD  400
#define RIGHT_THRESHOLD 800
#define UP_THRESHOLD    550
#define DOWN_THRESHOLD  450

#define COMMAND_NO     0x00
#define COMMAND_LEFT   0x01
#define COMMAND_RIGHT  0x02
#define COMMAND_UP     0x04
#define COMMAND_DOWN   0x08

#define MOTOR_SPEED 600

const int stepsPerRevolution = 2038;
// Creates an instance
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
AccelStepper myStepper1(MotorInterfaceType, 8, 10, 9, 11);
AccelStepper myStepper2(MotorInterfaceType, 4, 6, 5, 7);
//Stepper myStepper1(stepsPerRevolution, 8, 10, 9, 11);
//Stepper myStepper2(stepsPerRevolution, 4, 6, 5, 7);

int xValue = 0 ; // To store value of the X axis
int yValue = 0 ; // To store value of the Y axis
int command = COMMAND_NO;

const int trigPin = 3;
const int echoPin = 2;

float duration, distance;

void setup() {
  Serial.begin(9600) ;
  
  // set the maximum speed, acceleration factor,
  // initial speed and the target position
  myStepper1.setMaxSpeed(1000.0);
  myStepper1.setAcceleration(100.0);
//  myStepper1.setSpeed(600);//
//  myStepper1.moveTo(2048);  //1 revolution/
  
  myStepper2.setMaxSpeed(1000.0);
  myStepper2.setAcceleration(100.0);
//  myStepper2.setSpeed(600);
//  myStepper2.moveTo(2048);  //1 revolution/
//    myStepper1.runSpeed();
//    myStepper2.runSpeed();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
//  Serial.print("Distance: ");
//  Serial.println(distance);
//  delay(100);
  
  // read analog X and Y analog values
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);

  // converts the analog value to commands
  // reset commands
  command = COMMAND_NO;

  // check left/right commands
  if (xValue < LEFT_THRESHOLD)
    command = command | COMMAND_LEFT;
  else if (xValue > RIGHT_THRESHOLD)
    command = command | COMMAND_RIGHT;

  // check up/down commands
  if (yValue > UP_THRESHOLD)
    command = command | COMMAND_UP;
  else if (yValue < DOWN_THRESHOLD)
    command = command | COMMAND_DOWN;

  // NOTE: AT A TIME, THERE MAY BE NO COMMAND, ONE COMMAND OR TWO COMMANDS
  myStepper1.runSpeed();
  myStepper2.runSpeed();
  // print command to serial and process command
  if (command & COMMAND_LEFT) {
//    Serial.println("COMMAND LEFT");
//    myStepper1.runSpeed();
//    myStepper2.runSpeed();
    myStepper1.setSpeed(MOTOR_SPEED);
    myStepper2.setSpeed(MOTOR_SPEED);
    
  }

  if (command & COMMAND_RIGHT) {
//    Serial.println("COMMAND RIGHT");
    // TODO: add your task here
//    myStepper1.runSpeed();
//    myStepper2.runSpeed();
    myStepper1.setSpeed(-MOTOR_SPEED);
    myStepper2.setSpeed(-MOTOR_SPEED);
  }

  if (command & COMMAND_UP) {
//    Serial.println("COMMAND UP");
    // TODO: add your task here
//    myStepper1.runSpeed();
//    myStepper2.runSpeed();
    myStepper1.setSpeed(-(MOTOR_SPEED*((yValue-UP_THRESHOLD)/(1023.0-UP_THRESHOLD))));
    myStepper2.setSpeed((MOTOR_SPEED*((yValue-UP_THRESHOLD)/(1023.0-UP_THRESHOLD))));
//Serial.println((MOTOR_SPEED*((yValue-UP_THRESHOLD)/(1023.0-UP_THRESHOLD))));
//    myStepper1.setSpeed(MOTOR_SPEED);
//    myStepper2.setSpeed(-MOTOR_SPEED);
  }

  if (command & COMMAND_DOWN) {
//    Serial.println("COMMAND DOWN");
    // TODO: add your task here
//    myStepper1.runSpeed();
//    myStepper2.runSpeed();
    myStepper1.setSpeed(-(MOTOR_SPEED*((DOWN_THRESHOLD-yValue)/(DOWN_THRESHOLD*1.0))));
    myStepper2.setSpeed((MOTOR_SPEED*((DOWN_THRESHOLD-yValue)/(DOWN_THRESHOLD*1.0))));
  }

  if (command==0 | distance < 5){
//    Serial.println("COMMAND STOP");
    myStepper1.setSpeed(0);
    myStepper2.setSpeed(0);
  }
}
