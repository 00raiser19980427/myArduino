
#ifndef DISTRIBUTE_SPEED_H_
#define DISTRIBUTE_SPEED_H_

#include "math.h"

class DistributeSpeed {
private:
    const double myPI=3.14159265358979323846264338;
    const double RR = 170;

  public:
    float V1;
    float V2;
    float V3;
    float V4;

    void output4(float PID_x,float PID_y,float PID_yaw,float now_yaw){
      V1 =-PID_x*sin(PI*1/4+now_yaw) +PID_y * cos(PI*1/4+now_yaw)+ 0.365*PID_yaw;
      V2 = PID_x*cos(PI*1/4+now_yaw) +PID_y * sin(PI*1/4+now_yaw)+ 0.365*PID_yaw;
      V3 = PID_x*sin(PI*1/4+now_yaw) -PID_y * cos(PI*1/4+now_yaw)+ 0.365*PID_yaw;
      V4 =-PID_x*cos(PI*1/4+now_yaw) -PID_y * sin(PI*1/4+now_yaw)+ 0.365*PID_yaw;
    }
    void output3(float PID_x,float PID_y,float PID_yaw,float now_yaw){
      V1 =   PID_x*cos(now_yaw)             + PID_y*sin(now_yaw)              + RR*PID_yaw;
      V2 =   PID_x*cos(now_yaw + 2*myPI/3)  + PID_y*sin(now_yaw + 2*myPI/3)   + RR*PID_yaw;
      V3 = - PID_x*cos(now_yaw + myPI/3)    - PID_y*sin(now_yaw + myPI/3)     + RR*PID_yaw;
    }
};

#endif /* DISTRIBUTE_SPEED_H_ */
