/**
* @Author: emanuel
* @Date:   2016-10-16T12:40:32-04:00
@Last modified by:   emanuel
@Last modified time: 2016-10-16T03:22:39-04:00
*/

#include<Arduino.h>

// all libraries are contained in #include<ontrol.cpp>
#include<control.cpp>

void setMotorsOFF(){
  setLeftVelocity(0);
  setRightVelocity(0);
  delay(3000);
}

void setup () {
  //encodersINITPROOF();
  Serial.begin(115200);
  delay(1000);
  matrixSensorInit();
  delay(2000);
  //encodersINITPROOF();
  //motorsInit();   // Default speed = 125
  //offTimer.begin(setMotorsOFF, 2000000);
  //setLeftVelocity(0);
  //setRightVelocity(0);
}

void loop () {
  matrixSensorLoop();
  send_matrix();
  //bool_line();
  //print_bool_line();
  //controlLoop();

/*
  if(Serial.read()=='w'){
    setLeftVelocity(200);
    setRightVelocity(200);
  }
  if(Serial.read()=='s'){
    setLeftVelocity(0);
    setRightVelocity(0);
  }
  if(Serial.read()=='d'){
    setLeftVelocity(200);
    setRightVelocity(120);
  }
  if(Serial.read()=='a'){
    setLeftVelocity(120);
    setRightVelocity(200);
  }
*/

}
