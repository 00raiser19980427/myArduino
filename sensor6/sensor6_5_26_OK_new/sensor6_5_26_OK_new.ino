#include <Wire.h>
long accelX, accelY, accelZ;
double gForceX, gForceY, gForceZ;

long gyroX, gyroY, gyroZ;

long dataX_ave , dataY_ave , dataZ_ave ;
long dataX_HyoujunHensa , dataY_HyoujunHensa , dataZ_HyoujunHensa ;

float degX_new=0,degY_new=0,degZ_new=0;
float degX_10_re=0,degY_10_re=0,degZ_10_re=0;
float gy_x=0,gy_y=0,gy_z=0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  setupMPU6050();
  recordGyroRegisters();
  sensor_Pre();
  Serial.print("OK_setup\n\r");
  delay(1000);
}

void loop() {
  while(1){
  recordGyroRegisters();
  recordAccelRegisters();
  angle();
  Serial.print(gy_x);
  Serial.print("   ");
  Serial.print(gy_y);
  Serial.print("   ");
  Serial.print(gy_z);
  Serial.print("\n\r");
  delay(1);
  }
}


void setupMPU6050() {
  //MPU6050との通信を開始し、ジャイロと加速度の最大範囲を指定
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
  Wire.endTransmission();
}
 
void recordAccelRegisters() {
  //加速度読み取り
  Wire.beginTransmission(0b1101000);
  Wire.write(0x3B); // Accel Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000, 6); //Request Accel Registers (3B - 40)
  while (Wire.available() < 6);
  accelX = Wire.read() << 8 | Wire.read(); //Store first two bytes into accelX
  accelY = Wire.read() << 8 | Wire.read(); //Store middle two bytes into accelY
  accelZ = Wire.read() << 8 | Wire.read(); //Store last two bytes into accelZ
  gForceX = accelX / 16384.0; //change to deg/sec
  gForceY = accelY / 16384.0;
  gForceZ = accelZ / 16384.0;
}



void recordGyroRegisters() {
  //ジャイロの値を読み取る
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x43); //Starting register for Gyro Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000, 6); //Request Gyro Registers (43 - 48)
  while (Wire.available() < 6);
  gyroX = Wire.read() << 8 | Wire.read(); //Store first two bytes into accelX
  gyroY = Wire.read() << 8 | Wire.read(); //Store middle two bytes into accelY
  gyroZ = Wire.read() << 8 | Wire.read(); //Store last two bytes into accelZ
  
}
void gy_read_st(){ //recordGyroRegisters() couse of bug
  recordGyroRegisters(); 
  }
/*
void calculateGyroData() {
  //読み取った値をdeg/secに変換
  rotX = gyroX / 174.666;
  rotY = gyroY / 131.0;
  rotZ = gyroZ / 131.0;
}
*/
void sensor_Pre(){
      
      long dataX[100]   ,dataY[100]   ,dataZ[100] ;
      long  dataX_sum=0    ,dataY_sum=0    ,dataZ_sum=0 ;
      long dataX_bunsan=0 ,dataY_bunsan=0 ,dataZ_bunsan=0 ; 
      for(int i=0;i<=99;i++){
          gy_read_st();
          dataX[i]=gyroX;
          dataY[i]=gyroY;
          dataZ[i]=gyroZ;
      }
      for(int i=0;i<=99;i++){
          dataX_sum += dataX[i];
          dataY_sum += dataY[i];
          dataZ_sum += dataZ[i];
      }
      
      dataX_ave = dataX_sum / 100 ;
      dataY_ave = dataY_sum / 100 ;
      dataZ_ave = dataZ_sum / 100 ;
      
      for(int i=0;i<=99;i++){
          dataX_bunsan += (dataX[i] - dataX_ave) * (dataX[i] - dataX_ave);
          dataY_bunsan += (dataY[i] - dataY_ave) * (dataY[i] - dataY_ave);
          dataZ_bunsan += (dataZ[i] - dataZ_ave) * (dataZ[i] - dataZ_ave);
      }
      dataX_HyoujunHensa = sqrt(dataX_bunsan/100)*2;
      dataY_HyoujunHensa = sqrt(dataY_bunsan/100)*2;
      dataZ_HyoujunHensa = sqrt(dataZ_bunsan/100)*2;
      
  }


void angle(){
  deg_now_10();
  float degX_pre = degX_new;
  float degY_pre = degY_new;
  float degZ_pre = degZ_new;  
  degX_new = degX_10_re/100;
  degY_new = degY_10_re/100;
  degZ_new = degZ_10_re/100;
  
  if(abs(degX_new-degX_pre)<=0.01){
        gy_x = degX_pre;
      }
      else {
        degX_new += degX_pre;
        gy_x = degX_new;
      } 
  if(abs(degY_new-degY_pre)<=0.01){
        gy_y = degY_pre;
      }
      else {
        degY_new += degY_pre;
        gy_y = degY_new;
      } 
  if(abs(degZ_new-degZ_pre)<=0.01){
        gy_z = degZ_pre;
       }
      else {
        degZ_new += degZ_pre;
        gy_z = degZ_new;
      } 
}
void deg_now_10(){
  long degX_now[10];
  long degX_now_abs[10];
  long degX_sum = 0;
  long degX_ave = 0;
  long degX_use = 0;

  long degY_now[10];
  long degY_now_abs[10];
  long degY_sum = 0;
  long degY_ave = 0;
  long degY_use = 0;

  long degZ_now[10];
  long degZ_now_abs[10];
  long degZ_sum = 0;
  long degZ_ave = 0;
  long degZ_use = 0;
  
  int n_x=0;
  int n_y=0;
  int n_z=0;
  int jud_x = 0;
  int jud_y = 0;
  int jud_z = 0;
  
  for(int i=0; i<=9;i++){
    gy_read_st();
    degX_now[i] = gyroX - dataX_ave;
    degY_now[i] = gyroY - dataY_ave;
    degZ_now[i] = gyroZ - dataZ_ave;
    degX_now_abs[i] = abs(gyroX - dataX_ave);
    degY_now_abs[i] = abs(gyroY - dataY_ave);
    degZ_now_abs[i] = abs(gyroZ - dataZ_ave);
    degX_sum += degX_now[i];
    degY_sum += degY_now[i];
    degZ_sum += degZ_now[i];
    }
    degX_ave = degX_sum/10;
    degY_ave = degY_sum/10;
    degZ_ave = degZ_sum/10;
  for(int t=0; t<=9 ;t++){
      jud_x = abs(degX_ave) - dataX_HyoujunHensa;
      jud_y = abs(degY_ave) - dataY_HyoujunHensa;
      jud_z = abs(degZ_ave) - dataZ_HyoujunHensa;
      if(degX_now_abs[t]>jud_x){
        degX_use += degX_now[t];
        n_x++;
        } 
      if(degY_now_abs[t]>jud_y){
        degY_use += degY_now[t];
        n_y++;
        }  
      if(degZ_now_abs[t]>jud_z){
        degZ_use += degZ_now[t];
        n_z++;
        }     
  }
  degX_10_re = float(degX_use)/(float(n_x)*55.00);
  degY_10_re = float(degY_use)/(float(n_y)*55.00);
  degZ_10_re = float(degZ_use)/(float(n_z)*55.00);

}



  
