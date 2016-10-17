/**
* @Author: emanuel
* @Date:   2016-10-12T17:26:51-04:00
@Last modified by:   emanuel
@Last modified time: 2016-10-16T03:22:39-04:00
*/



 /*
 *
 *  Motors and Encoders Test
 *  Turn on a led when detect the black (HIGH)
 *
 */

#include<Arduino.h>

// Pins Definitions
//Encoders
const int encoderL_A = 23;  //orange wire
const int encoderL_B = 22;  //yellow wire
const int encoderR_A = 15;  //orange wire
const int encoderR_B = 16;  //yellow wire

long tick_L = 0;
long tick_R = 0;

void count_L(){
  tick_L++;
}

void count_R(){
  tick_R++;
}

void encodersINIT() {

  pinMode(encoderL_A, INPUT);
  pinMode(encoderL_B, INPUT);
  pinMode(encoderR_A, INPUT);
  pinMode(encoderR_B, INPUT);

  attachInterrupt(digitalPinToInterrupt(encoderR_A), count_R, RISING);
  attachInterrupt(digitalPinToInterrupt(encoderL_A), count_L, RISING);

}

/********* PROOF FUNCTIONS **********/

void encoderLeftProof() {
  digitalWriteFast(LED_BUILTIN, HIGH);
  delay(100);
  digitalWriteFast(LED_BUILTIN, LOW);
  Serial.println("left");
}

void encoderRightProof() {
  digitalWriteFast(LED_BUILTIN, HIGH);
  delay(100);
  digitalWriteFast(LED_BUILTIN, LOW);
  Serial.println("right");
}

void encodersINITPROOF() {

  pinMode(encoderL_A, INPUT);
  pinMode(encoderL_B, INPUT);
  pinMode(encoderR_A, INPUT);
  pinMode(encoderR_B, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(encoderR_A), encoderRightProof, RISING);
  attachInterrupt(digitalPinToInterrupt(encoderL_A), encoderLeftProof, RISING);

}
