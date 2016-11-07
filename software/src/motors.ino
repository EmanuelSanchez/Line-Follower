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
#include <pinout.h>

void setLeftVelocity(int32_t pwm){
  if (pwm<0){
    digitalWriteFast(motorL_phase, LOW);
    pwm = abs(pwm);
    analogWrite(motorL_en, pwm);
  }
  else{
    digitalWriteFast(motorL_phase, HIGH);
    analogWrite(motorL_en, pwm);
  }
}

void setRightVelocity(int32_t pwm){
  if (pwm<0){
    digitalWriteFast(motorR_phase, LOW);
    pwm = abs(pwm);
    analogWrite(motorR_en, pwm);
  }
  else{
    digitalWriteFast(motorR_phase, HIGH);
    analogWrite(motorR_en, pwm);
  }
}

void motorsInit () {
  //motors: pinout configuration
  pinMode(motorL_en, OUTPUT);
  pinMode(motorL_phase, OUTPUT);

  pinMode(motorR_en, OUTPUT);
  pinMode(motorR_phase, OUTPUT);

  digitalWriteFast(motorL_phase, HIGH);
  digitalWriteFast(motorR_phase, HIGH);

  //Set resolution to maximum, 16 bits
  analogWriteResolution(16);

  // Initialize motors turned off
  analogWrite(motorL_en, 0);
  analogWrite(motorR_en, 0);
}

void motorsProof () {
  digitalWriteFast(LED_BUILTIN, HIGH);
  delay(50);
  digitalWriteFast(LED_BUILTIN, LOW);
  delay(50);
}
