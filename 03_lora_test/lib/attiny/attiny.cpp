#include "attiny.h"

// constructor
ATTINY::ATTINY(){
  sleepCycles = 1;
  currentCycles = sleepCycles+1;
}

void ATTINY::setSleeptime(int time){
  sleepCycles = time/8;
}

bool ATTINY::checkAction(){
  if(currentCycles >= sleepCycles){
    resetCycles();
    return true;
  }
  return false;
}

void ATTINY::resetCycles(){
    currentCycles = 0;
}

void ATTINY::incrCycles(){
  currentCycles++;
}

// all page references are for this document:
// http://ww1.microchip.com/downloads/en/devicedoc/doc8006.pdf

void ATTINY::gotoSleep(){
  
  //disable ADC
  ADCSRA &= ~(1<<ADEN);
  // WD Reset Flag to 0 (p. 45)
  bitClear(MCUSR, WDRF);
  // WD Change Enable (p. 46)
  bitSet(WDTCSR, WDCE);
  // WD Enable (p. 46)
  bitSet(WDTCSR, WDE);
  // create 8 second WD Timer Prescaler
  // 1 0 0 1 means "8 seconds" (p. 47)
  bitSet(WDTCSR, WDP3);
  bitClear(WDTCSR, WDP2);
  bitClear(WDTCSR, WDP1);
  bitSet(WDTCSR, WDP0);
  // WD Interrupt Enable (p. 45)
  bitSet(WDTCSR, WDIE);

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_mode();
  wdt_disable();
  // enable ADC again
  ADCSRA |=  (1<<ADEN);
}

//discussion here: http://forum.arduino.cc/index.php?topic=222847.0
uint16_t ATTINY::getVoltage()
{
  ADMUX = _BV(MUX5) | _BV(MUX0);
  delay(2); 
  ADCSRA |= _BV(ADSC); 
  while (bit_is_set(ADCSRA,ADSC)); 
  uint8_t low  = ADCL;
  uint8_t high = ADCH;
  uint16_t result = (high<<8) | low;
  //1125300 = 1.1 x 1023 x 1000
  result = (1125300L / result) ; 
  return result;
}