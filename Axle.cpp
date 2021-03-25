#include "Axle.h"
//----------------
TwinEngineDrivingAxle::TwinEngineDrivingAxle(IArduinoMotor *p_motor_left,IArduinoMotor *p_motor_right): p_motor_left_(p_motor_left), p_motor_right_(p_motor_right){  
  if(this->p_motor_left_==NULL || this->p_motor_right_==NULL){    
    Serial.println("Motor pointer set NULL");
  }
}
//----------------
TwinEngineDrivingAxle::~TwinEngineDrivingAxle(){
  if(this->p_motor_left_ != NULL){
    delete this->p_motor_left_;
    this->p_motor_left_ = NULL;
  }  
  if(this->p_motor_right_ != NULL){
    delete this->p_motor_right_;
    this->p_motor_right_ = NULL;
  }  
}
//----------------
void TwinEngineDrivingAxle::GoLeftTankStyle(){
  this->p_motor_left_->GoBackward();
  this->p_motor_right_->GoForward();
}
//----------------
void TwinEngineDrivingAxle::GoRightTankStyle(){
  this->p_motor_left_->GoForward();
  this->p_motor_right_->GoBackward();
}
//----------------
void TwinEngineDrivingAxle::Stop(){
  this->p_motor_left_->Stop();
  this->p_motor_right_->Stop();
}
//----------------
void TwinEngineDrivingAxle::GoLeft(){
  this->Stop();
}
//----------------
void TwinEngineDrivingAxle::GoRight(){
  this->Stop();
}
//----------------
void TwinEngineDrivingAxle::GoForward(){
  this->p_motor_left_->GoForward();
  this->p_motor_right_->GoForward();
}
//----------------
void TwinEngineDrivingAxle::GoBackward(){
  this->p_motor_left_->GoBackward();
  this->p_motor_right_->GoBackward();
}
//----------------
void TwinEngineDrivingAxle::GoForwardRight(){
  this->p_motor_left_->GoForward();
  this->p_motor_right_->GoForward();
}
//----------------
void TwinEngineDrivingAxle::GoForwardLeft(){
  this->p_motor_left_->GoForward();
  this->p_motor_right_->GoForward(); 
}
//----------------
void TwinEngineDrivingAxle::GoBackwardRight(){
  this->p_motor_left_->GoBackward();
  this->p_motor_right_->GoBackward();
}
//----------------
void TwinEngineDrivingAxle::GoBackwardLeft(){
  this->p_motor_left_->GoBackward();
  this->p_motor_right_->GoBackward();  
}
//----------------
void TwinEngineDrivingAxle::SetSpeed(uint8_t new_speed){  
  this->p_motor_left_->SetSpeed(new_speed);
  this->p_motor_right_->SetSpeed(new_speed);
}
//----------------
//----------------
//----------------
TwinEngineTurningDrivingAxle::TwinEngineTurningDrivingAxle(IArduinoMotor *p_motor_left,IArduinoMotor *p_motor_right): TwinEngineDrivingAxle(p_motor_left, p_motor_right){
}
//----------------
void TwinEngineTurningDrivingAxle::SetTurn(TurnDirection new_turn){
  this->turn_=new_turn;
  this->SetSpeed(this->speed_);
}
//----------------
void TwinEngineTurningDrivingAxle::SetSpeed(uint8_t new_speed){  
  this->p_motor_left_->SetSpeed(this->turn_ == TurnDirection::LEFT ? abs(static_cast<int>(new_speed)*this->speed_difference_in_turn_)/100 : new_speed);
  this->p_motor_right_->SetSpeed(this->turn_ == TurnDirection::RIGHT ? abs(static_cast<int>(new_speed)*this->speed_difference_in_turn_)/100 : new_speed);
  if(this->speed_difference_in_turn_ < 0){//Если разница скоростей в повороте отрицательная, то обратить направление внутреннего колеса
    if(this->turn_ == TurnDirection::LEFT){
      this->p_motor_left_->SetDirection(this->is_going_forward_ ? false : true, this->is_going_forward_ ? true : false);
    }else if(this->turn_ == TurnDirection::RIGHT){
      this->p_motor_right_->SetDirection(this->is_going_forward_ ? false : true, this->is_going_forward_ ? true : false);
    }
  }
}
//----------------
void TwinEngineTurningDrivingAxle::SetSpeedDifferenceInTurn(int8_t new_speed_difference_in_turn){
  this->speed_difference_in_turn_=constrain(new_speed_difference_in_turn,-100,100);  
  this->SetSpeed(this->speed_);
}
//----------------
void TwinEngineTurningDrivingAxle::GoLeftTankStyle(){
  TwinEngineDrivingAxle::GoLeftTankStyle();
  this->SetTurn(TurnDirection::STRAIGHT);
}
//----------------
void TwinEngineTurningDrivingAxle::GoRightTankStyle(){
  TwinEngineDrivingAxle::GoRightTankStyle();
  this->SetTurn(TurnDirection::STRAIGHT);
}
//----------------
void TwinEngineTurningDrivingAxle::Stop(){
  is_going_forward_=true;
  this->p_motor_left_->Stop();
  this->p_motor_right_->Stop();
}
//----------------
void TwinEngineTurningDrivingAxle::GoLeft(){
  is_going_forward_=true;
  this->Stop();
}
//----------------
void TwinEngineTurningDrivingAxle::GoRight(){
  is_going_forward_=true;
  this->Stop();
}
//----------------
void TwinEngineTurningDrivingAxle::GoForward(){
  is_going_forward_=true;
  this->p_motor_left_->GoForward();
  this->p_motor_right_->GoForward();
  this->SetTurn(TurnDirection::STRAIGHT);
}
//----------------
void TwinEngineTurningDrivingAxle::GoBackward(){
  is_going_forward_=false;
  this->p_motor_left_->GoBackward();
  this->p_motor_right_->GoBackward();
  this->SetTurn(TurnDirection::STRAIGHT);
}
//----------------
void TwinEngineTurningDrivingAxle::GoForwardRight(){  
  is_going_forward_=true;
  this->p_motor_left_->GoForward();
  this->p_motor_right_->GoForward();
  this->SetTurn(TurnDirection::RIGHT);
}
//----------------
void TwinEngineTurningDrivingAxle::GoForwardLeft(){
  is_going_forward_=true;
  this->p_motor_left_->GoForward();
  this->p_motor_right_->GoForward(); 
  this->SetTurn(TurnDirection::LEFT);
}
//----------------
void TwinEngineTurningDrivingAxle::GoBackwardRight(){  
  is_going_forward_=false;
  this->p_motor_left_->GoBackward();
  this->p_motor_right_->GoBackward();
  this->SetTurn(TurnDirection::RIGHT); 
}
//----------------
void TwinEngineTurningDrivingAxle::GoBackwardLeft(){
  is_going_forward_=false;
  this->p_motor_left_->GoBackward();
  this->p_motor_right_->GoBackward();  
  this->SetTurn(TurnDirection::LEFT);
}
//----------------
//----------------
//----------------
TwinEngineTankStyleTurningDrivingAxle::TwinEngineTankStyleTurningDrivingAxle(IArduinoMotor *p_motor_left,IArduinoMotor *p_motor_right): TwinEngineTurningDrivingAxle(p_motor_left, p_motor_right){
}
//----------------
void TwinEngineTankStyleTurningDrivingAxle::GoLeft(){
  is_going_forward_=true;
  this->GoLeftTankStyle();
}
//----------------
void TwinEngineTankStyleTurningDrivingAxle::GoRight(){
  is_going_forward_=true;
  this->GoRightTankStyle();
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
