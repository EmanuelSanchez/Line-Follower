 /*
 * 
 *  Motors and Encoders Test
 *
 */

#define pwm_velocity 125

// Pins Definitions
//Motors:
const int motorL_en = 3;      // violet wire
const int motorL_phase = 2;   // blue wire
const int motorR_en = 4;      // violet wire
const int motorR_phase = 5;   // blue wire

//Encoders
const int encoderL_A = 23;  //orange wire
const int encoderL_B = 22;  //yellow wire
const int encoderR_A = 15;  //orange wire
const int encoderR_B = 16;  //yellow wire

void setup() {

  Serial.begin(230400);

  //motors: pinout configuration
  pinMode(motorL_en, OUTPUT);
  pinMode(motorL_phase, OUTPUT);
  pinMode(motorR_en, OUTPUT);
  pinMode(motorR_phase, OUTPUT);

  //motors: direction
  digitalWrite(motorL_phase, HIGH);
  digitalWrite(motorR_phase, HIGH);

  //wait 2 seconds
  delay(2000);

  //motors: set velocity
  analogWrite(motorL_en, pwm_velocity);
  analogWrite(motorR_en, pwm_velocity);

  pinMode(encoderL_A, INPUT);
  pinMode(encoderL_B, INPUT);
  pinMode(encoderR_A, INPUT);
  pinMode(encoderR_B, INPUT);

}

void loop() {
  


}
