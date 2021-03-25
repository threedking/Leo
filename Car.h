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
    TwinEngineTurningDrivingAxle *p_axle_backward_=NULL;
    
    enum class DrivingMode : uint8_t{ 
      STANDART,         //Без трюков
      SHARP,            //Усиленные повороты, резкие развороты
      DRIFT,            //Дрифт
      SHARP_and_DRIFT
    };

    DrivingMode active_mode_ = DrivingMode::STANDART;

    TurnDirection stunt_direction_ = TurnDirection::STRAIGHT; //Помнить последнее направление для совершения правильного трюка
    DriveDirection readiness_to_stunt_ = DriveDirection::STOPPED; //Если стоппед, то не стантим, иначе готовы стантить в направлении движения
    bool is_sharping_ = false, is_drifting_ = false; //Трюкачим ли сейчас()


    bool StuntControllerFB(DriveDirection new_readiness_to_stunt); // Вперед/назад
    bool StuntControllerS(); //Стоп
    bool StuntControllerLR(TurnDirection new_stunt_direction); //Влево/Вправо
    bool StuntControllerD(TurnDirection new_stunt_direction, DriveDirection new_readiness_to_stunt); //По диагонали - любой газ + любой поворот
    
    /*    
    КАК было:
    Если хотим повернуть влево, то
      Если сейчас не повернуты влево(а прямо или вправо >30), то
        Дрифтить или резко развернуться

    Условие прекращение дрифта - отпустить газ или повернуть руль

    КАК будет:

    Один метод будет вызываться во всех публичных методах управления и вызывать нужное.
    Он будет проверять режим вождения и от этого запускать нужное поведение. Нет. Он будет вызывать метод по указателю.

    Нужны методы реального поведения. Но не для всех: стоп, назад и вперед будут выполнять свои задачи, щелкая состояние
    Нужны методы дрифта в стороны и резких поворотов в стороны - хватит одного

    Вариант для резкого ИЛИ дрифтового режима:
    Если была нажата команда вперед
      Если была нажата команда вперед и в сторону      
      Пока не была нажата команда стоп

    Вариант для резкого И дрифтового режима:     
      Есть bool is_sharping, is_drifting
      
      Если была нажата команда вперед, то is_sharping = is_drifting = false
      Если 
      
    
    */

    bool SwitchMode(DrivingMode mode, bool try_activate);//Указанный режим попытаться активировать или деактивировать, вернет успех
    void GoSharpOrDrift(bool is_forward, bool is_right, bool is_sharp);
    
  public:
    TwoAxleSharpDriftCar(IAxle *p_axle_forward, TwinEngineDrivingAxle *p_axle_backward);
    virtual ~TwoAxleSharpDriftCar(){}
    
    void ActivateDrift();
    void DeactivateDrift();
    void ActivateSharp();
    void DeactivateSharp();
    void ActivateSharpAndDrift();
    void DeactivateSharpAndDrift();
    
    bool IsDriftModeOn();
    bool IsSharpModeOn();
    bool IsSharpAndDriftModeOn();

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
