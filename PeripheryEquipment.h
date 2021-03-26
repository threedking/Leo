#ifndef PeripheryEquipment_h
#define PeripheryEquipment_h

#include <stdint.h>
#include <Arduino.h>
//----------------
class UltraSonicSensor{
  protected:
    uint8_t pin_trig_=255;//255 - неправильно или не задан
    uint8_t pin_echo_=255;//255 - неправильно или не задан
  public:
    UltraSonicSensor() = delete;
    UltraSonicSensor(uint8_t new_pin_trig, uint8_t new_pin_echo);
    virtual ~UltraSonicSensor(){}
    int GetDistanceCM();
};
//----------------
class DigitalSensor{
  protected:
    uint8_t pin_=255;//255 - неправильно или не задан
  public:
    DigitalSensor() = delete;
    DigitalSensor(uint8_t new_pin);
    virtual ~DigitalSensor(){}
    bool GetState();
};
//----------------
#endif
