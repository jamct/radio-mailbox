#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/wdt.h>

#ifndef attiny_h
#define attiny_h

class ATTINY
{
  public:
    ATTINY();
    void gotoSleep();
    void incrCycles();
    void setSleeptime(int time);
    bool checkAction();
    uint16_t getVoltage();
  private:
    void resetCycles();
    int sleepCycles;
    int currentCycles;
};

#endif
