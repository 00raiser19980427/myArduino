#include <Wire.h>
#include <VL53L1X.h>
 
VL53L1X sensor_A;
VL53L1X sensor_B1;
VL53L1X sensor_B2;


#define SHUT_A  2
#define SHUT_B1 3
#define SHUT_B2 4

 
void setup() {
Serial.begin(38400);
pinMode(13,OUTPUT);
digitalWrite(13,HIGH);
pinMode(SHUT_A, OUTPUT);
pinMode(SHUT_B1, OUTPUT);
pinMode(SHUT_B2, OUTPUT);

digitalWrite(SHUT_A, LOW);
digitalWrite(SHUT_B1, LOW);
digitalWrite(SHUT_B2, LOW);

Serial.println("PinmodeOK");
delay(100);
Wire.begin();
Serial.println("Wire.begin");

pinMode(SHUT_A, INPUT);
delay(150);
sensor_A.init();
delay(100);
sensor_A.setAddress((uint8_t)23);
sensor_A.setTimeout(500);
Serial.println("sensor_A OK");
 
pinMode(SHUT_B1, INPUT);
delay(150);
sensor_B1.init(true);
delay(100);
sensor_B1.setAddress((uint8_t)24);
sensor_B1.setTimeout(500);
Serial.println("sensor_B1 OK");
 
pinMode(SHUT_B2, INPUT);
delay(150);
sensor_B2.init(true);
delay(100);
sensor_B2.setAddress((uint8_t)25);
sensor_B2.setTimeout(500);
Serial.println("sensor_B2 OK");


sensor_A.startContinuous(50);
sensor_B1.startContinuous(50);
sensor_B2.startContinuous(50);

digitalWrite(13,LOW);
Serial.println("SetupOK");
}

float XX;
float YY;
float rad;

float s_B1;
float s_B2;
 
void loop(){
  s_B1 =  sensor_B1.readRangeContinuousMillimeters();
  s_B2 =  sensor_B2.readRangeContinuousMillimeters();
  XX = (s_B1 + s_B2)/2 ;
  YY = sensor_A.readRangeContinuousMillimeters();
  rad = atan((s_B1 - s_B2)/153)*180/3.1455926535;

Serial.print("X,Y,rad...  ");
Serial.print(XX);
Serial.print("  ");
Serial.print(YY);
Serial.print("  ");
Serial.println(rad);

  
 /*
Serial.print("1,2,3...  ");
Serial.print(sensor_A.readRangeContinuousMillimeters());
Serial.print("  ");
Serial.print(sensor_B1.readRangeContinuousMillimeters());
Serial.print("  ");
Serial.println(sensor_B2.readRangeContinuousMillimeters());
*/
delay(100);
}
