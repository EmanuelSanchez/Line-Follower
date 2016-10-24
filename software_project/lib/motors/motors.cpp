/**
* @Author: emanuel
* @Date:   2016-10-16T13:48:50-04:00
@Last modified by:   emanuel
@Last modified time: 2016-10-16T03:22:39-04:00
*/


/*
*   Motors
*   Proof the motors with PWM and determinate velocity (pwm_velocity)
*/

#include <Arduino.h>

// Pins Definitions
//Motors:
const int motorL_en = 3;      // violet wire
const int motorL_phase = 2;   // blue wire
const int motorR_en = 4;      // violet wire
const int motorR_phase = 5;   // blue wire

const int default_velocity = 105;
const int max_velocity = 255;

void setLeftVelocity(uint8_t _pwm_velocity){
  analogWrite(motorL_en, _pwm_velocity);
}

void setRightVelocity(uint8_t _pwm_velocity){
  analogWrite(motorR_en, _pwm_velocity);
}

void motorsInit () {

  //motors: pinout configuration
  pinMode(motorL_en, OUTPUT);
  pinMode(motorL_phase, OUTPUT);
  pinMode(motorR_en, OUTPUT);
  pinMode(motorR_phase, OUTPUT);

  //motors: direction
  digitalWrite(motorL_phase, HIGH);
  digitalWrite(motorR_phase, HIGH);

  //wait 2 seconds
  delay(2000);

  //motors: set velocity
  setLeftVelocity(default_velocity);
  setRightVelocity(default_velocity);
}

void motorsProof () {
  digitalWriteFast(LED_BUILTIN, HIGH);
  delay(50);
  digitalWriteFast(LED_BUILTIN, LOW);
  delay(50);
}
