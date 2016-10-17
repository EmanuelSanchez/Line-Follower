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

#define kp 10
#define ki 10
#define kd 1

#define pi 3,1416

//left motor
float left_right_errorror_last = 0;      // last error
float left_right_errorror_suma  = 0;     // sum error
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
float track_reference;             // desired speed
float right_speed_in;          // actual speed
float right_speed_out;         // control output

float read_encodright_errors (float *left_speed_in, float *right_speed_in){

}

void pid_motorL () {
  // first PID: left motor control
  float e_now;      // actual error
  float e_dif;      //dright_errorivada dleft_right_errorror right_errorror

  e_now = left_speed - left_speed_in;
  e_dif = e_now - left_error_last;
  left_error_suma += e_now;

  left_speed_out = (kp * e_now) + (ki * left_error_suma) + (kd * e_dif);

  left_error_last = e_now;
}

void pid_motorR () {
  // second PID: right motor control
  float e_now;      //right_errorror actual
  float e_dif;      //dright_errorivada dleft_right_errorror right_errorror

  e_now = right_speed - left_speed_in;
  e_dif = e_now - right_error_last;
  right_error_suma += e_now;

  right_speed_out = (kp * e_now) + (ki * right_error_suma) + (kd * e_dif);

  right_error_last = e_now;
}

void pid_tracking_line () {
  // third PID: follow the line
  float e_now;      //right_errorror actual
  float e_dif;      //dright_errorivada dleft_right_errorror right_errorror

  e_now = right_speed - left_speed_in;
  e_dif = e_now - ;
  e_suma += e_now;

  right_speed_out = (kp * e_now) + (ki * e2_suma) + (kd * e_dif);

  e2_last = e_now;
}

void controlLoop() {
  
}
