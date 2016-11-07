/**
* @Author: emanuel
* @Date:   2016-10-16T12:40:32-04:00
@Last modified by:   emanuel
@Last modified time: 2016-10-16T03:22:39-04:00
*/

#include <defines.h>
#include "Teensy_Encoder.h"
#include "pinout.h"

#define motorL_en 3      // violet wire
#define motorL_phase 2   // blue wire
#define motorR_en 4      // violet wire
#define motorR_phase 5   // blue wire

void setup () {
  //delay(2000);
  Serial.begin(115200);
  motorsInit();
  matrixSensorInit();
  setSetPointW(0);
  setSetPointV(350/3); //Range max: 750 mm.
  setLeftVelocity(default_velocity/3);
  setRightVelocity(default_velocity/3);
  controlInit();
  Serial.print("Beginning");
}

void loop () {
  matrixSensorLoop(); //adquisition from sensor matrix and prepares data
  bool_matrix();
  Serial.print("Cicle");
  //print_bool_matrix();
}
