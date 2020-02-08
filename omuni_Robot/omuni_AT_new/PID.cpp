#include "PID.h"

void PID::set_PID_constant(float kp,float ki,float kd){
  KP=&kp;
  KI=&ki;
  KD=&kd;
}

float PID::input_PID_measured_target(float measured,float target){
  i[0] = i[1];
    i[1] = measured - target ;
  integral = (integral + (i[0] + i[1]) / 2) *5 /1000;
  if(i[0]*i[1]){
    integral = 0 ;
  }
  return (*KP * i[1]) + (*KI * integral) + (*KD * (i[1] - i[0]) * 5 / 1000);
}
