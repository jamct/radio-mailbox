/*
  RFM95.h - Library header file for RFM95 LoRa module.
  Created by Leo Korbee, March 31, 2018.
  Released into the public domain.
  @license Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
  Thanks to all the folks who contributed beforme me on this code.

*/

#ifndef RFM95_h
#define RMF95_h

#include "Arduino.h"

class RFM95
{
  public:
    RFM95(int DIO0, int NSS);
    void init();
    void RFM_Write(unsigned char RFM_Address, unsigned char RFM_Data);
    unsigned char RFM_Read(unsigned char RFM_Address);
    void RFM_Send_Package(unsigned char *RFM_Tx_Package, unsigned char Package_Length);
  private:
    int _DIO0;
    int _NSS;
};


#endif
