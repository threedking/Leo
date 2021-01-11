#ifndef ArduinoMotor_h
#define ArduinoMotor_h

#include <stdint.h>
#include <Arduino.h>
//----------------
class IArduinoMotor{//Абстрактный в качестве интерфейса
  public:
    IArduinoMotor(){}
    virtual ~IArduinoMotor(){}
    virtual void SetSpeed(uint8_t speed)=0;
    virtual void SetDirection(bool forward, bool backward)=0;
    void GoForward();
    void GoBackward();
    void Stop();
};
//----------------
class ArduinoMotor3Pins: public IArduinoMotor{
  protected:
    uint8_t pin_forward_=255;//255 - неправильно или не задан
    uint8_t pin_backward_=255;//255 - неправильно или не задан
    uint8_t pin_speed_=255;//255 - неправильно или не задан
  
    ArduinoMotor3Pins(){}
    
  public:
    ArduinoMotor3Pins(uint8_t new_pin_forward,uint8_t new_pin_backward,uint8_t new_pin_speed);
    virtual ~ArduinoMotor3Pins(){}
  
    void SetSpeed(uint8_t speed) override;
    void SetDirection(bool forward, bool backward) override;
};
//----------------
class ArduinoMotor2Pins: public IArduinoMotor{
  protected:
    uint8_t pin_forward_=255;//255 - неправильно или не задан
    uint8_t pin_backward_=255;//255 - неправильно или не задан
    uint8_t speed_=0;
    bool direction_forward_=false;
    bool direction_backward_=false;
  
    ArduinoMotor2Pins(){}  
  
    void ApplyEngineParameters();
      
  public:  
    ArduinoMotor2Pins(uint8_t new_pin_forward,uint8_t new_pin_backward);
    virtual ~ArduinoMotor2Pins(){}
  
    void SetSpeed(uint8_t speed) override;
    void SetDirection(bool forward, bool backward) override;
};
//----------------
#endif
