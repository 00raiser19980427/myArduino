#include "Arduino.h"
#include "motor.h"

void motor::MotorPin_init(byte PWM,byte DIRE){
  PwmPin = &PWM;
  DirectionPin = &DIRE;
}

void motor::SetDuty(int Duty){  
  if(Duty < 0){
    if(Duty<-255){
      Duty=-255;
      }
    digitalWrite(*DirectionPin,LOW);
    Duty = -Duty;
  }
  else{
    if(Duty>255){
      Duty=255;
      }
    digitalWrite(*DirectionPin,HIGH);
  }
  analogWrite(*PwmPin,Duty);
}
