#include "Car.h"

TwoAxleCar *p_leo = TwoAxleCar(
  TwinEngineDrivingAxle(ArduinoMotor3Pins(6, 7, 5), ArduinoMotor3Pins(8, 9, 10)) ,
  ServoSteeringAxle(11, 90, 180) );

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
