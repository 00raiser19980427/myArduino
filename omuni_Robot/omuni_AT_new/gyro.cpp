#include "Arduino.h"
#include "gyro.h"
#include <Wire.h>

void gyro::setupMPU6050() {
  //MPU6050 contact start!! ,and decide max&min of the gyro&accel sensor 
  Wire.begin();
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
  Serial.println("MPU6050 OK!!");
}

void gyro::sensor_read(){
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x43); //Starting register for Gyro Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000, 6); //Request Gyro Registers (43 - 48)
  while (Wire.available() < 6);
  GyroX = Wire.read() << 8 | Wire.read(); //Store first two bytes into accelX
  GyroY = Wire.read() << 8 | Wire.read(); //Store middle two bytes into accelY
  GyroZ = Wire.read() << 8 | Wire.read(); //Store last two bytes into accelZ
}

void gyro::sensor_init(){
      Serial.print("Please wait about 10 sec\n\r");
      sensor_read();
      delay(1000);
      sum_sensInit = 0;
      bunsan_sensInit = 0;
      for(int i=0;i<100;i++){
          sensor_read();
          Data_s_sensInit[i] = GyroZ;
          sum_sensInit += GyroZ ;
          delay(100);
      }
      ave_sensInit = sum_sensInit / 100 ;
      
      for(int i=0;i<100;i++){
          bunsan_sensInit += (Data_s_sensInit[i] - ave_sensInit) * (Data_s_sensInit[i] - ave_sensInit);
      }
      HyoujunHensa_sensInit = sqrt(bunsan_sensInit/100) * HyoujunHensa_Baisu;
      Serial.println("sensor_init OK!!");
}

volatile void gyro::deg_integral(){
  degZ += (float)sampling_10_re / 1000;
}

void gyro::sampling_10(){    
  sum_samp = 0;
  ave_samp = 0;
  use_sampSum = 0;
  namber_of_use=0;
  jud_samp = 0;
  for(i_sump=0; i_sump<10; i_sump++){
    sensor_read();
    samp_s[i_sump] = GyroZ - ave_sensInit;
    abs_samp_s[i_sump] = abs(GyroZ - ave_sensInit);
    sum_samp += samp_s[i_sump];
    }
    ave_samp = sum_samp/10;
  for(t_sump=0; t_sump<10 ;t_sump++){
    jud_samp = abs(ave_samp) - HyoujunHensa_sensInit;
    if(abs_samp_s[t_sump]>jud_samp){
        use_sampSum += samp_s[t_sump];
        namber_of_use++;
    }     
  }

  sampling_10_re = use_sampSum/(namber_of_use*131.00); //131+- parameter
}
