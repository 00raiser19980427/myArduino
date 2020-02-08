#include <Wire.h>
long accelX, accelY, accelZ;
double gForceX, gForceY, gForceZ;

long gyroX, gyroY, gyroZ;

long dataX_ave , dataY_ave , dataZ_ave ;
long dataX_HyoujunHensa , dataY_HyoujunHensa , dataZ_HyoujunHensa ;



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
  Serial.print(angleX());
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
void gy_read_st(){        //recordGyroRegisters() couse of bug
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
      long dataX_sum=0    ,dataY_sum=0    ,dataZ_sum=0 ;
      long dataX_bunsan=0 ,dataY_bunsan=0 ,dataZ_bunsan=0 ; 
      for(int i=1;i<=100;i++){
          gy_read_st();
          dataX[i]=gyroX;
          dataY[i]=gyroY;
          dataZ[i]=gyroZ;
          delay(10);
      }
      for(int i=1;i<=100;i++){
          dataX_sum += dataX[i];
          dataY_sum += dataY[i];
          dataZ_sum += dataZ[i];
      }
      
      dataX_ave = dataX_sum / 100 ;
      dataY_ave = dataY_sum / 100 ;
      dataZ_ave = dataZ_sum / 100 ;
      
      for(int i=1;i<=100;i++){
          dataX_bunsan += (dataX[i] - dataX_ave) * (dataX[i] - dataX_ave);
          dataY_bunsan += (dataY[i] - dataY_ave) * (dataY[i] - dataY_ave);
          dataZ_bunsan += (dataZ[i] - dataZ_ave) * (dataZ[i] - dataZ_ave);
      }
      dataX_HyoujunHensa = sqrt(dataX_bunsan/100)*2;
      dataY_HyoujunHensa = sqrt(dataY_bunsan/100)*2;
      dataZ_HyoujunHensa = sqrt(dataZ_bunsan/100)*2;
      
      Serial.print("dataX_sum=");
      Serial.print(dataX_sum);
      Serial.print("\n\r");
      Serial.print("dataX_ave=");
      Serial.print(dataX_ave);
      Serial.print("\n\r");
      Serial.print("dataX_HyoujunHensa=");
      Serial.print(dataX_HyoujunHensa);
      Serial.print("\n\r");
  }

float degX_new = 0;
float angleX(){
  float degX_pre = degX_new;
  degX_new = degX_now_10()/100;
  if(abs(degX_new-degX_pre)<=0.01){
  return degX_pre;
    }
  else {
    degX_new += degX_pre;
    return degX_new;
  } 
}
float degX_now_10(){
  long degX_now[10];
  long degX_now_abs[10];
  long degX_sum = 0;
  long degX_ave = 0;
  long degX_use = 0;
  int n=0;
  int jud = 0;
  for(int i=0; i<=9;i++){
    gy_read_st();
    degX_now[i] = gyroX - dataX_ave;
    degX_now_abs[i] = abs(gyroX - dataX_ave);
    degX_sum += degX_now[i];
    }
    degX_ave = degX_sum/10;
  for(int t=0; t<=9 ;t++){
      jud = abs(degX_ave) - dataX_HyoujunHensa*2;
      if(degX_now_abs[t]>jud){
        degX_use += degX_now[t];
        n++;
        }    
  }
  return float(degX_use)/(float(n)*97.55);
}



  
