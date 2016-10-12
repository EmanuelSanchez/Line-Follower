 /*
 * 
 *  Motors and Encoders Test
 *
 */

uint8_t pwm_velocity = 60;

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

int lec;

void setup() {

  Serial.begin(9600);

  //motors: pinout configuration
  pinMode(motorL_en, OUTPUT);
  pinMode(motorL_phase, OUTPUT);
  pinMode(motorR_en, OUTPUT);
  pinMode(motorR_phase, OUTPUT);

  //encoders: pinout configuration
  pinMode(encoderL_A, INPUT);
  pinMode(encoderL_B, INPUT);
  pinMode(encoderR_A, INPUT);
  pinMode(encoderR_B, INPUT);

  pinMode(13, OUTPUT);

  //motors: direction
  digitalWrite(motorL_phase, HIGH);
  digitalWrite(motorR_phase, HIGH);

  //wait 2 seconds
  delay(2000);

  //motors: set velocity
  analogWrite(motorL_en, pwm_velocity);
  analogWrite(motorR_en, pwm_velocity);

}

void loop() {
  /*
  lec = analogRead(encoderR_A);
  if(lec<150){
      analogWrite(motorL_en, 0);
      analogWrite(motorR_en, pwm_velocity);
  }
  else{
      analogWrite(motorL_en, pwm_velocity);
      analogWrite(motorR_en, 0);
  }
  */
  
  //Serial.println(analogRead(encoderR_A));
  if(+(digitalReadFast(encoderL_B))==HIGH)
  {
    digitalWriteFast(13, LOW);
  }
  else
  {
    digitalWriteFast(13, HIGH);
  }
  Serial.println(digitalRead(encoderL_B));
  //Serial.println(digitalRead(encoderR_A));
  //Serial.println(analogRead(encoderL_B));
  //Serial.println(analogRead(encoderR_A));
  //Serial.println(analogRead(encoderR_B));


}
