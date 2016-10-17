/**
* @Author: emanuel
* @Date:   2016-10-16T12:40:32-04:00
@Last modified by:   emanuel
@Last modified time: 2016-10-16T03:22:39-04:00
*/

#include<Arduino.h>

// all libraries are contained in #include<ontrol.cpp>
#include<control.cpp>


void setup () {
  encodersINIT();
  Serial.begin(115200);
  matrixSensorInit();
  motorsInit();   // Default speed = 125
}

void loop () {
  matrixSensorLoop();
  //print_matrix();
  bool_line();
  print_bool_line();
  controlLoop();
}
