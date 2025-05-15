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

  digitalWrite(enA, HIGH);
  digitalWrite(enB, HIGH);
}

void loop() {
  //mundur (bismillah semoga bekerja 🙏🤲🤲)
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  delay(1000);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  delay(1000);
  // digitalWrite(IN3, HIGH);
  // digitalWrite(IN4, LOW);
  // delay(1000);
  // digitalWrite(IN3, HIGH);
  // digitalWrite(IN4, LOW);
  // delay(1000);
  

  // // read analog X and Y analog values
  // xValue = analogRead(VRX_PIN);
  // yValue = analogRead(VRY_PIN);

  // converts the analog value to commands
  // reset commands
  // command = COMMAND_NO;

  // // check left/right commands
  // if (xValue < LEFT_THRESHOLD)
  //   command = command | COMMAND_LEFT;
  // else if (xValue > RIGHT_THRESHOLD)
  //   command = command | COMMAND_RIGHT;

  // // check up/down commands
  // if (yValue > UP_THRESHOLD)
  //   command = command | COMMAND_UP;
  // else if (yValue < DOWN_THRESHOLD)
  //   command = command | COMMAND_DOWN;

  // // myStepper1.runSpeed();
  // // myStepper2.runSpeed();
  // if (command & COMMAND_LEFT) {    
  //   digitalWrite(IN1, HIGH);
  //   digitalWrite(IN2, LOW);
  // }

  // if (command & COMMAND_RIGHT) {
  //   digitalWrite(IN1, LOW);
  //   digitalWrite(IN2, HIGH);
  // }

  // if (command & COMMAND_UP) {
  //   digitalWrite(IN1, HIGH);
  //   digitalWrite(IN2, LOW);
  // }

  // if (command & COMMAND_DOWN) {
  //   digitalWrite(IN1, LOW);
  //   digitalWrite(IN2, HIGH);
  // }
  // Serial.println(command);
  // if (command==0){
  //   digitalWrite(IN1, LOW);
  //   digitalWrite(IN2, LOW);
  //   digitalWrite(IN3, LOW);
  //   digitalWrite(IN4, LOW);
  // }
}
