#include "LED.h"
//----------------
iLED::iLED(uint8_t new_pin):pin_(new_pin){
  if( this->pin_ > 100){
    Serial.println("LED pin set wrong");
  } 
}
//----------------
//----------------
//----------------
LEDDigital::LEDDigital(uint8_t new_pin):iLED(new_pin){
  pinMode(this->pin_, OUTPUT);
  this->TurnOff();
}
//----------------
void LEDDigital::TurnOn(){
  digitalWrite(this->pin_, HIGH);
}
//----------------
void LEDDigital::TurnOff(){
  digitalWrite(this->pin_, LOW);
}
//----------------
//----------------
//----------------
LEDPWM::LEDPWM(uint8_t new_pin):iLED(new_pin){
  this->TurnOff();
}
//----------------
void LEDPWM::TurnOn(uint8_t new_pwm){
  this->pwm_ = new_pwm;
  analogWrite(this->pin_, pwm_);
}
//----------------
void LEDPWM::TurnOn(){
  this->pwm_ = 255;
  analogWrite(this->pin_, pwm_);    
}
//----------------
void LEDPWM::TurnOff(){
  this->pwm_ = 0;
  analogWrite(this->pin_, pwm_);  
}
//----------------
uint8_t LEDPWM::GetPWM(){
  return this->pwm_;
}
//----------------
//----------------
//----------------
LEDAnimatedPWM::LEDAnimatedPWM(uint8_t new_pin):LEDPWM(new_pin){
  this->TurnOff();
}
//----------------
void LEDAnimatedPWM::Breath(unsigned long &now){
  static unsigned long temp=0;
  temp = this->period_ / this->coef_offset_;
  if(temp == 1){
    temp = 0;
  }
      
  this->pwm_ = uint8_t( sin( exp( sin( (now - temp) / (this->period_*this->coef_period_) *PI ) ) -0.36787944 ) * 255.0 );      
      
  analogWrite(this->pin_, this->pwm_);
  Serial.println(this->pwm_);
} 
//----------------
void LEDAnimatedPWM::SetPeriod(double new_period){
  this->SetPeriod(new_period, 1, new_period);
} 
//----------------
void LEDAnimatedPWM::SetPeriod(double new_period, double new_coef_period, double new_coef_offset){
  if(abs(new_period) > 1e-8){
    this->period_ = new_period;
  }
  if(abs(new_coef_period) > 1e-8){
    this->coef_period_ = new_coef_period;
  }
  if(abs(new_coef_offset) > 1e-8){
    this->coef_offset_ = new_coef_offset;
  }
}
//----------------
//----------------
//----------------
RGBLEDAnimatedPWM::RGBLEDAnimatedPWM(uint8_t new_pin_r, uint8_t new_pin_g, uint8_t new_pin_b): leds_{new_pin_r, new_pin_g, new_pin_b} {
}
//----------------
void RGBLEDAnimatedPWM::TurnOn(){
  this->leds_[0].TurnOn();
  this->leds_[1].TurnOn();
  this->leds_[2].TurnOn();  
}
//----------------    
void RGBLEDAnimatedPWM::TurnOff(){
  this->leds_[0].TurnOff();
  this->leds_[1].TurnOff();
  this->leds_[2].TurnOff();
}
//----------------        
void RGBLEDAnimatedPWM::Breath(unsigned long &now){
  this->leds_[0].Breath(now);
  this->leds_[1].Breath(now);
  this->leds_[2].Breath(now);
}
//----------------
void RGBLEDAnimatedPWM::SetPeriod(double new_period){
  this->leds_[0].SetPeriod(new_period);
  this->leds_[1].SetPeriod(new_period);
  this->leds_[2].SetPeriod(new_period);
}
//----------------    
void RGBLEDAnimatedPWM::SetPeriod(double new_period, double new_coef_period, double new_coef_offset){
  this->leds_[0].SetPeriod(new_period, new_coef_period, new_coef_offset);
  this->leds_[1].SetPeriod(new_period, new_coef_period, new_coef_offset);
  this->leds_[2].SetPeriod(new_period, new_coef_period, new_coef_offset);
}
//----------------    
