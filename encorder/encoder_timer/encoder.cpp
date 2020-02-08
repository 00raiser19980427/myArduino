#include "Arduino.h"
#include "encoder.h"

void encoder::EncPin(byte pinA , byte pinB){
  EncA = pinA;
  EncB = pinB;
  pinMode(EncA, INPUT_PULLUP);
  pinMode(EncB, INPUT_PULLUP);
  }

void encoder::EncCount(){
  EncState = ((EncState & B00000011) << 2) + (!digitalRead(EncB) << 1) + !digitalRead(EncA);
  switch(EncState){
      //反時計回り
      case B00000010 : 
      case B00001011 : 
      case B00001101 : 
      case B00000100 :
        Count--;  
        break;
      //時計回り
      case B00000001 : 
      case B00000111 : 
      case B00001110 : 
      case B00001000 : 
        Count++;     
        break;
    }
  }
