/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-joystick
 */

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

#define enA 8
#define enB 9
#define IN1 10
#define IN2 11
#define IN3 12
#define IN4 13

int xValue = 0 ; // To store value of the X axis
int yValue = 0 ; // To store value of the Y axis
int command = COMMAND_NO;

float duration, distance;

void setup() {
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

void loop() {

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

  int speedX = 0;
  int speedY = 0;
  int motorSpeed = 0;
  
  // Calculate potential speed based on X-axis deflection
  if (command & COMMAND_LEFT) {
    speedX = map(xValue, LEFT_THRESHOLD, 0, MIN_PWM_SPEED, MAX_PWM_SPEED);
  } else if (command & COMMAND_RIGHT) {
    speedX = map(xValue, RIGHT_THRESHOLD, 1023, MIN_PWM_SPEED, MAX_PWM_SPEED);
  }
  speedX = constrain(speedX, MIN_PWM_SPEED, MAX_PWM_SPEED);

  // Calculate potential speed based on Y-axis deflection
  if (command & COMMAND_UP) {
    speedY = map(yValue, UP_THRESHOLD, 1023, MIN_PWM_SPEED, MAX_PWM_SPEED);
  } else if (command & COMMAND_DOWN) {
    speedY = map(yValue, DOWN_THRESHOLD, 0, MIN_PWM_SPEED, MAX_PWM_SPEED);
  }
  speedY = constrain(speedY, MIN_PWM_SPEED, MAX_PWM_SPEED);

  bool y_axis_command_active = false;
  bool x_axis_command_active = false;

  // Set motor directions based on command
  // The original structure of sequential ifs is maintained.
  // The last command group (X or Y) to set IN pins will determine the direction.

  if (command & COMMAND_LEFT) {    
    Serial.println("LEFT");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    x_axis_command_active = true;
  }

  if (command & COMMAND_RIGHT) {
    Serial.println("RIGHT");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    x_axis_command_active = true;
  }

  if (command & COMMAND_UP) {
    Serial.println("UP");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    y_axis_command_active = true; 
  }

  if (command & COMMAND_DOWN) {
    Serial.println("DOWN");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    y_axis_command_active = true;
  }
  
  if (command == COMMAND_NO){ // No command, stop motors
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    // x_axis_command_active and y_axis_command_active remain false
  }

  // Determine final motor speed based on which axis command took precedence
  if (y_axis_command_active) { // If UP or DOWN command was active
    motorSpeed = speedY;
  } else if (x_axis_command_active) { // Else, if LEFT or RIGHT command was active
    motorSpeed = speedX;
  } else { // No command active
    motorSpeed = 0;
  }

  // Apply the calculated speed to both motors via PWM
  analogWrite(enA, motorSpeed);
  analogWrite(enB, motorSpeed);