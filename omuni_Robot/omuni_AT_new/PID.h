#ifndef PID_H_
#define PID_H_

class PID
{
  private:
  float *KP;  //const
  float *KI;  //const
  float *KD;  //const
  float i[2];      
  float integral;  


  public:
  PID(void){
    integral = 0;
  }
    void set_PID_constant(float kp,float ki,float kd);
  float input_PID_measured_target(float,float);  //now,target
  float ad;
};

#endif /* PID_H_ */
