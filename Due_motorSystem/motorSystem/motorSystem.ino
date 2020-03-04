#include <DueTimer.h>

#define ENC_A 2
#define ENC_B 3
#define timer_action 1000

#define KP 80
#define KI 1200
#define KD 0.003

#define accSafety 2 //1~2 safe , 2.5~ Danger

#define gearRatio 4.333333333333333 // 13:3
#define encPulse 500 
#define pi 3.141592653589793238
//double changeToAngV  = (gearRatio * encPulse )/(pi*500) ; // (gearRatio * encPulse * 4 )/(2*pi*1000)
double changeToAngV = 5.517371360519038 ;

int pos;
volatile int v_print; 
volatile int EncCount = 0;
volatile int timerCount = 0;
volatile bool mainflag = false;
volatile bool PIDflag = false;

void timerFire() {   
  timerCount ++ ;
  if(timerCount>=5){
    mainflag = true;
    v_print = EncCount; 
    timerCount = 0;
    }
  EncCount = 0;
  PIDflag = true;
}

void ENC_READ() {  
  pos = ((pos & B00000011) << 2) + (!digitalRead(ENC_B) << 1) + !digitalRead(ENC_A);
  switch(pos){
      //反時計回り
      case B00000010 : 
      case B00001011 : 
      case B00001101 : 
      case B00000100 :
        EncCount--;    
        break;
      //時計回り
      case B00000001 : 
      case B00000111 : 
      case B00001110 : 
      case B00001000 : 
        EncCount++;   
        break;
    }
}

void setup() {
  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);
 
  attachInterrupt(digitalPinToInterrupt(ENC_A), ENC_READ, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_B), ENC_READ, CHANGE);

  Timer3.attachInterrupt(timerFire);
  Timer3.start(1000);
  

  pinMode(11,OUTPUT);//ボード内側のpwmピン
  pinMode(12,OUTPUT);//ボード外側のpwmピン
  analogWriteResolution(11);
  analogWriteResolution(12);
 
  Serial.begin(250000);
  Serial.println("Setup OK!!");
}


void motor(int xx){ 
  if(xx >= 0){
  analogWrite(11,xx);
  analogWrite(12,0);
  }
  if(xx < 0){
  xx = -xx;
  analogWrite(11,0);
  analogWrite(12,xx);
  }
}




float i[2];
float integral;
float PID_output = 0;


float PID(float measured,float target){
  i[0] = i[1];
  i[1] = target - measured ;
  if(i[0]*i[1]>0){
    integral = integral + (i[1] + i[0]) / 2 * 0.001;//0.001は制御周期dt
  } 
  PID_output = KP * i[1] + KI * integral - KD * (i[1] - i[0]) / 0.001;
  return PID_output;
}


float velocity_pre = 0;

float inputMotor( float velocity){
  velocity = velocity * (float)changeToAngV;
  if(velocity >= 0){
    if(velocity - velocity_pre > accSafety){
      velocity = velocity_pre;
      velocity_pre = velocity_pre  +  accSafety;
    }
  }
  else{
    if(velocity_pre - velocity > accSafety){
      velocity = velocity_pre;
      velocity_pre = velocity_pre  -  accSafety;
    }
  }
  return velocity;
}


void loop() {
  while(1){
    motor(PID_output);
    if(mainflag){
     mainflag = false;
     Serial.println(v_print / (float)changeToAngV);
    }
    if(PIDflag){
     PIDflag = false;
     PID(v_print , inputMotor(10));   // [rad/s]
    } 
  }
}
 
