/*
 * 
*   this program is for the "arduino MEGA"
*
*   "DistributeSpeed" , "Move" and "PID" classes are not library , so you can rewrite(delete) to yourselves classes !! 
*   
*   When you want to use library that includes "current robot position by encodor" , "current robot posture by gyro_sensor" and motors,
*   you have to include "tools.h" and make its instance!!
*   
*   you have to rewrite this page(omuni_AT_new).
*   Specifically , point that is writed as "change it to using yourself ..." 
*   
*   Write your code between "UserCode...start" and "UserCode...end".
*   (Debugging may not be possible when writing to other areas)
*   
*   pin_number is this page(omuni_AT_new) and "tools.h" .
*      this page   |   encoder pin
*     -------------------------------
*       tools.h    |   motor_PWM pin , motor_deriction pin
*   gyro sensor use I2C .
*   
*/

#include <TimerOne.h>
#include "Move.h"       ////change it to using yourself !!

#define timer_time 1000 //[micro sec]
#define main_time 5     // ~255msec //"main action" loop time[msec]

#define sub_action      //Define "sub_action" if you want to use sub-Code !! /
#define sub_time 100    // ~255msec

#define sub_time 100

#define PinEnc_X_A 2
#define PinEnc_X_B 3
#define PinEnc_Y_A 18
#define PinEnc_Y_B 19



Move mv;     ////change it to using yourself instance!!



volatile bool mainFlag = false;
volatile byte TimerCount = 0;


  volatile bool subFlag = false;
  volatile byte subCount = 0;


void timerFire() {
  TimerCount ++;
  subCount ++;
  if(TimerCount >= main_time){
    mainFlag = true;
    TimerCount = 0;
    }
    
  #ifdef sub_action
    if(subCount >= sub_time){
      subFlag = true;
      subCount = 0;
      }
  #endif 
  mv.tool.gy.deg_integral();     ////change it to using yourself instance!!   //essential code!!
}

void ENC_READ_X(){
  mv.tool.EncX.EncCount();       ////change it to using yourself instance!!   //essential code!!
  }
void ENC_READ_Y(){
  mv.tool.EncY.EncCount();       ////change it to using yourself instance!!   //essential code!!
  }
void setup() {
  Serial.begin(9600);
  Serial.println("Setup Start");
  
  mv.tool.gyro_motors_init();         ////change it to using yourself instance!!  //essential code!!
  
  mv.tool.EncX.EncPin(PinEnc_X_A , PinEnc_X_B);      ////change yourself using instance!!   //essential code!!
  mv.tool.EncY.EncPin(PinEnc_Y_A , PinEnc_Y_B);      ////change yourself using instance!!   //essential code!!
  
  attachInterrupt(digitalPinToInterrupt(PinEnc_X_A), ENC_READ_X, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PinEnc_X_B), ENC_READ_X, CHANGE);  
  attachInterrupt(digitalPinToInterrupt(PinEnc_Y_A), ENC_READ_Y, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PinEnc_Y_B), ENC_READ_Y, CHANGE);

  
  Timer1.initialize(timer_time); 
  Timer1.attachInterrupt(timerFire);
  
  Serial.println("SetUp_OK!!");
}

long t=0;

void loop() { 
    Serial.println("LoopStart!!");
////---------------------------------------------UserCode_init_onceTime_start-----------------------------------

      mv.XPID.set_PID_constant(1.2,0.05,0);
      mv.YPID.set_PID_constant(1.2,0.05,0);
      mv.yawPID.set_PID_constant(0.8,0.1,0);
////---------------------------------------------UserCode_init_onceTime_End-------------------------------------

  while(1){     
        
    mv.tool.gy.sampling_10();        ////change it to using yourself instance!!  //essential code!!
    
    if(mainFlag){                    //per 5("sub_time")msec count  
        
        mv.tool.nowXY_integral();    ////change it to using yourself instance!!  //essential code!!
     
////---------------------------------------------UserCode_Start-------------------------------------------------  


       mv.goposition(150*sin((float)t/70),150*cos((float)t/70)-150,0);  //not essential...deleteOK
      t++;
      
////---------------------------------------------UserCode_End---------------------------------------------------
      mainFlag = false;   
    }
    #ifdef sub_action
    if(subFlag){    //per 100("sub_time")msec count

        
  ////---------------------------------------------UserSubCode_Start------------------------------------------------ 
       
      
        Serial.print(mv.tool.rad);
        Serial.print("  ");
        Serial.print(mv.tool.nowX);
        Serial.print("  ");
        Serial.println(mv.tool.nowY);
  
        
  ////---------------------------------------------UserSubCode_End--------------------------------------------------
    subFlag = false;
   }
   #endif
  }
}
