#define BTNIN1 2
#define BTNIN2 4

#include <Servo.h>

Servo myservo;

float press_count = 180;
bool prev_state = LOW;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BTNIN1,INPUT);
  pinMode(BTNIN2,INPUT);
  myservo.attach(11);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool buttonState1 = digitalRead(BTNIN1);
  bool buttonState2 = digitalRead(BTNIN2);
  bool buttonStateUniversal = max(buttonState1, buttonState2);
//  prev_state = 0;
//  buttonStateUniversal = 1;
  while (prev_state != buttonStateUniversal){
    if (buttonState1 == HIGH){
      press_count += 10;
      prev_state = HIGH;
      Serial.println(press_count);
    }
    if (buttonState2 == HIGH){
      press_count -= 10;
      prev_state = HIGH;
      Serial.println(press_count);
    }
    delay(20);
    prev_state = buttonStateUniversal;
  }
  if (press_count >= 180.0) {press_count = 180;}
  if (press_count <= -180.0) {press_count = -180;}
  myservo.write(abs(press_count)*(180/160));
}
