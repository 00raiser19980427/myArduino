#include <DueTimer.h>

#define ENC_A 2
#define ENC_B 3
#define timer_action 1000


//#define KP 300
//#define KI 10
//#define KD 0
#define KP 80
#define KI 1200
#define KD 0.003



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
  if(velocity >= 0){
    if(velocity - velocity_pre > 1){
      velocity = velocity_pre;
      velocity_pre = velocity_pre  +  1;
    }
  }
  else{
    if(velocity_pre - velocity > 1){
      velocity = velocity_pre;
      velocity_pre = velocity_pre  -  1;
    }
  }
  return velocity;
}


void loop() {
  while(1){
    motor(PID_output);
    if(mainflag){
     mainflag = false;
     Serial.println(v_print);
    }
    if(PIDflag){
     PIDflag = false;
     PID(v_print , inputMotor(-10));
    } 
  }
}
 
