/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-joystick
 */
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

enum state {
 LED_OFF,
 LED_ON
};
// The blink state variable.
uint8_t led_state = LED_OFF;

const int stepsPerRevolution = 2038;
// Creates an instance
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
AccelStepper myStepper1(MotorInterfaceType, 8, 10, 9, 11);
AccelStepper myStepper2(MotorInterfaceType, 4, 6, 5, 7);

int xValue = 0 ; // To store value of the X axis
int yValue = 0 ; // To store value of the Y axis
int command = COMMAND_NO;

float duration, distance;

unsigned long last_blink_time;
unsigned int blink_interval;

void setup() {
  Serial.begin(9600) ;
  
  // set the maximum speed, acceleration factor,
  // initial speed and the target position
  myStepper1.setMaxSpeed(1000.0);
  myStepper1.setAcceleration(100.0);
  
  myStepper2.setMaxSpeed(1000.0);
  myStepper2.setAcceleration(100.0);

  pinMode(LED_BUILTIN, OUTPUT);
  last_blink_time = millis();
}

void blink_task() {
  switch (led_state) {
    case LED_OFF:
      // LED is off, we need to turn it on.
      digitalWrite(LED_BUILTIN, HIGH);
      // Update the state variable.
      led_state = LED_ON;
      // Update the blink interval (just for fun).
      blink_interval = 50;
      break;
    case LED_ON:
      digitalWrite(LED_BUILTIN, LOW);
      led_state = LED_OFF;
      blink_interval = 450;
      break;
  }
}

void loop() {

  // blink_interval = analogRead(A2);

  if (millis() - last_blink_time >= blink_interval) {
    // Update the last blink time.
    last_blink_time += blink_interval;
    // Execute the blink task.
    blink_task();
    // digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }

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

  myStepper1.runSpeed();
  myStepper2.runSpeed();
  if (command & COMMAND_LEFT) {
    myStepper1.setSpeed(MOTOR_SPEED);
    myStepper2.setSpeed(MOTOR_SPEED);
    
  }

  if (command & COMMAND_RIGHT) {
    myStepper1.setSpeed(-MOTOR_SPEED);
    myStepper2.setSpeed(-MOTOR_SPEED);
  }

  if (command & COMMAND_UP) {
    myStepper1.setSpeed(-(MOTOR_SPEED*((yValue-UP_THRESHOLD)/(1023.0-UP_THRESHOLD))));
    myStepper2.setSpeed((MOTOR_SPEED*((yValue-UP_THRESHOLD)/(1023.0-UP_THRESHOLD))));
  }

  if (command & COMMAND_DOWN) {
    myStepper1.setSpeed(-(MOTOR_SPEED*((DOWN_THRESHOLD-yValue)/(DOWN_THRESHOLD*1.0))));
    myStepper2.setSpeed((MOTOR_SPEED*((DOWN_THRESHOLD-yValue)/(DOWN_THRESHOLD*1.0))));
  }
  Serial.println(command);
  if (command==0){
    myStepper1.setSpeed(0);
    myStepper2.setSpeed(0);
  }
}
