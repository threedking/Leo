#ifndef Axle_h
#define Axle_h

#include "ArduinoMotor.h"

#include <Servo.h>

#include <stdint.h>
#include <Arduino.h>
//----------------
enum class TurnDirection : uint8_t{
  LEFT,
  STRAIGHT,
  RIGHT
};
//----------------
enum class DriveDirection : uint8_t{
  STOPPED,
  FORWARD,
  BACKWARD
};
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
  public:
    TwinEngineDrivingAxle(IArduinoMotor *p_motor_left,IArduinoMotor *p_motor_right);
    virtual ~TwinEngineDrivingAxle();
    
    virtual void GoLeftTankStyle();
    virtual void GoRightTankStyle();
    
    virtual void Stop() override;
    virtual void GoLeft() override;
    virtual void GoRight() override;
    virtual void GoForward() override;
    virtual void GoBackward() override;
    virtual void GoForwardRight() override;
    virtual void GoForwardLeft() override;
    virtual void GoBackwardRight() override;
    virtual void GoBackwardLeft() override;
    virtual void SetSpeed(uint8_t new_speed) override;
};
//----------------
class TwinEngineTurningDrivingAxle: public TwinEngineDrivingAxle{ //Поворачивает разницей в скоростей колес. На GoLeft GoRight стоит.
  protected:   
    int8_t speed_difference_in_turn_=25;//Процент(-100 - 100) отношения скорости внутреннего колеса к внешнему в повороте. Если <0, то направление противоположное    
    bool is_going_forward_=true;//Запоминаем направление оси для отрицательной разницы скорости в повороте
    
    TurnDirection turn_= TurnDirection::STRAIGHT; // Если не прямо, то скорость колес разная (speed_difference_in_turn_)    

    void SetTurn(TurnDirection new_turn);
  public:
    TwinEngineTurningDrivingAxle(IArduinoMotor *p_motor_left,IArduinoMotor *p_motor_right);
    virtual ~TwinEngineTurningDrivingAxle(){}
        
    void SetSpeedDifferenceInTurn(int8_t new_speed_difference_in_turn);

    virtual void GoLeftTankStyle() override;
    virtual void GoRightTankStyle() override;
    
    virtual void Stop() override;
    virtual void GoLeft() override;
    virtual void GoRight() override;
    virtual void GoForward() override;
    virtual void GoBackward() override;
    virtual void GoForwardRight() override;
    virtual void GoForwardLeft() override;
    virtual void GoBackwardRight() override;
    virtual void GoBackwardLeft() override;
    virtual void SetSpeed(uint8_t new_speed) override;
};
//----------------
class TwinEngineTankStyleTurningDrivingAxle: public TwinEngineTurningDrivingAxle{ //На GoLeft GoRight работает как танк
  protected:   
  public:
    TwinEngineTankStyleTurningDrivingAxle(IArduinoMotor *p_motor_left,IArduinoMotor *p_motor_right);
    virtual ~TwinEngineTankStyleTurningDrivingAxle(){}
    
    virtual void GoLeft() override;
    virtual void GoRight() override;
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

    virtual void Stop() override;
    virtual void GoLeft() override;
    virtual void GoRight() override;
    virtual void GoForward() override;
    virtual void GoBackward() override;
    virtual void GoForwardRight() override;
    virtual void GoForwardLeft() override;
    virtual void GoBackwardRight() override;
    virtual void GoBackwardLeft() override;
    virtual void SetSpeed(uint8_t new_speed) override;

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
