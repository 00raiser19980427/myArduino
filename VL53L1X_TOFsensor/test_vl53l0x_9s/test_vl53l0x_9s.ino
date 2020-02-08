#include <Wire.h>
#include <VL53L1X.h>
 
VL53L1X sensor_1;
VL53L1X sensor_2;
VL53L1X sensor_3;
VL53L1X sensor_4;
VL53L1X sensor_5;
VL53L1X sensor_6;
VL53L1X sensor_7;
VL53L1X sensor_8;
VL53L1X sensor_9;
 
#define SHUT_1 10
#define SHUT_2 2
#define SHUT_3 3
#define SHUT_4 4
#define SHUT_5 5
#define SHUT_6 6
#define SHUT_7 7
#define SHUT_8 8
#define SHUT_9 9
 
void setup() {
Serial.begin(19200);
pinMode(13,OUTPUT);
digitalWrite(13,HIGH);
pinMode(SHUT_1, OUTPUT);
pinMode(SHUT_2, OUTPUT);
pinMode(SHUT_3, OUTPUT);
pinMode(SHUT_4, OUTPUT);
pinMode(SHUT_5, OUTPUT);
pinMode(SHUT_6, OUTPUT);
pinMode(SHUT_7, OUTPUT);
pinMode(SHUT_8, OUTPUT);
pinMode(SHUT_9, OUTPUT);
digitalWrite(SHUT_1, LOW);
digitalWrite(SHUT_2, LOW);
digitalWrite(SHUT_3, LOW);
digitalWrite(SHUT_4, LOW);
digitalWrite(SHUT_5, LOW);
digitalWrite(SHUT_6, LOW);
digitalWrite(SHUT_7, LOW);
digitalWrite(SHUT_8, LOW);
digitalWrite(SHUT_9, LOW);

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
Serial.println("sensor 1 OK");
 
pinMode(SHUT_2, INPUT);
delay(150);
sensor_2.init(true);
delay(100);
sensor_2.setAddress((uint8_t)24);
sensor_2.setTimeout(500);
Serial.println("sensor 2 OK");
 
pinMode(SHUT_3, INPUT);
delay(150);
sensor_3.init(true);
delay(100);
sensor_3.setAddress((uint8_t)25);
sensor_3.setTimeout(500);
Serial.println("sensor 3 OK");

pinMode(SHUT_4, INPUT);
delay(150);
sensor_4.init(true);
delay(100);
sensor_4.setAddress((uint8_t)26);
sensor_4.setTimeout(500);
Serial.println("sensor 4 OK");

pinMode(SHUT_5, INPUT);
delay(150);
sensor_5.init(true);
delay(100);
sensor_5.setAddress((uint8_t)27);
sensor_5.setTimeout(500);
Serial.println("sensor 5 OK");

pinMode(SHUT_6, INPUT);
delay(150);
sensor_6.init(true);
delay(100);
sensor_6.setAddress((uint8_t)28);
sensor_6.setTimeout(500);
Serial.println("sensor 6 OK");

pinMode(SHUT_7, INPUT);
delay(150);
sensor_7.init(true);
delay(100);
sensor_7.setAddress((uint8_t)29);
sensor_7.setTimeout(500);
Serial.println("sensor 7 OK");

pinMode(SHUT_8, INPUT);
delay(150);
sensor_8.init(true);
delay(100);
sensor_8.setAddress((uint8_t)30);
sensor_8.setTimeout(500);
Serial.println("sensor 8 OK");

pinMode(SHUT_9, INPUT);
delay(150);
sensor_9.init(true);
delay(100);
sensor_9.setAddress((uint8_t)31);
sensor_9.setTimeout(500);
Serial.println("sensor 9 OK");
 
sensor_1.startContinuous(50);
sensor_2.startContinuous(50);
sensor_3.startContinuous(50);
sensor_4.startContinuous(50);
sensor_5.startContinuous(50);
sensor_6.startContinuous(50);
sensor_7.startContinuous(50);
sensor_8.startContinuous(50);
sensor_9.startContinuous(50);
digitalWrite(13,LOW);
Serial.println("SetupOK");
}
 
void loop(){
Serial.print("1,2,3...  ");
Serial.print(sensor_1.readRangeContinuousMillimeters());
Serial.print("  ");
Serial.print(sensor_2.readRangeContinuousMillimeters());
Serial.print("  ");
Serial.print(sensor_3.readRangeContinuousMillimeters());
Serial.print("  ");
Serial.print(sensor_4.readRangeContinuousMillimeters());
Serial.print("  ");
Serial.print(sensor_5.readRangeContinuousMillimeters());
Serial.print("  ");
Serial.print(sensor_6.readRangeContinuousMillimeters());
Serial.print("  ");
Serial.print(sensor_7.readRangeContinuousMillimeters());
Serial.print("  ");
Serial.print(sensor_8.readRangeContinuousMillimeters());
Serial.print("  ");
Serial.println(sensor_9.readRangeContinuousMillimeters());
delay(100);
}
