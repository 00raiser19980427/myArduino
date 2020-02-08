#include <Wire.h>
#include <VL53L1X.h>
 
VL53L1X sensor;
 
#define SHUT 6

void setup() {
Serial.begin(19200);
pinMode(13,OUTPUT);
digitalWrite(13,HIGH);
pinMode(SHUT, OUTPUT);

digitalWrite(SHUT, LOW);

Serial.println("PinmodeOK");
delay(100);
Wire.begin();
Serial.println("Wire.begin");

pinMode(SHUT, INPUT);
delay(150);
sensor.init();
delay(100);
sensor.setAddress((uint8_t)23);
sensor.setTimeout(100);

Serial.println("sensorOK");
 
sensor.startContinuous(50);

digitalWrite(13,LOW);
Serial.println("SetupOK");
}
 
void loop(){
Serial.println(sensor.readRangeContinuousMillimeters());
delay(10);
}
