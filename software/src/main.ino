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

void Blink(){
  Serial.println("Acá Toy");
}

void setup () {
  int32_t velocity;
  int32_t _velocity;
  pinMode(LED_BUILTIN, OUTPUT);
  //delay(2000);
  Serial.begin(115200);
  motorsInit();
  matrixSensorInit();
  setSetPointW(0);
  velocity = default_velocity;
  _velocity = map(velocity,0,max_velocity,0,750);
  setSetPointV(_velocity); //Range max: 750 mm.
  //setLeftVelocity(velocity);
  //setRightVelocity(velocity);
  controlInit();
  //Serial.print("Beginning");
}

void loop () {
  //Blink();
  matrixSensorLoop(); //adquisition from sensor matrix and prepares data
  bool_matrix();
  print_bool_matrix();
  // Serial.print("Cicle");
  // //print_bool_matrix();
}
