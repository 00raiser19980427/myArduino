#ifndef MOVE_H_
#define MOVE_H_

#include "DistributeSpeed.h"
#include "PID.h"
#include "tools.h"


class Move{

public:
  tools tool;
  PID XPID;
  PID YPID;
  PID yawPID;
  DistributeSpeed dist;
  float now_x;
  float now_y;
  float now_yaw;


  void goposition(float target_x,float target_y,float target_yaw){
    now_x = tool.nowX;
    now_y = tool.nowY;
    now_yaw = tool.rad;
    
    dist.output3( XPID.input_PID_measured_target(now_x,target_x)  ,  YPID.input_PID_measured_target(now_y,target_y)  ,  yawPID.input_PID_measured_target(now_yaw,target_yaw)  ,  now_yaw);
    tool.M1.SetDuty(dist.V1);
    tool.M2.SetDuty(dist.V2);
    tool.M3.SetDuty(dist.V3);
  }
};

#endif /* TEST_MOVE_H_ */
