#include <Wire.h>
#include <VL53L1X.h>
 
VL53L1X sensor_1;
VL53L1X sensor_2;
VL53L1X sensor_3;
 
#define SHUT_1 6
#define SHUT_2 9
#define SHUT_3 8
 
void setup() {
Serial.begin(19200);
pinMode(13,OUTPUT);
digitalWrite(13,HIGH);
pinMode(SHUT_1, OUTPUT);
pinMode(SHUT_2, OUTPUT);
pinMode(SHUT_3, OUTPUT);
digitalWrite(SHUT_1, LOW);
digitalWrite(SHUT_2, LOW);
digitalWrite(SHUT_3, LOW);

Serial.println("PinmodeOK");
delay(100);
Wire.begin();
Serial.println("Wire.begin");

pinMode(SHUT_1, INPUT);
delay(150);
sensor_1.init();
delay(100);
sensor_1.setAddress((uint8_t)23);
sensor_1.setTimeout(500);

Serial.println("sensor1OK");
 
pinMode(SHUT_2, INPUT);
delay(150);
sensor_2.init(true);
delay(100);
sensor_2.setAddress((uint8_t)24);
sensor_2.setTimeout(500);

Serial.println("sensor2OK");
 
pinMode(SHUT_3, INPUT);
delay(150);
sensor_3.init(true);
delay(100);
sensor_3.setAddress((uint8_t)25);
sensor_3.setTimeout(500);

Serial.println("sensor3OK");
 
sensor_1.startContinuous(50);
sensor_2.startContinuous(50);
sensor_3.startContinuous(50);
digitalWrite(13,LOW);
Serial.println("SetupOK");
}
 
void loop(){
Serial.print("1,2,3...  ");
Serial.print(sensor_1.readRangeContinuousMillimeters());
Serial.print("  ");
Serial.print(sensor_2.readRangeContinuousMillimeters());
Serial.print("  ");
Serial.println(sensor_3.readRangeContinuousMillimeters());
delay(100);
}
