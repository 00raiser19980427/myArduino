#include "Arduino.h"
#include "tools.h"
  

void tools::nowXY_integral(){
  rad = (double)gy.degZ*3.1415926535/180;
  nowX += -((double)EncX.Count*cos(rad) - (double)EncY.Count*sin(rad)) * EncPerimeter / EncPulse ;
  nowY += -((double)EncX.Count*sin(rad) + (double)EncY.Count*cos(rad)) * EncPerimeter / EncPulse ;
  EncX.Count = 0;  
  EncY.Count = 0;  
  }


void tools::gyro_motors_init(){
  gy.setupMPU6050();
  gy.sensor_read();
  gy.sensor_init();
  
  pinMode(motor1_PwmPin , OUTPUT);
  pinMode(motor2_PwmPin , OUTPUT);
  pinMode(motor3_PwmPin , OUTPUT);
  pinMode(motor4_PwmPin , OUTPUT);

  pinMode(motor1_DirectionPin , OUTPUT);
  pinMode(motor2_DirectionPin , OUTPUT);
  pinMode(motor3_DirectionPin , OUTPUT);
  pinMode(motor4_DirectionPin , OUTPUT);

  M1.MotorPin_init(motor1_PwmPin , motor1_DirectionPin);
  M2.MotorPin_init(motor2_PwmPin , motor2_DirectionPin);
  M3.MotorPin_init(motor3_PwmPin , motor3_DirectionPin);
  M4.MotorPin_init(motor4_PwmPin , motor4_DirectionPin);
}
