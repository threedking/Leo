#include "ArduinoMotor.h"
//----------------
void IArduinoMotor::GoForward(){
  this->SetDirection(true,false);
}
void IArduinoMotor::GoBackward(){
  this->SetDirection(false,true);
}
void IArduinoMotor::Stop(){
  this->SetDirection(false,false);
}
//----------------
//----------------
//----------------
ArduinoMotor3Pins::ArduinoMotor3Pins(uint8_t new_pin_forward,uint8_t new_pin_backward,uint8_t new_pin_speed){
  if( new_pin_forward <= 100 && new_pin_backward <= 100 && new_pin_speed <= 100 ){
    this->pin_forward_=new_pin_forward;
    this->pin_backward_=new_pin_backward;
    this->pin_speed_=new_pin_speed;
    pinMode(this->pin_forward_,OUTPUT);  
    pinMode(this->pin_backward_,OUTPUT);  
    pinMode(this->pin_speed_,OUTPUT);  
  }else{
    Serial.println("Motor pins set wrong");
  } 
}
//----------------  
void ArduinoMotor3Pins::SetSpeed(uint8_t speed){
  analogWrite(this->pin_speed_, speed);    
}
//----------------
void ArduinoMotor3Pins::SetDirection(bool forward, bool backward){
  digitalWrite(this->pin_forward_, forward ? HIGH : LOW);
  digitalWrite(this->pin_backward_, backward ? HIGH : LOW);    
}
//----------------
//----------------
//----------------
ArduinoMotor2Pins::ArduinoMotor2Pins(uint8_t new_pin_forward,uint8_t new_pin_backward){
  if( new_pin_forward <= 100 && new_pin_backward <= 100 ){
    this->pin_forward_=new_pin_forward;
    this->pin_backward_=new_pin_backward;
    pinMode(this->pin_forward_,OUTPUT);  
    pinMode(this->pin_backward_,OUTPUT);  
  }else{
    Serial.println("Motor pins set wrong");
  } 
} 
//----------------  
void ArduinoMotor2Pins::ApplyEngineParameters(){
  analogWrite(this->pin_forward_, this->direction_forward_ ? this->speed_ : 0);
  analogWrite(this->pin_backward_, this->direction_backward_ ? this->speed_ : 0);  
}
//----------------
void ArduinoMotor2Pins::SetSpeed(uint8_t speed){
  this->speed_=speed;
  this->ApplyEngineParameters();          
}  
//----------------
void ArduinoMotor2Pins::SetDirection(bool forward, bool backward){
  this->direction_forward_=forward;
  this->direction_backward_=backward;
  this->ApplyEngineParameters();
}  
//----------------
