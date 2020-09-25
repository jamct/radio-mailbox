#include <Arduino.h>

//ir-led of proximity sensor (invisible)
#define irled 7
// power in for diode in proximity sensor
#define irdiode 3
//adc pin (connect to output of sensor)
#define irsens 2

// a simple status LED
#define statusled 8

// define a threshold for your mailbox.
#define THRESHOLD 15


bool checkLetter();

void setup()
{
  pinMode(irled, OUTPUT);
  pinMode(irdiode, OUTPUT);
  pinMode(statusled, OUTPUT);
}

void loop()
{
  if(checkLetter() == true ){
    digitalWrite(statusled, HIGH);
  }else{
    digitalWrite(statusled, LOW);
  }
  delay(100);
}

bool checkLetter(){
  digitalWrite(irled,HIGH);
  digitalWrite(irdiode,HIGH);
  unsigned int measure=0;
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
