#include <PS3USB.h>

#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

  //-------------------------servo_setting---------------------
  #include <Wire.h>
  #include <Adafruit_PWMServoDriver.h>
  Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
  #define SERVOMIN  49 // this is the 'minimum' pulse length count (out of 4096)  //about 49
  #define SERVOMAX  409 // this is the 'maximum' pulse length count (out of 4096) //about 409

  //-----------------------------------------------------------

USB Usb;
PS3USB PS3(&Usb); // This will just create the instance


bool printAngle;
uint8_t state = 0;

void setup() {

  //--------------------------------------------------NOGUCHI_start-------------------------------------------------------------
    //-------------------------servo_setting_start----------------------
    pwm.begin();
    pwm.setPWMFreq(50);
    //-------------------------servo_setting_end----------------------
    
  pinMode(22, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(28, OUTPUT);
  //--------------------------------------------------NOGUCHI_end-------------------------------------------------------------
  
  Serial.begin(115200);
  #if !defined(__MIPSEL__)
    while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  #endif
    if (Usb.Init() == -1) {
      Serial.print(F("\r\nOSC did not start"));
      while (1); //halt
    }
  Serial.print(F("\r\nPS3 USB Library Started"));
}


//-------------------------------------------------------NOGUCHI----------------------------------------------------------------

float M1 = 0;
float M2 = 0;
float M3 = 0;
float M4 = 0;

int Left_Stick_X = 0;
int Left_Stick_Y = 0;
int Spin = 0;

float X_bec = 0;
float Y_bec = 0;

void motorA_duty(int xx){ 
  digitalWrite(22,LOW);
  if(xx < 0){
    digitalWrite(22,HIGH);
    xx = -xx;
  }
  analogWrite(3,xx);
}
void motorB_duty(int xx){ 
  digitalWrite(24,LOW);
  if(xx < 0){
    digitalWrite(24,HIGH);
    xx = -xx;
  }
  analogWrite(5,xx);
}

void motorC_duty(int xx){ 
  digitalWrite(26,LOW);
  if(xx < 0){
    digitalWrite(26,HIGH);
    xx = -xx;
  }
  analogWrite(6,xx);
}
void motorD_duty(int xx){ 
  digitalWrite(28,HIGH);
  if(xx < 0){
    digitalWrite(28,LOW);
    xx = -xx;
  }
  analogWrite(9,xx);
}

/*
void distribute_speed(float XX , float YY ,float RR){
  M1 = -XX + RR;
  M2 = (XX/2) - (sqrt(3)*YY/2) + RR;
  M3 = (XX/2) + (sqrt(3)*YY/2) + RR;
  }
*/
void distribute_speed(float XX , float YY ,float RR){  
  M1 = -XX/sqrt(2) - YY/sqrt(2) + RR ;
  M2 = -XX/sqrt(2) + YY/sqrt(2) + RR;
  M3 =  XX/sqrt(2) + YY/sqrt(2) + RR; 
  M4 =  XX/sqrt(2) - YY/sqrt(2) + RR;
  }

  
    //-------------------------------servo_setting-----------------------------------------------------------
    void setServoPulse(uint8_t n, double pulse) {
    double pulselength;  
      pulselength = 1000000;   // 1,000,000 us per second
      pulselength /= 50;   // 50 Hz
      Serial.print(pulselength); Serial.println(" us per period"); 
      pulselength /= 4096;  // 12 bits of resolution
      Serial.print(pulselength); Serial.println(" us per bit"); 
      pulse *= 1000000;  // convert to us
      pulse /= pulselength;
      Serial.println(pulse);\
      pwm.setPWM(n, 0, pulse);
    }
    float conversion_range(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }
    //-------------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------------------------------------------------------

void loop() {
  Usb.Task();
  //-------------------------servo_setting-------------------------------------
  pwm.setPWM(0, 0, conversion_range(25,0,180,SERVOMIN,SERVOMAX));
  //---------------------------------------------------------------------------

  //--------------------------------NOGUCHI----------------------------------------------------------------------

  X_bec = PS3.getAnalogHat(LeftHatX)-127;
    if (X_bec > -20 && X_bec < 20){
        X_bec = 0;
      }
  Y_bec = PS3.getAnalogHat(LeftHatY)-127;  
    if (Y_bec > -20 && Y_bec < 20){
        Y_bec = 0;
      }
  Spin  = PS3.getAnalogButton(L2) - PS3.getAnalogButton(R2);
    if (Spin > -20 && Spin < 20){
        Spin = 0;
      }
  
  
  distribute_speed ( X_bec/2 , -Y_bec/2 , Spin/5 );  
  motorA_duty(M1);
  motorB_duty(M2);
  motorC_duty(M3);
  motorD_duty(M4);
  Serial.println(M1);
  //---------------------------------------------------------------------------------------------------------------
}
