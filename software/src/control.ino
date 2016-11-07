/**
* @Author: emanuleft_right_errorror
* @Date:   2016-10-16T18:16:30-04:00
@Last modified by:   emanuleft_right_errorror
@Last modified time: 2016-10-16T03:22:39-04:00
*/

/*
*  Control:
*     Control Sistem of the Line Followright_error
*/

#include "Teensy_Encoder.h"

// Temporal interrupts
IntervalTimer controllerTimer;
#define interruptTiming 1000 //1000 -> 1ms

// Movile Constants
#define r 1.72  //wheel radius
#define L 7.6   //distance between wheels

//Control Variables
#define kpW 90000
#define kdW 1000

#define kpV 250
#define kdV 50

// Encoder variables.
#define counts_to_mm 11.06
int32_t  enc_count_left, enc_count_right;
int32_t  enc_count_left_old, enc_count_right_old;
float VL, VR, Vmean, Wenc; // mm/s

//left motor
double linearSpeed_output;         // control output
double linearSpeed_setpoint;         // control output

//right motor

double angularSpeed_output;         // control output
double angularSpeed_setpoint;         // control output

// PD variables
double Verror_now;
double Verror_old;
double Verror_dif;
double Werror_now;
double Werror_old;
double Werror_dif;

int32_t leftSpeed;
int32_t rightSpeed;

void controlInit(void){
  configureEncoderLib();
  controllerTimer.begin(interruptHandler, interruptTiming);
}

void interruptHandler(void){
  updateEncoderStatus();
  PD_controller();
}

void updateEncoderStatus(void){
  // Read the encoder count
  enc_count_left  = getRot1Steps();
  enc_count_right = getRot2Steps();

  // Calculate wheel speeds in mm/s
  VR = (enc_count_right - enc_count_right_old) / counts_to_mm * 1000 * 1000/interruptTiming; // the *1000 is to convert from mm/ms to mm/s
  VL = (enc_count_left - enc_count_left_old)   / counts_to_mm * 1000 * 1000/interruptTiming;
  Vmean = (VR + VL)/2;        // Mean speed
  Wenc = (VR - VL)*r/L;           // angular velocity measured by the encoders in degree/s

  // Update variables
  enc_count_right_old = enc_count_right;
  enc_count_left_old = enc_count_left;
}

void PD_controller () {
  double angularSpeed_input;          // actual speed
  double linearSpeed_input;          // actual speed
  double encoderFeedbackV;
  double encoderFeedbackW;

  // Serial.print("\nVmean");
  // Serial.print(Vmean);

  //encoderFeedbackW = Wenc;
  encoderFeedbackV = Vmean;
  Werror_now = angularSpeed_setpoint - 0;
  //Werror_now = angularSpeed_setpoint - getMatrixCenterMass();
  Verror_now = linearSpeed_setpoint - encoderFeedbackV;

  Werror_dif = Werror_now - Werror_old;
  Verror_dif = Verror_now - Verror_old;

  angularSpeed_output = (kpW * Werror_now) + (kdW * Werror_dif);
  linearSpeed_output = (kpV * Verror_now) + (kdV * Verror_dif);

  Werror_old = Werror_now;
  Verror_old = Verror_now;

  leftSpeed = (int32_t)(linearSpeed_output - angularSpeed_output);
  rightSpeed = (int32_t)(linearSpeed_output + angularSpeed_output);

  // Serial.print("\nW Error: ");
  // Serial.print(Werror_now);
  // Serial.print("\t\tW: ");
  // Serial.print(angularSpeed_output);
  // Serial.print("\t\tV Error: ");
  // Serial.print(Verror_now);
  // Serial.print("\t\tV: ");
  // Serial.print(linearSpeed_output);
  // Serial.print("\t\tLeftSpeed: ");
  // Serial.print(leftSpeed);
  // Serial.print("\t\t");
  // //Serial.print(linearSpeed_output + angularSpeed_output);
  // Serial.print("\t\tRightSpeed: ");
  // Serial.print(rightSpeed);
  // Serial.print("\t\t");
  // //Serial.print(linearSpeed_output - angularSpeed_output);

  if(leftSpeed > 65535){
    leftSpeed = 65535;
  }
  else if(leftSpeed < -65535){
    leftSpeed = -65535;
  }

  if(rightSpeed > 65535){
    rightSpeed = 65535;
  }
  else if(rightSpeed < -65535){
    rightSpeed = -65535;
  }

  // Serial.print("\nleftSpeed: ");
  // Serial.print(leftSpeed);
  // //Serial.print("\t\t\tErro")
  // Serial.print("\nrightSpeed: ");
  // Serial.print(rightSpeed);

  setLeftVelocity(leftSpeed);
  setRightVelocity(rightSpeed);
}

float getVR(void){

    return VR;
}

float getVL(void){

    return VL;
}

float getVmean(void){

    return Vmean;
}

//Controller setpoint
void setSetPointV(float spv){

    linearSpeed_setpoint = spv;
}

float getSetPointV(void){

    return linearSpeed_setpoint;
}

float getSetPointW(void){

    return angularSpeed_setpoint;
}

void setSetPointW(float spw){

    angularSpeed_setpoint = spw;
}
