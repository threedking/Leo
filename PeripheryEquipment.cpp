#include "PeripheryEquipment.h"
//----------------
UltraSonicSensor::UltraSonicSensor(uint8_t new_pin_trig, uint8_t new_pin_echo): pin_trig_(new_pin_trig), pin_echo_(new_pin_echo){
  if( this->pin_trig_ <= 100 && this->pin_echo_ <= 100 ){
    pinMode(this->pin_trig_,OUTPUT);  
    pinMode(this->pin_echo_,INPUT);  
  }else{
    Serial.println("Ultra Sonic Sensor pins set wrong");
  } 
}
//----------------
int UltraSonicSensor::GetDistanceCM(){  
  long duration;
  digitalWrite(this->pin_trig_, LOW);
  delayMicroseconds(2);
  digitalWrite(this->pin_trig_, HIGH);
  delayMicroseconds(20);
  digitalWrite(this->pin_trig_, LOW);
  duration = pulseIn(this->pin_echo_, HIGH);
  duration /= 59;
  return duration < 2 || duration > 200 ? 200 : duration;
}
//----------------
//----------------
//----------------
DigitalSensor::DigitalSensor(uint8_t new_pin): pin_(new_pin){
  if( this->pin_ <= 100){
    pinMode(this->pin_,OUTPUT);
  }else{
    Serial.println("Digital Sensor pin set wrong");
  } 
}
//----------------
bool DigitalSensor::GetState(){
  return digitalRead(this->pin_);
}
//----------------
