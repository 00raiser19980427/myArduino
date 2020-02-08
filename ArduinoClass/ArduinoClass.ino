#include "LedController.h"

LedController ledCont1 = LedController(10);
LedController ledCont2 = LedController(13);
void setup() {

}

void loop() {
  ledCont1.on();
  ledCont2.on();
  delay(1000);
  ledCont1.off();
  ledCont2.off();
  delay(1000);
}
