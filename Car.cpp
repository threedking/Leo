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
