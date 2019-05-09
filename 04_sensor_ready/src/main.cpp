#include <attiny.h>
#include "tinySPI.h"
#include "LoRaWAN.h"

//Change Keys in secconfig.h for your TTN application:
#include "secconfig.h"

ATTINY at =  ATTINY();

#include <Arduino.h>

//ir-led of proximity sensor (invisible)
#define irled 7
// power in for diode in proximity sensor
#define irdiode 3
//adc pin (connect to output of sensor)
#define irsens 2

// define a threshold for your mailbox.
#define THRESHOLD 15

// init RFM95W
#define DIO0 10
#define NSS  9
RFM95 rfm(DIO0,NSS);

LoRaWAN lora = LoRaWAN(rfm);
unsigned int Frame_Counter_Tx = 0x0000;

bool checkLetter();

void setup()
{
  at.setSleeptime(32);
  rfm.init();
  lora.setKeys(NwkSkey, AppSkey, DevAddr);
  pinMode(irled, OUTPUT);
  pinMode(irdiode, OUTPUT);
}

void loop()
{
Serial.println(at.getVoltage());

   if (at.checkAction())
  {
    uint8_t Data_Length = 0x01;
    uint8_t Data[Data_Length];

 if(checkLetter() == true ){
    Data[0] = 0xff;
  }else{
    Data[0] = 0x00;
  }

    lora.Send_Data(Data, Data_Length, Frame_Counter_Tx);
    Frame_Counter_Tx++;
  }
  at.setSleeptime(32);
  at.gotoSleep();
}

//interrupt service routine. Incrementing sleep counter
ISR(WDT_vect)
{
  at.incrCycles();
}

bool checkLetter(){
  digitalWrite(irled,HIGH);
  digitalWrite(irdiode,HIGH);
  unsigned int measure;
  for(int i = 0 ; i <3 ; i++){
    delay(5);
    measure += analogRead(irsens);
  }
  measure = measure/3;
  digitalWrite(irled,LOW);
  digitalWrite(irdiode,LOW);

  if(measure > THRESHOLD){
    return true;
  }else{
    return false;
  }
}