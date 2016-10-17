/**
* @File-Name: Led Proof
* @Author: emanuel
* @Date:   2016-10-16T03:20:37-04:00
* @Last modified by:   emanuel
* @Last modified time: 2016-10-16T03:21:17-04:00
*/

 #include <Arduino.h>

// Pins Definitions
//Led
const int led = 13;

void setup() {

  pinMode(led, OUTPUT);

}

void loop() {

  digitalWriteFast(led, HIGH);
  delay(50);
  digitalWriteFast(led, LOW);
  delay(50);

}
