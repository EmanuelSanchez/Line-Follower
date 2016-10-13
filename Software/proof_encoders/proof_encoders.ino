 /*
 * 
 *  Motors and Encoders Test
 *  Turn on a led when detect the black (HIGH)
 *
 */

// Pins Definitions
//Encoders
const int encoderL_A = 23;  //orange wire
const int encoderL_B = 22;  //yellow wire
const int encoderR_A = 15;  //orange wire
const int encoderR_B = 16;  //yellow wire

//Led
const int led = 13;

void setup() {

  pinMode(led, OUTPUT);

  pinMode(encoderL_A, INPUT);
  pinMode(encoderL_B, INPUT);
  pinMode(encoderR_A, INPUT);
  pinMode(encoderR_B, INPUT);

}

void loop() {

  if(digitalReadFast(encoderL_A)==HIGH)
  {
    digitalWriteFast(led, HIGH);
  }
  else
  {
    digitalWriteFast(led, LOW);
  }

}
