#include <DueTimer.h>

int myLed = 13;

bool ledOn = false;
void myHandler(){
  ledOn = !ledOn;

  digitalWrite(myLed, ledOn); // Led on, off, on, off...
}

void setup(){
  pinMode(myLed, OUTPUT);

  Timer3.attachInterrupt(myHandler);
  Timer3.start(1000000); // Calls every 1000ms = 1000000μsec
}

void loop(){
  while(1){
  }
}
