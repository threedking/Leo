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
bool TwoAxleSharpDriftCar::StuntControllerFB(DriveDirection new_readiness_to_stunt){ // Вперед/назад
  if(!this->IsSharpAndDriftModeOn()){
    return false;
  }
  this->is_drifting_ = false;
  if(this->readiness_to_stunt_ != new_readiness_to_stunt){ // Начинаем ехать сюда, активируем стант
    this->stunt_direction_ = TurnDirection::STRAIGHT;
    this->is_drifting_ = false;
    this->is_sharping_ = false;
    this->readiness_to_stunt_ = new_readiness_to_stunt;
  }else{ // Уже сюда ехали, переключаем трюкачество
    this->is_sharping_ = !this->is_sharping_;
  }
  return false;
}
//----------------
bool TwoAxleSharpDriftCar::StuntControllerS(){ //Стоп
  if(!this->IsSharpAndDriftModeOn()){
    return false;
  }
  this->stunt_direction_ = TurnDirection::STRAIGHT;
  this->readiness_to_stunt_ = DriveDirection::STOPPED;
  this->is_drifting_ = false;
  this->is_sharping_ = false;  
  return false;
}
//----------------
bool TwoAxleSharpDriftCar::StuntControllerLR(TurnDirection new_stunt_direction){ //Влево/Вправо
  if(!this->IsSharpAndDriftModeOn()){
    return false;
  }
  if(this->readiness_to_stunt_ == DriveDirection::STOPPED ||
  new_stunt_direction == TurnDirection::STRAIGHT){
    return false;
  }
  this->is_sharping_ = false;
  if(new_stunt_direction == this->stunt_direction_){ //Уже сюда поворачивали
    this->is_drifting_ = !this->is_drifting_;
  }else{
    this->stunt_direction_ = new_stunt_direction;
  }
  return false;
}
//----------------
bool TwoAxleSharpDriftCar::StuntControllerD(TurnDirection new_stunt_direction, DriveDirection new_readiness_to_stunt){ //По диагонали - любой газ + любой поворот
  if(!this->IsSharpAndDriftModeOn()){
    return false;
  }
  if(this->readiness_to_stunt_ == DriveDirection::STOPPED ||
  this->readiness_to_stunt_ != new_readiness_to_stunt){   // Начинаем ехать сюда, активируем стант
    this->stunt_direction_ = new_stunt_direction;
    this->is_drifting_ = false;
    this->is_sharping_ = false;
    this->readiness_to_stunt_ = new_readiness_to_stunt;      
    return false;
  }
  
  if(new_stunt_direction != TurnDirection::STRAIGHT){
    if(new_stunt_direction != this->stunt_direction_){ //Поворачивали в противоположную сторону - дрифтим
      this->is_drifting_ = true;
      this->is_sharping_ = false;
      this->stunt_direction_ = new_stunt_direction;
      this->GoSharpOrDrift(this->readiness_to_stunt_ == DriveDirection::FORWARD, this->stunt_direction_ == TurnDirection::RIGHT, !this->is_drifting_);
      return true;
    }else{ //Поворачиваели в эту же сторону
      this->is_drifting_ = false;
      if(this->is_sharping_){
        this->GoSharpOrDrift(this->readiness_to_stunt_ == DriveDirection::FORWARD, this->stunt_direction_ == TurnDirection::RIGHT, this->is_sharping_);
        return true;      
      }
    }
  }else{ //Это первый поворот сюда
      this->stunt_direction_ = new_stunt_direction;        
  }
  return false;
}
//----------------    
void TwoAxleSharpDriftCar::GoSharpOrDrift(bool is_forward, bool is_right, bool is_sharp){
  if( is_forward ? (is_sharp ? is_right : !is_right) : (is_sharp ? !is_right : is_right) ){
    this->p_axle_backward_->GoRightTankStyle();
  }else{
    this->p_axle_backward_->GoLeftTankStyle();    
  }
}
//----------------
bool TwoAxleSharpDriftCar::SwitchMode(DrivingMode mode, bool try_activate){ //Указанный режим попытаться активировать или деактивировать
  if(this->active_mode_ == (try_activate ? DrivingMode::STANDART : mode) ){ //Активировать можно только если сейчас STANDART, деактивировать только себя
      this->active_mode_ = try_activate ? mode : DrivingMode::STANDART;
      return true;
  }
  return false;
}
//----------------
void TwoAxleSharpDriftCar::ActivateSharpAndDrift(){
  if(SwitchMode(DrivingMode::SHARP_and_DRIFT, true)){
    this->stunt_direction_ = TurnDirection::STRAIGHT;
    this->readiness_to_stunt_ = DriveDirection::STOPPED;
    this->is_drifting_ = false;
    this->is_sharping_ = false;
  }
}
//----------------
void TwoAxleSharpDriftCar::DeactivateSharpAndDrift(){
  SwitchMode(DrivingMode::SHARP_and_DRIFT, false);
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
bool TwoAxleSharpDriftCar::IsSharpAndDriftModeOn(){
  return this->active_mode_ == DrivingMode::SHARP_and_DRIFT;  
}
//----------------
void TwoAxleSharpDriftCar::SetSpeedDifferenceInTurnBackAxle(int8_t new_speed_difference_in_turn){
  this->p_axle_backward_->SetSpeedDifferenceInTurn(new_speed_difference_in_turn);
}
//----------------
void TwoAxleSharpDriftCar::Stop(){
  if(!this->StuntControllerS()){
    this->p_axle_forward_->Stop();
    this->p_axle_backward_->Stop();
  }
}
//----------------
void TwoAxleSharpDriftCar::GoLeft(){
  if(!this->StuntControllerLR(TurnDirection::LEFT)){
    this->p_axle_forward_->GoLeft();
    this->p_axle_backward_->Stop();
  }
}
//----------------
void TwoAxleSharpDriftCar::GoRight(){
  if(!this->StuntControllerLR(TurnDirection::RIGHT)){
    this->p_axle_forward_->GoRight();
    this->p_axle_backward_->Stop();
  }
}
//----------------
void TwoAxleSharpDriftCar::GoForward(){
  if(!this->StuntControllerFB(DriveDirection::FORWARD)){
    this->p_axle_forward_->GoForward(); 
    this->p_axle_backward_->GoForward();
  }
}
//----------------
void TwoAxleSharpDriftCar::GoBackward(){
  if(!this->StuntControllerFB(DriveDirection::BACKWARD)){
    this->p_axle_forward_->GoBackward();
    this->p_axle_backward_->GoBackward();
  }
}
//----------------
void TwoAxleSharpDriftCar::GoForwardRight(){
  if(!this->StuntControllerD(TurnDirection::RIGHT, DriveDirection::FORWARD)){
    this->p_axle_forward_->GoForwardRight();
    this->p_axle_backward_->GoForwardRight();
  }
}
//----------------
void TwoAxleSharpDriftCar::GoForwardLeft(){
  if(!this->StuntControllerD(TurnDirection::LEFT, DriveDirection::FORWARD)){
    this->p_axle_forward_->GoForwardLeft();
    this->p_axle_backward_->GoForwardLeft();
  }
}
//----------------
void TwoAxleSharpDriftCar::GoBackwardRight(){
  if(!this->StuntControllerD(TurnDirection::RIGHT, DriveDirection::BACKWARD)){
    this->p_axle_forward_->GoBackwardRight();
    this->p_axle_backward_->GoBackwardRight();
  }
}
//----------------
void TwoAxleSharpDriftCar::GoBackwardLeft(){
  if(!this->StuntControllerD(TurnDirection::LEFT, DriveDirection::BACKWARD)){
    this->p_axle_forward_->GoBackwardLeft();
    this->p_axle_backward_->GoBackwardLeft();
  }
}
//----------------
void TwoAxleSharpDriftCar::SetSpeed(uint8_t new_speed){
  this->p_axle_forward_->SetSpeed(new_speed);
  this->p_axle_backward_->SetSpeed(new_speed);
}
//----------------
//----------------
//----------------
