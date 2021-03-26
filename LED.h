#ifndef LED_h
#define LED_h

#include <stdint.h>
#include <Arduino.h>
//----------------
class iLED{
  protected:
    uint8_t pin_=255;
  public:
    iLED() = delete;
    iLED(uint8_t new_pin);
    virtual ~iLED(){}
    
    virtual void TurnOn()=0;;
    virtual void TurnOff()=0;;
};
//----------------
class LEDDigital: public iLED{
  public:
    LEDDigital(uint8_t new_pin);
    LEDDigital() = delete;
    virtual ~LEDDigital(){}
        
    virtual void TurnOff() override;
    virtual void TurnOn() override;
};
//----------------
class LEDPWM: public iLED{
  protected:       
    uint8_t pwm_=0;
  public:
    LEDPWM(uint8_t new_pin);
    LEDPWM() = delete;
    virtual ~LEDPWM(){}

    virtual void TurnOn(uint8_t new_pwm);
    virtual void TurnOff() override;
    virtual void TurnOn() override;
    uint8_t GetPWM();
};
//----------------
class LEDAnimatedPWM: public LEDPWM{
  protected:
    double period_=3000.0;
    double coef_period_=1.0;
    double coef_offset_=1000.0;
  public:
    LEDAnimatedPWM(uint8_t new_pin);
    LEDAnimatedPWM() = delete;
    virtual ~LEDAnimatedPWM(){}
    
    void Breath(unsigned long &now);
    void SetPeriod(double new_period);
    void SetPeriod(double new_period, double new_coef_period, double new_coef_offset);
};
//----------------
class RGBLEDAnimatedPWM{
  protected:       
    LEDAnimatedPWM leds_[3];
  public:
    RGBLEDAnimatedPWM(uint8_t new_pin_r, uint8_t new_pin_g, uint8_t new_pin_b);
    RGBLEDAnimatedPWM() = delete;
    virtual ~RGBLEDAnimatedPWM(){}
    
    void Breath(unsigned long &now);
    void TurnOn();
    void TurnOff();
    void SetPeriod(double new_period);
    void SetPeriod(double new_period, double new_coef_period, double new_coef_offset);
};
//----------------
#endif
