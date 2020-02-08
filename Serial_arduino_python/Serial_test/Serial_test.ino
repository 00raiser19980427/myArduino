#include <TimerOne.h>

int t;
bool jud = false;
void timerFire() {
  static int x;
  x++;
  jud = true;
  if(x > 5){
    x = 1;  
  }
  t = x;
}

void setup() {
  Serial.begin(9600);
  Timer1.initialize(1000000); 
  Timer1.attachInterrupt(timerFire);

}


void loop() {
  if (jud){
    Serial.write(t);
    jud = false;
  }
}
