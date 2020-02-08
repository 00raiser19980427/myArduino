
//--------------------------------------------------Controller_setting_start--------------------------
#include <PS3BT.h>
#include <usbhub.h>

#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd);

//--------------------------------------------------Controller_setting_end----------------------------

//--------------------------------------------------NOGUCHI_start-----------------------------------------------------------

#define mortorA_PwmPin 5
#define mortorB_PwmPin 6
#define mortorC_PwmPin 7
#define mortorD_PwmPin 8

#define mortorA_DirectionPin 22
#define mortorB_DirectionPin 24
#define mortorC_DirectionPin 26
#define mortorD_DirectionPin 28
//--------------------------------------------------NOGUCHI_end-------------------------------------------------------------
void setup() {

//--------------------------------------------------NOGUCHI_start-----------------------------------------------------------

  TCCR3B = (TCCR3B & 0b11111000) | 0x01; //change pwm_Hz to 31.37255 [kHz] //pin5
  TCCR4B = (TCCR4B & 0b11111000) | 0x01; //change pwm_Hz to 31.37255 [kHz]//pin6,7,8

  
  pinMode(mortorA_DirectionPin, OUTPUT);
  pinMode(mortorB_DirectionPin, OUTPUT);
  pinMode(mortorC_DirectionPin, OUTPUT);
  pinMode(mortorD_DirectionPin, OUTPUT);
//--------------------------------------------------NOGUCHI_end-------------------------------------------------------------
//--------------------------------------------------Controller_setup_start--------------------------
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
//--------------------------------------------------Controller_setup_end--------------------------
}


//-------------------------------------------------------NOGUCHI_start----------------------------------------------------------------

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
  digitalWrite(mortorA_DirectionPin,HIGH);
  if(xx < 0){
    digitalWrite(mortorA_DirectionPin,LOW);
    xx = -xx;
  }
  analogWrite(mortorA_PwmPin,xx);
}
void motorB_duty(int xx){ 
  digitalWrite(mortorB_DirectionPin,LOW);
  if(xx < 0){
    digitalWrite(mortorB_DirectionPin,HIGH);
    xx = -xx;
  }
  analogWrite(mortorB_PwmPin,xx);
}

void motorC_duty(int xx){ 
  digitalWrite(mortorC_DirectionPin,HIGH);
  if(xx < 0){
    digitalWrite(mortorC_DirectionPin,LOW);
    xx = -xx;
  }
  analogWrite(mortorC_PwmPin,xx);
}

void motorD_duty(int xx){ 
  digitalWrite(mortorD_DirectionPin,HIGH);
  if(xx < 0){
    digitalWrite(mortorD_DirectionPin,LOW);
    xx = -xx;
  }
  analogWrite(mortorD_PwmPin,xx);
}


/*
void distribute_speed(float XX , float YY ,float RR){ //M1 is backside of robot...
  M1 = XX + RR;
  M2 = -(XX/2) + (sqrt(3)*YY/2) + RR;
  M3 = -(XX/2) - (sqrt(3)*YY/2) + RR;
}
*/
void distribute_speed(float XX , float YY ,float RR){  
  M1 = -XX/sqrt(2) - YY/sqrt(2) + RR;
  M2 = -XX/sqrt(2) + YY/sqrt(2) + RR;
  M3 =  XX/sqrt(2) + YY/sqrt(2) + RR; 
  M4 =  XX/sqrt(2) - YY/sqrt(2) + RR;
}

//-------------------------------------------------------NOGUCHI_end------------------------------------------------------------------


void loop() {

//-------------------------------------------------------NOGUCHI_start----------------------------------------------------------------
  Serial.println("you have to push START_button for you moving robot!!");
  while(1){
    Usb.Task();   //recieve controller signal
      if (PS3.getButtonClick(START)) {
        break;
      }
  }
  
  while(1){
  Usb.Task();     //recieve controller signal
  X_bec = PS3.getAnalogHat(LeftHatX)-127;
    if (X_bec > -30 && X_bec < 30){
        X_bec = 0;
      }
  Y_bec = PS3.getAnalogHat(LeftHatY)-127;  
    if (Y_bec > -30 && Y_bec < 30){
        Y_bec = 0;
      }
  Spin  = PS3.getAnalogButton(L2) - PS3.getAnalogButton(R2);
    if (Spin > -30 && Spin < 30){
        Spin = 0;
      }


distribute_speed ( X_bec , -Y_bec , Spin/2 );  

  
  motorA_duty(M1/2);
  motorB_duty(M2/2);
  motorC_duty(M3/2);  
  motorD_duty(M4/2);
  Serial.print(X_bec);
  Serial.print("  ");
  Serial.print(Y_bec);
  Serial.print("  ");
  Serial.println(Spin);
  }

//-------------------------------------------------------NOGUCHI_end----------------------------------------------------------------
}
