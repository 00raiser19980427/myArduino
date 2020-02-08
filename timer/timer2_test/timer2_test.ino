#include <MsTimer2.h>

void timerFire() {
  Serial.print("timer");
  //100ms毎にここが呼び出される
}

void setup() {
  Serial.begin(9600);
  Serial.print("setupOK");
   //100ms毎にtimer
  MsTimer2::set(1000, timerFire);
  MsTimer2::start();
}

void loop() {

}
