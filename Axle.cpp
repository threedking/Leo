#include "Axle.h"
//----------------
TwinEngineDrivingAxle::TwinEngineDrivingAxle(IArduinoMotor *p_motor_left,IArduinoMotor *p_motor_right): p_motor_left_(p_motor_left), p_motor_right_(p_motor_right){  
  if(p_motor_left_==NULL || p_motor_right_==NULL){    
    Serial.println("Motor pointer set NULL");
  }
}
//----------------
TwinEngineDrivingAxle::~TwinEngineDrivingAxle(){
  if(p_motor_left_!=NULL){
    delete p_motor_left_;
    p_motor_left_=NULL;
  }  
  if(p_motor_right_!=NULL){
    delete p_motor_right_;
    p_motor_right_=NULL;
  }  
}
//----------------
void TwinEngineDrivingAxle::SetTurn(Turn new_turn){
  this->turn_=new_turn;
  this->SetSpeed(this->speed_);
}
//----------------
void TwinEngineDrivingAxle::SetSpeed(uint8_t new_speed){  
  this->p_motor_left_->SetSpeed(this->turn_ == Turn::LEFT ? abs(static_cast<int>(new_speed)*this->speed_difference_in_turn_)/100 : new_speed);
  this->p_motor_right_->SetSpeed(this->turn_ == Turn::RIGHT ? abs(static_cast<int>(new_speed)*this->speed_difference_in_turn_)/100 : new_speed);
  if(this->speed_difference_in_turn_ < 0){//Если разница скоростей в повороте отрицательная, то обратить направление внутреннего колеса
    if(this->turn_ == Turn::LEFT){
      this->p_motor_left_->SetDirection(this->is_going_forward_ ? false : true, this->is_going_forward_ ? true : false);
    }else if(this->turn_ == Turn::RIGHT){
      this->p_motor_right_->SetDirection(this->is_going_forward_ ? false : true, this->is_going_forward_ ? true : false);
    }
  }
}
//----------------
void TwinEngineDrivingAxle::SetSpeedDifferenceInTurn(int8_t new_speed_difference_in_turn){
  this->speed_difference_in_turn_=constrain(new_speed_difference_in_turn,-100,100);  
  this->SetSpeed(this->speed_);
}
//----------------
void TwinEngineDrivingAxle::Stop(){  
  is_going_forward_=true;
  this->p_motor_left_->Stop();
  this->p_motor_right_->Stop();
}
//----------------
void TwinEngineDrivingAxle::GoLeft(){
  is_going_forward_=true;
  this->GoLeftTankStyle();
}
//----------------
void TwinEngineDrivingAxle::GoRight(){
  is_going_forward_=true;
  this->GoRightTankStyle();
}
//----------------
void TwinEngineDrivingAxle::GoLeftTankStyle(){
  this->p_motor_left_->GoBackward();
  this->p_motor_right_->GoForward();
  this->SetTurn(Turn::FRONT);
}
//----------------
void TwinEngineDrivingAxle::GoRightTankStyle(){
  this->p_motor_left_->GoForward();
  this->p_motor_right_->GoBackward();
  this->SetTurn(Turn::FRONT);
}
//----------------
void TwinEngineDrivingAxle::GoForward(){
  is_going_forward_=true;
  this->p_motor_left_->GoForward();
  this->p_motor_right_->GoForward();
  this->SetTurn(Turn::FRONT);
}
//----------------
void TwinEngineDrivingAxle::GoBackward(){
  is_going_forward_=false;
  this->p_motor_left_->GoBackward();
  this->p_motor_right_->GoBackward();
  this->SetTurn(Turn::FRONT);
}
//----------------
void TwinEngineDrivingAxle::GoForwardRight(){  
  is_going_forward_=true;
  this->p_motor_left_->GoForward();
  this->p_motor_right_->GoForward();
  this->SetTurn(Turn::RIGHT);
}
//----------------
void TwinEngineDrivingAxle::GoForwardLeft(){
  is_going_forward_=true;
  this->p_motor_left_->GoForward();
  this->p_motor_right_->GoForward(); 
  this->SetTurn(Turn::LEFT);
}
//----------------
void TwinEngineDrivingAxle::GoBackwardRight(){  
  is_going_forward_=false;
  this->p_motor_left_->GoBackward();
  this->p_motor_right_->GoBackward();
  this->SetTurn(Turn::RIGHT); 
}
//----------------
void TwinEngineDrivingAxle::GoBackwardLeft(){
  is_going_forward_=false;
  this->p_motor_left_->GoBackward();
  this->p_motor_right_->GoBackward();  
  this->SetTurn(Turn::LEFT);
}
//----------------
//----------------
//----------------
ServoSteeringAxle::ServoSteeringAxle(uint8_t new_pin_steering_servo, int16_t new_min_angle, int16_t new_max_angle):min_angle_(new_min_angle), max_angle_(new_max_angle), mid_angle_((new_min_angle + new_max_angle) / 2){
  if( new_pin_steering_servo <= 100 && this->max_angle_ > this->min_angle_){
    this->pin_steering_servo_=new_pin_steering_servo;    
    this->servo_.attach(this->pin_steering_servo_); 
  }else{
    Serial.println("Servo pin or min/max angle set wrong");
  }
}
//----------------
ServoSteeringAxle::~ServoSteeringAxle(){
  this->servo_.detach();
}
//----------------
void ServoSteeringAxle::ApplyTurn(){  
  this->servo_.write(this->angle_);
}
//----------------
void ServoSteeringAxle::SetAngleAndApply(int16_t new_angle){
  this->angle_=constrain(new_angle, this->min_angle_, this->max_angle_);  
  this->ApplyTurn();
}
//----------------
void ServoSteeringAxle::TurnStraight(){
  this->SetAngleAndApply(this->mid_angle_);
}
//----------------
void ServoSteeringAxle::TurnMaxLeft(){
  this->SetAngleAndApply(this->min_angle_);
}
//----------------
void ServoSteeringAxle::TurnMaxRight(){
  this->SetAngleAndApply(this->max_angle_);
}
//----------------
void ServoSteeringAxle::AddDegreesToTheRight(uint8_t degrees_right){
  this->SetAngleAndApply(this->angle_ + degrees_right);
}
//----------------
void ServoSteeringAxle::AddDegreesToTheLeft(uint8_t degrees_left){
  this->SetAngleAndApply(this->angle_ - degrees_left);
}
//----------------
void ServoSteeringAxle::TurnPercentLeft(uint8_t percent_left){
  if(percent_left <= 100){
    this->SetAngleAndApply( this->mid_angle_ - (this->mid_angle_ - this->min_angle_) * percent_left / 100 );
  }
}
//----------------
void ServoSteeringAxle::TurnPercentRight(uint8_t percent_right){
  if(percent_right <= 100){
    this->SetAngleAndApply( this->mid_angle_ + (this->max_angle_ - this->mid_angle_) * percent_right / 100 );
  }
}
//----------------
void ServoSteeringAxle::Stop(){  
}
//----------------
void ServoSteeringAxle::GoLeft(){
  this->TurnMaxLeft();
}
//----------------
void ServoSteeringAxle::GoRight(){  
  this->TurnMaxRight();  
}
//----------------
void ServoSteeringAxle::GoForward(){
  this->TurnStraight();
}
//----------------
void ServoSteeringAxle::GoBackward(){
  this->TurnStraight();  
}
//----------------
void ServoSteeringAxle::GoForwardRight(){  
  this->TurnMaxRight();
}
//----------------
void ServoSteeringAxle::GoForwardLeft(){
  this->TurnMaxLeft();
}
//----------------
void ServoSteeringAxle::GoBackwardRight(){
  this->TurnMaxRight();  
}
//----------------
void ServoSteeringAxle::GoBackwardLeft(){
  this->TurnMaxLeft();
}
//----------------
void ServoSteeringAxle::SetSpeed(uint8_t new_speed){
  
}
//----------------
