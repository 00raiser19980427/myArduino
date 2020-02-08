#include <TimerOne.h>

void timerFire() {
  Serial.print("timerOK");
  //100ms（=100000us）毎にここが呼び出される
}

void setup() {
  Serial.begin(9600);
  Serial.print("setupOK");
  Timer1.initialize(1000000); //マイクロ秒単位で設定
  Timer1.attachInterrupt(timerFire);
}

void loop() {

}
