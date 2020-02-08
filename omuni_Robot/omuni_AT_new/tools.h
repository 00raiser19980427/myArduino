#ifndef TOOLS_H_
#define TOOLS_H_

#include "motor.h"
#include "encoder.h"
#include "gyro.h"

#define motor1_PwmPin 4
#define motor2_PwmPin 5
#define motor3_PwmPin 6
#define motor4_PwmPin 7
#define motor1_DirectionPin 22
#define motor2_DirectionPin 24
#define motor3_DirectionPin 26
#define motor4_DirectionPin 28

class tools {
  public:
    motor M1;
    motor M2;
    motor M3;
    motor M4;
    encoder EncX;
    encoder EncY;
    void nowXY_integral();
    double nowX;
    double nowY;
    double rad;
    gyro gy;
    void gyro_motors_init();


  private:
    
    const double EncPerimeter = 157.0796;//[mm]
    const double EncPulse = 2000;


    
};

#endif
