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

// constans to left motor control
#define kpL 10
#define kiL 10
#define kdL 1

// constans to right motor control
#define kpR 10
#define kiR 10
#define kdR 1

// constans to track line control
#define kpT 60
#define kiT 10
#define kdT 0

#define pi 3,1416
#define line_reference 3  // line is array of 7 sensors, the middle is the Reference (3)
#define max_output_signal 125 // the signal control can't exceed the max speed (255), natural speed + signal control <= max speed

//left motor
float left_error_last = 0;      // last error
float left_error_suma  = 0;     // sum error
float left_speed;             // desired speed
float left_speed_in;          // actual speed
float left_speed_out;         // control output

//right motor
float right_error_last = 0;      // last error
float right_error_suma  = 0;     // sum error
float right_speed;             // desired speed
float right_speed_in;          // actual speed
float right_speed_out;         // control output

//right motor
float track_error_last = 0;      // last error
float track_error_suma  = 0;     // sum error
float track_output_signal;       // control signal to track line

/*
float read_encodright_errors (float *left_speed_in, float *right_speed_in){

}
*/
void pid_motorL () {
  // first PID: left motor control
  float error_now;      // actual error
  float error_dif;      //dright_errorivada dleft_right_errorror right_errorror

  error_now = left_speed - left_speed_in;
  error_dif = error_now - left_error_last;
  left_error_suma += error_now;
  left_error_last = error_now;

  left_speed_out = (kpL * error_now) + (kiL * left_error_suma) + (kdL * error_dif);
}

void pid_motorR () {
  // second PID: right motor control
  float error_now;      //right_errorror actual
  float error_dif;      //dright_errorivada dleft_right_errorror right_errorror

  error_now = right_speed - right_speed_in;
  error_dif = error_now - right_error_last;
  right_error_suma += error_now;
  right_error_last = error_now;

  right_speed_out = (kpR * error_now) + (kiR * right_error_suma) + (kdR * error_dif);
}

void pid_tracking_line () {
  // third PID: follow the line

  float error_now;
  float error_dif;

  for(int i=0; i<7; i++){
    if(line[i]){
      error_now=i-line_reference;    // line is array of 7 sensors, the middle is the Reference (3)
    }
  }
//  Serial.print("Error");
//  Serial.println(error_now);

  error_dif = error_now - track_error_last;
  track_error_suma += error_now;
  track_error_last = error_now;

  track_output_signal = (kpT * error_now) + (kiT * track_error_suma) + (kdT * error_dif);
//  Serial.print("Signal");
//  Serial.println(track_output_signal);
}

void controlLoop(){
  pid_tracking_line();

  if(track_output_signal > max_output_signal){
    track_output_signal = max_output_signal;
  }
  else if(track_output_signal < -max_output_signal){
    track_output_signal = -max_output_signal;
  }
//  Serial.print("Final Signal: \t");
//  Serial.println(track_output_signal);

  if(track_output_signal<0){      // line at left side
    setLeftVelocity(default_velocity+track_output_signal);
    setRightVelocity(default_velocity-track_output_signal);
/*    Serial.println("left side");
    Serial.print("Leff: \t");
    Serial.println(default_velocity+track_output_signal);
    Serial.print("Right: \t");
    Serial.println(default_velocity-track_output_signal);
    delay(1000);*/
  }
  else if (track_output_signal>0){    // line at rith side
    setLeftVelocity(default_velocity+track_output_signal);
    setRightVelocity(default_velocity-track_output_signal);
/*    Serial.println("right side");
    Serial.print("Leff: \t");
    Serial.println(default_velocity+track_output_signal);
    Serial.print("Right: \t");
    Serial.println(default_velocity-track_output_signal);
    delay(1000);*/
  }
  else{     // line at the middle
    setLeftVelocity(default_velocity);
    setRightVelocity(default_velocity);
  }
  //delay(500);
}
