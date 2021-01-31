#include "Car.h"
//----------------
OneAxleCar::OneAxleCar(IAxle *p_axle):p_axle_(p_axle){
}
//----------------
void OneAxleCar::Stop(){
  this->p_axle_->Stop();
}
//----------------
void OneAxleCar::GoLeft(){
  this->p_axle_->GoLeft();
}
//----------------
void OneAxleCar::GoRight(){
  this->p_axle_->GoRight();
}
//----------------
void OneAxleCar::GoForward(){
  this->p_axle_->GoForward();
}
//----------------
void OneAxleCar::GoBackward(){
  this->p_axle_->GoBackward();
}
//----------------
void OneAxleCar::GoForwardRight(){
  this->p_axle_->GoForwardRight();
}
//----------------
void OneAxleCar::GoForwardLeft(){
  this->p_axle_->GoForwardLeft();
}
//----------------
void OneAxleCar::GoBackwardRight(){
  this->p_axle_->GoBackwardRight();
}
//----------------
void OneAxleCar::GoBackwardLeft(){
  this->p_axle_->GoBackwardLeft();
}
//----------------
void OneAxleCar::SetSpeed(uint8_t new_speed){
  this->p_axle_->SetSpeed(new_speed);
}
//----------------
//----------------
//----------------
TwoAxleCar::TwoAxleCar(IAxle *p_axle_forward, IAxle *p_axle_backward):p_axle_forward_(p_axle_forward),p_axle_backward_(p_axle_backward){
}
//----------------
void TwoAxleCar::Stop(){
  this->p_axle_forward_->Stop();
  this->p_axle_backward_->Stop();
}
//----------------
void TwoAxleCar::GoLeft(){
  this->p_axle_forward_->GoLeft();
  this->p_axle_backward_->GoLeft();
}
//----------------
void TwoAxleCar::GoRight(){
  this->p_axle_forward_->GoRight();
  this->p_axle_backward_->GoRight();
}
//----------------
void TwoAxleCar::GoForward(){
  this->p_axle_forward_->GoForward();
  this->p_axle_backward_->GoForward();
}
//----------------
void TwoAxleCar::GoBackward(){
  this->p_axle_forward_->GoBackward();
  this->p_axle_backward_->GoBackward();
}
//----------------
void TwoAxleCar::GoForwardRight(){
  this->p_axle_forward_->GoForwardRight();
  this->p_axle_backward_->GoForwardRight();
}
//----------------
void TwoAxleCar::GoForwardLeft(){
  this->p_axle_forward_->GoForwardLeft();
  this->p_axle_backward_->GoForwardLeft();
}
//----------------
void TwoAxleCar::GoBackwardRight(){
  this->p_axle_forward_->GoBackwardRight();
  this->p_axle_backward_->GoBackwardRight();
}
//----------------
void TwoAxleCar::GoBackwardLeft(){
  this->p_axle_forward_->GoBackwardLeft();
  this->p_axle_backward_->GoBackwardLeft();
}
//----------------
void TwoAxleCar::SetSpeed(uint8_t new_speed){
  this->p_axle_forward_->SetSpeed(new_speed);
  this->p_axle_backward_->SetSpeed(new_speed);
}
//----------------
//----------------
//----------------
TwoAxleSharpDriftCar::TwoAxleSharpDriftCar(IAxle *p_axle_forward, TwinEngineDrivingAxle *p_axle_backward):p_axle_forward_(p_axle_forward),p_axle_backward_(p_axle_backward){
}
//----------------
void TwoAxleSharpDriftCar::SwitchMode(DrivingMode mode, bool try_activate){ //Указанный режим попытаться активировать или деактивировать
  if(this->active_mode_ == (try_activate ? DrivingMode::STANDART : mode) ){ //Активировать можно только если сейчас STANDART, деактивировать только себя
      this->active_mode_ = try_activate ? mode : DrivingMode::STANDART;
  }
}
//----------------
void TwoAxleSharpDriftCar::ActivateDrift(){
  SwitchMode(DrivingMode::DRIFT, true);
}
//----------------
void TwoAxleSharpDriftCar::DeactivateDrift(){
  SwitchMode(DrivingMode::DRIFT, false);
}
//----------------
void TwoAxleSharpDriftCar::ActivateSharp(){
  SwitchMode(DrivingMode::SHARP, true);  
}
//----------------
void TwoAxleSharpDriftCar::DeactivateSharp(){
  SwitchMode(DrivingMode::SHARP, false);  
}
//----------------
bool TwoAxleSharpDriftCar::IsDriftModeOn(){
  return this->active_mode_ == DrivingMode::DRIFT;
}
//----------------
bool TwoAxleSharpDriftCar::IsSharpModeOn(){
  return this->active_mode_ == DrivingMode::SHARP;  
}
//----------------
void TwoAxleSharpDriftCar::SetSpeedDifferenceInTurnBackAxle(int8_t new_speed_difference_in_turn){
  this->p_axle_backward_->SetSpeedDifferenceInTurn(new_speed_difference_in_turn);
}
//----------------
void TwoAxleSharpDriftCar::Stop(){
  this->p_axle_forward_->Stop();
  this->p_axle_backward_->Stop();
}
//----------------
void TwoAxleSharpDriftCar::GoLeft(){
  this->p_axle_forward_->GoLeft();
  this->p_axle_backward_->Stop();
}
//----------------
void TwoAxleSharpDriftCar::GoRight(){
  this->p_axle_forward_->GoRight();
  this->p_axle_backward_->Stop();
}
//----------------
void TwoAxleSharpDriftCar::GoForward(){
  this->p_axle_forward_->GoForward();
  this->p_axle_backward_->GoForward();
}
//----------------
void TwoAxleSharpDriftCar::GoBackward(){
  this->p_axle_forward_->GoBackward();
  this->p_axle_backward_->GoBackward();
}
//----------------
void TwoAxleSharpDriftCar::GoForwardRight(){
  this->p_axle_forward_->GoForwardRight();
  this->p_axle_backward_->GoForwardRight();
}
//----------------
void TwoAxleSharpDriftCar::GoForwardLeft(){
  this->p_axle_forward_->GoForwardLeft();
  this->p_axle_backward_->GoForwardLeft();
}
//----------------
void TwoAxleSharpDriftCar::GoBackwardRight(){
  this->p_axle_forward_->GoBackwardRight();
  this->p_axle_backward_->GoBackwardRight();
}
//----------------
void TwoAxleSharpDriftCar::GoBackwardLeft(){
  this->p_axle_forward_->GoBackwardLeft();
  this->p_axle_backward_->GoBackwardLeft();
}
//----------------
void TwoAxleSharpDriftCar::SetSpeed(uint8_t new_speed){
  this->p_axle_forward_->SetSpeed(new_speed);
  this->p_axle_backward_->SetSpeed(new_speed);
}
//----------------
//----------------
//----------------
