#include <TimerOne.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN  49 // this is the 'minimum' pulse length count (out of 4096)  //about 49
#define SERVOMAX  409 // this is the 'maximum' pulse length count (out of 4096) //about 409


// called this way, it uses the default address 0x40
  Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(&Wire, 0x40);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!

void setup() {
  Serial.begin(9600);
  Serial.print("setupOK");
  
  Timer1.initialize(1000000); //マイクロ秒単位で設定
  Timer1.attachInterrupt(timerFire);
  
  pwm.begin();
  pwm.setPWMFreq(50);  // Analog servos run at ~60 Hz updates

  delay(1000);
}


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



double th1; //付け根
double th2; //足先
double newth1;
double newth2;
double L3;
double L3L3;
double L1 = 80;
double L2 = 105;
double L1L1 = 6400; //L1^2=80^2;
double L2L2 = 11025; //L2^2=105^2;
double L1L2 = 8400;
double L1L2_2 = 16800;
double pi = 3.14159265359; // 円周率

void TwoRink_1(float targetX, float targetY) {
  L3 = sqrt((targetX * targetX) + (targetY * targetY));
  L3L3 = L3 * L3;
  th2 = pi - acos(((L1L1) + (L2L2) - (L3L3)) / L1L2_2);
  th1 = atan2(targetY, targetX) - acos((L1L1 + L3L3 - L2L2) / (2 * L1 * L3));
}
void TwoRink_2(float targetX, float targetY) {
  L3 = sqrt((targetX * targetX) + (targetY * targetY));
  L3L3 = L3 * L3;
  th2 = pi - acos(((L1L1) + (L2L2) - (L3L3)) / L1L2_2);
  th1 = atan2(targetY, targetX) - acos((L1L1 + L3L3 - L2L2) / (2 * L1 * L3));
  newth1 =  2*acos(targetX/L3) - th1;
  newth2 = -th2;
}

float degree(double th){
  return (180*th/pi);
}
float conversion_range(float x, float in_min, float in_max, float out_min, float out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

                                           
void loop() {
  while(1){    
      TwoRink_1(-20,165);                                                               //-----MIGI_MAE-----
      pwm.setPWM(0, 0, conversion_range(degree(th2),0,180,SERVOMIN,SERVOMAX));        //saki
      pwm.setPWM(1, 0, conversion_range(degree(th1)-25,180,0,SERVOMIN,SERVOMAX));     //momo
      pwm.setPWM(2, 0, conversion_range(60,180,0,SERVOMIN,SERVOMAX));                 //Tsukene
      th1 =0;
      th2 =0;
      
      TwoRink_2(5,180);                                                              //-----MIGI_USHIRO-----
      pwm.setPWM(3, 0, conversion_range(degree(newth2)+90,0,180,SERVOMIN,SERVOMAX));  //saki
      pwm.setPWM(4, 0, conversion_range(degree(newth1)-1,180,0,SERVOMIN,SERVOMAX));   //momo
      pwm.setPWM(5, 0, conversion_range(80,180,0,SERVOMIN,SERVOMAX));                 //Tsukene
      th1 = 0;
      th2 = 0;
      newth1=0;
      newth2=0;

      TwoRink_1(-20,165);                                                               //-----HIDARI_MAE-----
      pwm.setPWM(6, 0, conversion_range(degree(th2),180,0,SERVOMIN,SERVOMAX));        //saki
      pwm.setPWM(7, 0, conversion_range(degree(th1)+5,0,180,SERVOMIN,SERVOMAX));      //momo
      pwm.setPWM(8, 0, conversion_range(100,180,0,SERVOMIN,SERVOMAX));                //Tsukene
      th1 = 0;
      th2 = 0;
      
      TwoRink_2(5,180);                                                              //-----HIDARI_USHIRO------
      pwm.setPWM(9, 0, conversion_range(degree(newth2)+90,180,0,SERVOMIN,SERVOMAX));  //saki
      pwm.setPWM(10, 0, conversion_range(degree(newth1)+25,0,180,SERVOMIN,SERVOMAX)); //momo
      pwm.setPWM(11, 0, conversion_range(75,180,0,SERVOMIN,SERVOMAX));                //Tsukene
      Serial.print(newth1);
      th1 = 0;
      th2 = 0;
      newth1=0;
      newth2=0;


  }  
}

void timerFire() {
  
  //100msec（=100000us）毎にここが呼び出される

}
