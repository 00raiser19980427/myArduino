#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver PWM = Adafruit_PWMServoDriver();
#define SERVOMIN  49 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  409 // this is the 'maximum' pulse length count (out of 4096)
uint8_t servonum = 0;

void setup() {
  Serial.begin(9600);
  PWM.begin();
  PWM.setPWMFreq(50);  // 50Hz

}
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  PWM.setPWM(n, 0, pulse);

}

float th1; //付け根
float th2; //足先
float L3;
float L3L3;
float L1 = 80;
float L2 = 105;
float L1L1 = 6400; //L1^2=80^2;
float L2L2 = 11025; //L2^2=105^2;
float L1L2 = 8400;
float L1L2_2 = 16800;
float pi = 3.14159265359; // 円周率

void TwoRink(float targetX, float targetY) {
  L3 = sqrt((targetX * targetX) + (targetY * targetY));
  L3L3 = L3 * L3;
  th2 = pi - acos(((L1L1) + (L2L2) - (L3L3)) / L1L2_2);
  th1 = atan2(targetY, -targetX) - acos((L1L1 + L3L3 - L2L2) / (2 * L1 * L3));
}

float conversion_range(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float foot_rootX;
float foot_rootY;
int num = 1;
float n;

void loop() {
while(1){
  switch (num) {
    case 1:
      foot_rootY = 165;
      while (foot_rootX < 50) {
        TwoRink(foot_rootX, foot_rootY);
        float n1 = (th1 * 180 / pi) + 15;
        float n2 = (th2 * 180 / pi) - 15;

        Serial.print(th1);

        PWM.setPWM(0, 0, conversion_range(n1, 0, 180, SERVOMIN, SERVOMAX));
        PWM.setPWM(1, 0, conversion_range(n2, 180, 0, SERVOMIN, SERVOMAX));

        foot_rootX++;
        delay(5);
      }
      foot_rootX = 50;
      num = 2;
      break;
    case 2:
      while (foot_rootX <= 50, foot_rootX > 0) {
        foot_rootY = 165 + n * 2 / 5;
        TwoRink(foot_rootX, foot_rootY);
        float n1 = (th1 * 180 / pi) + 15;
        float n2 = (th2 * 180 / pi) - 15;

        PWM.setPWM(0, 0, conversion_range(n1, 0, 180, SERVOMIN, SERVOMAX));
        PWM.setPWM(1, 0, conversion_range(n2, 180, 0, SERVOMIN, SERVOMAX));
        
        foot_rootX--;
        n--;
        delay(5);
      }
      foot_rootX = 0;
      num = 3;
      break;
    case 3:
      while (foot_rootX <= 0, foot_rootX > -50) {
        foot_rootY = 165 + n * 2 / 5;
        TwoRink(foot_rootX, foot_rootY);
        float n1 = (th1 * 180 / pi) + 15;
        float n2 = (th2 * 180 / pi) - 15;

        PWM.setPWM(0, 0, conversion_range(n1, 0, 180, SERVOMIN, SERVOMAX));
        PWM.setPWM(1, 0, conversion_range(n2, 180, 0, SERVOMIN, SERVOMAX));
        
        foot_rootX--;
        n++;
        delay(5);
      }
      foot_rootX = -50;
      num = 1;
      break;

  }
}
}
