#include <Arduino.h>
#include <SoftwareSerial.h>

/*
* Example with serial output for debugging
* Connect Arduino Pins 1 and 2 to USB-Serial-Converter
*/

SoftwareSerial Serial(1, 2);

//ir-led of proximity sensor (invisible)
#define irled 9
// power in for diode in proximity sensor
#define irdiode 8
//adc pin (connect to output of sensor)
#define irsens 7

// a simple status LED
#define statusled 5

// define a threshold for your mailbox.
#define THRESHOLD 15

bool checkLetter();

void setup()
{
  pinMode(irled, OUTPUT);
  pinMode(irdiode, OUTPUT);
  pinMode(statusled, OUTPUT);
  Serial.begin(9600);
  Serial.println("Connection ready...");
}

void loop()
{
  if(checkLetter() == true ){
    digitalWrite(statusled, HIGH);
    Serial.println("1");
  }else{
    digitalWrite(statusled, LOW);
    Serial.println("0");
  }
  delay(100);
}

bool checkLetter(){
  digitalWrite(irled,HIGH);
  digitalWrite(irdiode,HIGH);
  unsigned int measure = 0;
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
