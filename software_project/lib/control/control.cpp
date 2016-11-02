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

#include<matrix.cpp>
#include<motors.cpp>
#include<encoders.cpp>
#include<PID.cpp>

#define Maxmotor_output 125 // the signal control can't exceed the max speed (255), natural speed + signal control <= max speed

//left motor
double Lmotor_input;          // actual speed
double Lmotor_output;         // control output
double Lmotor_setpoint;         // control output
#define kpL 10
#define kiL 10
#define kdL 1

//right motor
double Rmotor_input;          // actual speed
double Rmotor_output;         // control output
double Rmotor_setpoint;         // control output
#define kpR 10
#define kiR 10
#define kdR 1

//line
double line_input;
double line_output;       // control signal to track line
double line_setpoint = 3;  // line is array of 7 sensors, the middle is the Reference (3)
#define kpT 60
#define kiT 10
#define kdT 0

PID pid_motorL(&Lmotor_input, &Lmotor_output, &Lmotor_setpoint, kpL, kiL, kdL, DIRECT);
PID pid_motorR(&Rmotor_input, &Rmotor_output, &Rmotor_setpoint, kpR, kiR, kdR, DIRECT);
PID pid_line(&line_input, &line_output, &line_setpoint, kpT, kiT, kdT, DIRECT);

void controlInit(){

}

void controlLoop(){
  for(int i=0; i<7; i++){
    if(line[i]){
      line_input = i;    // line is array of 7 sensors, the middle is the Reference (3)
    }
  }
}
