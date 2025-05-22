/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-joystick
 */

// ESP32 Pin Definitions (adjust these to your specific ESP32 board and wiring)
#define VRX_PIN  35 // Example ADC1 pin for ESP32 (e.g., GPIO35)
#define VRY_PIN  34 // Example ADC1 pin for ESP32 (e.g., GPIO34)

#define LEFT_THRESHOLD  400
#define RIGHT_THRESHOLD 800
#define UP_THRESHOLD    550
#define DOWN_THRESHOLD  450

#define COMMAND_NO     0x00
#define COMMAND_LEFT   0x01
#define COMMAND_RIGHT  0x02
#define COMMAND_UP     0x04
#define COMMAND_DOWN   0x08

// ESP32 GPIO pins for H-Bridge (adjust these to your specific ESP32 board and wiring)
#define enA 25 // Example GPIO for ESP32, uno --> 8, hitam
#define enB 26 // Example GPIO for ESP32, uno --> 9, kunig
#define IN1 27 // Example GPIO for ESP32, uno --> 10, abu
#define IN2 14 // Example GPIO for ESP32, uno --> 11, oren
#define IN3 12 // Example GPIO for ESP32, uno --> 12, putih
#define IN4 13 // Example GPIO for ESP32, uno --> 13, ungu



// For LED_BUILTIN, ESP32 boards vary. Common is GPIO 2.
// If you use LED_BUILTIN, you might need to define it explicitly, e.g.:
// #ifndef LED_BUILTIN
// #define LED_BUILTIN 2
// #endif

int xValue = 0 ; // To store value of the X axis
int yValue = 0 ; // To store value of the Y axis
int command = COMMAND_NO;

float duration, distance; // These variables are declared but not used in the provided code.

void setup() {
  Serial.begin(9600);

  // Set ESP32 analog read resolution to 10-bit (0-1023) to match Arduino Uno behavior
  // if your thresholds are based on that range.
  // Alternatively, adjust thresholds for ESP32's default 12-bit resolution (0-4095).
  analogReadResolution(10); 

  // pinMode(LED_BUILTIN, OUTPUT); // Note: LED_BUILTIN is set up but not used in the loop.
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

  // myStepper1.runSpeed(); // These lines are commented out in your original code
  // myStepper2.runSpeed(); // and refer to myStepper objects not defined here.
  if (command & COMMAND_LEFT) {    
    Serial.println("LEFT");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }

  if (command & COMMAND_RIGHT) {
    Serial.println("RIGHT");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }

  if (command & COMMAND_UP) {
    Serial.println("UP");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }

  if (command & COMMAND_DOWN) {
    Serial.println("DOWN");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  
  if (command==0){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
}