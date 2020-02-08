#include <TimerOne.h>


typedef union {
  int val;
  byte binary[2];
} uni_num;

int t;
bool jud = false;
uni_num un;

void timerFire() {
  static int x;
  x++;
  jud = true;
  if(x > 5){
    x = 1;  
  }
  un.val = x*1000;
}

void setup() {
  Serial.begin(9600);
  Timer1.initialize(1000000); 
  Timer1.attachInterrupt(timerFire);

}


void loop() {
  if (jud){
    Serial.write(un.binary,2);
    jud = false;
  }
}
