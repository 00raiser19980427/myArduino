#include <TimerOne.h>
#include "encoder.h"

#define PinEnc_A 2  //エンコーダのA相のピン番号
#define PinEnc_B 3  //エンコーダのB相のピン番

#define timer_action 1000 //timerの実行周期を指定

encoder Enc0;  //encoderクラスのインスタンスを生成

bool mainFlag = false;       // mainのif文で判断、volatile型で定義...割り込み関数内で使用するため
volatile byte TimerCount = 0; // timer内で加算、volatile型で定義...割り込み関数内で使用するため

void timerFire() {
  TimerCount ++;
  if(TimerCount >= 10){
    mainFlag = true;
    TimerCount = 0;
    }
}

void ENC_READ(){
  Enc0.EncCount();
  }

void setup() {
  Serial.begin(9600);
  Serial.println("Setup Start");
  Enc0.EncPin(PinEnc_A , PinEnc_B);
  attachInterrupt(digitalPinToInterrupt(PinEnc_A), ENC_READ, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PinEnc_B), ENC_READ, CHANGE);
  Timer1.initialize(timer_action); 
  Timer1.attachInterrupt(timerFire);
  Serial.println("Setup OK!!");
}

void loop() {
  while(1){
    if(mainFlag){
    Serial.println(Enc0.Count);
    mainFlag = false;
    }
  }
}
