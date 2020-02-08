#include <TimerOne.h>
#include <Wire.h>

#define timer_time 1000 //call "timerFire()" per 1ms（=1000micro_sec)
#define HyoujunHensa_Baisu 2

long GyroX = 0 , GyroY = 0 , GyroZ = 0;

long dataZ_ave = 0 ;
long dataZ_HyoujunHensa = 0 ;

long degZ_10_re=0;
float gy_z=0;

long timer_count = 0;

void timerFire() {  
  timer_count++;
  deg_integral();
  if(timer_count >= 100){
  Serial.println(gy_z);
  timer_count = 0;
  }
}

void setup() {
  Serial.begin(9600);
  Wire.begin(); //start i2c
  setupMPU6050();
  sensor_Pre();
  
  Timer1.initialize(timer_time); //setting at micro_second(1sec=1000mmsec=1000000microsec)
  Timer1.attachInterrupt(timerFire);
  
  Serial.print("OK_setup\n\r");
  delay(1000);
}

void setupMPU6050() {
  //MPU6050 contact start!! ,and decide max&min of the gyro&accel sensor 
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x6B); //Accessing the register 6B
  Wire.write(0b00000000); //SLEEP register to 0
  Wire.endTransmission();
  Wire.beginTransmission(0b1101000);
  Wire.write(0x1B); //Accessing the register 1B - Gyroscope Configuration
  Wire.write(0x00000000); //gyro to full scale ± 250deg./s
  Wire.endTransmission();
  Wire.beginTransmission(0b1101000);
  Wire.write(0x1C); //Accessing the register 1C - Acccelerometer Configuration
  Wire.write(0b00000000); //accel to +/- 2g
}

void gy_read_st(){
  //read gyro sensor
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x43); //Starting register for Gyro Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000, 6); //Request Gyro Registers (43 - 48)
  while (Wire.available() < 6);
  GyroX = Wire.read() << 8 | Wire.read(); //Store first two bytes into accelX
  GyroY = Wire.read() << 8 | Wire.read(); //Store middle two bytes into accelY
  GyroZ = Wire.read() << 8 | Wire.read(); //Store last two bytes into accelZ
}

void sensor_Pre(){
      Serial.print("Please wait about 10 sec\n\r");
      gy_read_st();
      delay(1000);
      long dataZ[100] ;
      long dataZ_sum=0 ;
      long dataZ_bunsan=0 ; 
      for(int i=0;i<100;i++){
          gy_read_st();
          dataZ[i] = GyroZ;
          dataZ_sum += GyroZ ;
          delay(100);
      }
      dataZ_ave = dataZ_sum / 100 ;
      
      for(int i=0;i<100;i++){
          dataZ_bunsan += (dataZ[i] - dataZ_ave) * (dataZ[i] - dataZ_ave);
      }
      dataZ_HyoujunHensa = sqrt(dataZ_bunsan/100) * HyoujunHensa_Baisu;
}


void deg_integral(){
  gy_z += (float)degZ_10_re / timer_time;
}


void deg_now_10(){    
  long degZ_now[10];
  long degZ_now_abs[10];
  long degZ_sum = 0;
  long degZ_ave = 0;
  long degZ_use = 0;
  int n_z=0;
  int jud_z = 0;
  
  for(int i=0; i<10;i++){
    gy_read_st();
    degZ_now[i] = GyroZ - dataZ_ave;
    degZ_now_abs[i] = abs(GyroZ - dataZ_ave);
    degZ_sum += degZ_now[i];
    }
    degZ_ave = degZ_sum/10;
  for(int t=0; t<10 ;t++){
    jud_z = abs(degZ_ave) - dataZ_HyoujunHensa;
    if(degZ_now_abs[t]>jud_z){
        degZ_use += degZ_now[t];
        n_z++;
    }     
  }

  degZ_10_re = degZ_use/(n_z*131.00); //131+- parameter
}

void loop() {
  while(1){
  gy_read_st();
  deg_now_10();
  }
}
