#include <DueTimer.h>

#define ENC_A 2
#define ENC_B 3

#define timer_action 1000 //1msec

int pos;
volatile int v_print; 
volatile int EncCount = 0;
volatile int timerCount = 0;
volatile bool mainflag = false;

void timerFire() {   
  timerCount ++ ;
  if(timerCount>=10){
    mainflag = true;
    timerCount = 0;
    v_print = EncCount; 
    }
   
  EncCount = 0;
}

void ENC_READ() {  
  pos = ((pos & B00000011) << 2) + (!digitalRead(ENC_B) << 1) + !digitalRead(ENC_A);
  switch(pos){
      //反時計回り
      case B00000010 : 
      case B00001011 : 
      case B00001101 : 
      case B00000100 :
        EncCount--;    
        break;
      //時計回り
      case B00000001 : 
      case B00000111 : 
      case B00001110 : 
      case B00001000 : 
        EncCount++;   
        break;
    }
}

void setup() {
  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);
 
  attachInterrupt(digitalPinToInterrupt(ENC_A), ENC_READ, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_B), ENC_READ, CHANGE);

  Timer3.attachInterrupt(timerFire);
  Timer3.start(1000);
  Serial.println("Setup OK!!");
 
  Serial.begin(250000);
}
 
 
void loop() {
  
  if(mainflag){
    mainflag = false;
   Serial.println(v_print);
    }
    
  }
 
