#ifndef Axle_h
#define Axle_h

#include "ArduinoMotor.h"

#include <Servo.h>

#include <stdint.h>
#include <Arduino.h>
//----------------
class IAxle{
  public:
    IAxle(){}
    virtual ~IAxle(){}
    
    virtual void Stop()=0;
    virtual void GoLeft()=0;
    virtual void GoRight()=0;
    virtual void GoForward()=0;
    virtual void GoBackward()=0;
    virtual void GoForwardRight()=0;
    virtual void GoForwardLeft()=0;
    virtual void GoBackwardRight()=0;
    virtual void GoBackwardLeft()=0;
    virtual void SetSpeed(uint8_t new_speed)=0;
};
//----------------
class TwinEngineDrivingAxle: public IAxle{  
  protected:
    IArduinoMotor *p_motor_left_=NULL;
    IArduinoMotor *p_motor_right_=NULL;    

    uint8_t speed_=255;
    int8_t speed_difference_in_turn_=25;//Процент(-100 - 100) отношения скорости внутреннего колеса к внешнему в повороте. Если <0, то направление противоположное
    int8_t turn_=0;// -1 - влево, 0 - прямо, 1 - вправо. Если не прямо, то скорость колес разная (speed_difference_in_turn_)    
    bool is_going_forward_=true;//Запоминаем направление оси для отрицательной разницы скорости в повороте

    void SetTurn(int8_t new_turn);
  public:
    TwinEngineDrivingAxle(IArduinoMotor *p_motor_left,IArduinoMotor *p_motor_right);
    virtual ~TwinEngineDrivingAxle();
    
    void SetSpeed(uint8_t new_speed) override;
    void SetSpeedDifferenceInTurn(int8_t new_speed_difference_in_turn);

    void GoLeftTankStyle();
    void GoRightTankStyle();
    
    void Stop() override;
    void GoLeft() override;
    void GoRight() override;
    void GoForward() override;
    void GoBackward() override;
    void GoForwardRight() override;
    void GoForwardLeft() override;
    void GoBackwardRight() override;
    void GoBackwardLeft() override;
};
//----------------
class ServoSteeringAxle: public IAxle{
  protected:
    uint8_t pin_steering_servo_=255;//255 - неправильно или не задан
    int16_t angle_=0, min_angle_=0, max_angle_=360, mid_angle_=180;

    Servo servo_;

    void SetAngleAndApply(int16_t new_angle);
    void ApplyTurn();
  public:
    ServoSteeringAxle(uint8_t new_pin_steering_servo, int16_t new_min_angle, int16_t new_max_angle);
    virtual ~ServoSteeringAxle();

    void Stop() override;
    void GoLeft() override;
    void GoRight() override;
    void GoForward() override;
    void GoBackward() override;
    void GoForwardRight() override;
    void GoForwardLeft() override;
    void GoBackwardRight() override;
    void GoBackwardLeft() override;
    void SetSpeed(uint8_t new_speed) override;

    void TurnStraight();
    void TurnMaxLeft();
    void TurnMaxRight();
    void AddDegreesToTheRight(uint8_t degrees_right);
    void AddDegreesToTheLeft(uint8_t degrees_left);
    void TurnPercentLeft(uint8_t percent_left);
    void TurnPercentRight(uint8_t percent_right);
};
//----------------
#endif
