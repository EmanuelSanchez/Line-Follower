/**
* @Author: emanuel
* @Date:   2016-10-16T12:19:54-04:00
@Last modified by:   emanuel
@Last modified time: 2016-10-16T03:22:39-04:00
*/

#include<Arduino.h>
#include"motors/motors.cpp"

void setup() {

  Serial.begin(230400);

  //motors: pinout configuration
  pinMode(motorL_en, OUTPUT);
  pinMode(motorL_phase, OUTPUT);
  pinMode(motorR_en, OUTPUT);
  pinMode(motorR_phase, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);

  //motors: direction
  digitalWrite(motorL_phase, HIGH);
  digitalWrite(motorR_phase, HIGH);

  //wait 2 seconds
  delay(2000);

  //motors: set velocity
  analogWrite(motorL_en, pwm_velocity);
  analogWrite(motorR_en, pwm_velocity);

  pinMode(encoderL_A, INPUT);
  pinMode(encoderL_B, INPUT);
  pinMode(encoderR_A, INPUT);
  pinMode(encoderR_B, INPUT);

}

void loop() {

  pinMode(LED_BUILTIN, HIGH);
  delay(500);
  pinMode(LED_BUILTIN, LOW);
  delay(500);

}
