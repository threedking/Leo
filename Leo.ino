#include "Car.h"

TwoAxleCar *p_leo = new TwoAxleCar(
  new TwinEngineDrivingAxle(new ArduinoMotor3Pins(6, 7, 5), new ArduinoMotor3Pins(8, 9, 10)) , 
  new ServoSteeringAxle(11, 0, 180) );

void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
