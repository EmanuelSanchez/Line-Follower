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

//Led
const int led = 13;

uint8_t tick_L = 0;
uint8_t tick_R = 0;

void count_L(){
  tick_L++;
  Serial.println();
  Serial.print("Left: ");
  Serial.println(tick_L);
}

void count_R(){
  tick_R++;
  Serial.println();
  Serial.print("Right: ");
  Serial.println(tick_R);
}

void encodersINIT() {

  pinMode(led, OUTPUT);

  pinMode(encoderL_A, INPUT);
  pinMode(encoderL_B, INPUT);
  pinMode(encoderR_A, INPUT);
  pinMode(encoderR_B, INPUT);

}

void encodersINIT1() {

  Serial.begin(9600);

  pinMode(led, OUTPUT);

  pinMode(encoderL_A, INPUT);
  pinMode(encoderL_B, INPUT);
  pinMode(encoderR_A, INPUT);
  pinMode(encoderR_B, INPUT);

  attachInterrupt(digitalPinToInterrupt(encoderR_A), count_R, RISING);
  attachInterrupt(digitalPinToInterrupt(encoderL_A), count_L, RISING);

}

void encodersProof() {

  if(digitalReadFast(encoderL_A)==HIGH)
  {
    digitalWriteFast(led, HIGH);
  }
  else
  {
    digitalWriteFast(led, LOW);
  }

}