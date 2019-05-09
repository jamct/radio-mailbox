#include <attiny.h>
#include "tinySPI.h"
#include "LoRaWAN.h"

//Change Keys in secconfig.h for your TTN application:
#include "secconfig.h"

ATTINY at =  ATTINY();

// init RFM95W
#define DIO0 10
#define NSS  9
RFM95 rfm(DIO0,NSS);

LoRaWAN lora = LoRaWAN(rfm);
unsigned int Frame_Counter_Tx = 0x0000;

void setup()
{
  at.setSleeptime(32);
  rfm.init();
  lora.setKeys(NwkSkey, AppSkey, DevAddr);
}

void loop()
{
Serial.println(at.getVoltage());

   if (at.checkAction())
  {
    uint8_t Data_Length = 0x02;
    uint8_t Data[Data_Length];

    // measure voltage and send via LoRaWAN (2 byte)
    uint16_t vcc = at.getVoltage();
    Data[0] = (vcc >> 8) & 0xff;
    Data[1] = (vcc & 0xff);

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
