#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


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
#define SERVOMIN  49 // this is the 'minimum' pulse length count (out of 4096)  //about 49
#define SERVOMAX  409 // this is the 'maximum' pulse length count (out of 4096) //about 409


void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm.begin();
  pwm.setPWMFreq(50);  // Analog servos run at ~60 Hz updates

  delay(10);
}

// you can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. its not precise!
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





void loop() {


      pwm.setPWM(0, 0, conversion_range(25,0,180,SERVOMIN,SERVOMAX));
      pwm.setPWM(1, 0, conversion_range(65,180,0,SERVOMIN,SERVOMAX));
      pwm.setPWM(2, 0, conversion_range(120,0,180,SERVOMIN,SERVOMAX));
      
      pwm.setPWM(3, 0, conversion_range(70,0,180,SERVOMIN,SERVOMAX));
      pwm.setPWM(4, 0, conversion_range(90,0,180,SERVOMIN,SERVOMAX));
      pwm.setPWM(5, 0, conversion_range(100,0,180,SERVOMIN,SERVOMAX));

      pwm.setPWM(6, 0, conversion_range(150,0,180,SERVOMIN,SERVOMAX));
      pwm.setPWM(7, 0, conversion_range(90,0,180,SERVOMIN,SERVOMAX));
      pwm.setPWM(8, 0, conversion_range(80,0,180,SERVOMIN,SERVOMAX));
      
      pwm.setPWM(9, 0, conversion_range(130,0,180,SERVOMIN,SERVOMAX));
      pwm.setPWM(10, 0, conversion_range(115,0,180,SERVOMIN,SERVOMAX));
      pwm.setPWM(11, 0, conversion_range(105,0,180,SERVOMIN,SERVOMAX));

}
