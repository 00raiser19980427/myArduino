#include <TimerOne.h>
#include <Wire.h>
long accelX, accelY, accelZ;
long time_timer = 0;


long accX_ave = 0 , accY_ave = 0 ;
double accX = 0 , accY = 0 , accZ = 0;



void timerFire() {
  time_timer++;
  if(time_timer==100){
  Serial.print(accX);
  Serial.print("    ");
  Serial.print(accY);
  Serial.print("    ");
  Serial.print(accZ);
  Serial.print("\n\r");
  //call per 1000ms（=1000000micro_sec)
  time_timer=0;
  }  
}

void setup() {
  Wire.begin(); //start i2c
  setupMPU6050();
  acc_read_st();
  
  Serial.begin(9600);
  Serial.print("Please wait about 10 sec");
  Serial.print("\n\r");
  acc_init();

  Timer1.initialize(1000); //setting at micro_second(1sec=1000mmsec=1000000microsec)
  Timer1.attachInterrupt(timerFire);
   
  Serial.print("OK_setup\n\r");
  delay(1000);
}


void loop() {
  while(1){
      acc_read_st();
      accel_use();
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
}

void acc_read_st(){
  recordAccelRegisters();
}

void acc_init(){
  long accX_sum = 0 , accY_sum = 0;
  for(int i=0;i<100;i++){
   acc_read_st();
   accX_sum += accelX; 
   accY_sum += accelY; 
   delay(100); 
    }
  accX_ave = accX_sum / 100;
  accY_ave = accY_sum / 100;
}

void accel_use(){
  long accX_sump = 0 , accY_sump = 0 , accZ_sump = 0;
  for(int i=0;i<10;i++){
    acc_read_st();
    accX_sump += accelX;
    accY_sump += accelY;
    accZ_sump += accelZ;
    }
  accX = double(accX_sump/10 - accX_ave)/16350; // 0 to 1(=9.8m/s^2) //about 16384  [16350] is parameter
  accY = double(accY_sump/10 - accY_ave)/16425; // 0 to 1(=9.8m/s^2) //about 16384  [16425] is parameter
  accZ = double(accZ_sump/10 - 2600)/16800;     // 0 to 1(=9.8m/s^2) //about 16384  [2600],[16800] is parameter
  }
