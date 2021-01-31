#ifndef Car_h
#define Car_h

#include "Axle.h"

#include <stdint.h>
#include <Arduino.h>
//----------------
class ICar{
  public:
    ICar(){}
    virtual ~ICar(){}

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
class OneAxleCar: public ICar{
  protected:    
    IAxle *p_axle_=NULL;
  public:  
    OneAxleCar(IAxle *p_axle);
    virtual ~OneAxleCar(){}
    
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
};
//----------------
class TwoAxleCar: public ICar{
  protected:
    IAxle *p_axle_forward_=NULL;
    IAxle *p_axle_backward_=NULL;
  public:
    TwoAxleCar(IAxle *p_axle_forward, IAxle *p_axle_backward);
    virtual ~TwoAxleCar(){}
    
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
};
//----------------
class TwoAxleSharpDriftCar: public ICar{
  protected:
    IAxle *p_axle_forward_=NULL;
    TwinEngineDrivingAxle *p_axle_backward_=NULL;
    
    enum class DrivingMode : uint8_t{
      STANDART,
      SHARP,
      DRIFT
    };

    DrivingMode active_mode_ = DrivingMode::STANDART;

    /*
    Если хотим повернуть влево, то
      Если сейчас не повернуты влево(а прямо или вправо >30), то
        Дрифтить или резко развернуться

    Условие прекращение дрифта - отпустить газ или повернуть руль
    */

    void SwitchMode(DrivingMode mode, bool try_activate);//Указанный режим попытаться активировать или деактивировать    
  public:
    TwoAxleSharpDriftCar(IAxle *p_axle_forward, TwinEngineDrivingAxle *p_axle_backward);
    virtual ~TwoAxleSharpDriftCar(){}
    
    void ActivateDrift();
    void DeactivateDrift();
    void ActivateSharp();
    void DeactivateSharp();
    
    bool IsDriftModeOn();
    bool IsSharpModeOn();

    void SetSpeedDifferenceInTurnBackAxle(int8_t new_speed_difference_in_turn);
    
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
};
//----------------
#endif
