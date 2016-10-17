/**
* @Author: emanuel
* @Date:   2016-10-12T17:25:42-04:00
@Last modified by:   emanuel
@Last modified time: 2016-10-16T03:22:39-04:00
* @Description:
*   Proof the motors with PWM and determinate velocity (pwm_velocity)
*
*/

#include <Arduino.h>

#define pwm_velocity 0

// Pins Definitions
//Motors:
const int motorL_en = 3;      // violet wire
const int motorL_phase = 2;   // blue wire
const int motorR_en = 4;      // violet wire
const int motorR_phase = 5;   // blue wire

//Encoders
const int encoderL_A = 23;  //orange wire
const int encoderL_B = 22;  //yellow wire
const int encoderR_A = 15;  //orange wire
const int encoderR_B = 16;  //yellow wire

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

