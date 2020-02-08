#include <Wire.h>

long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;
 
long gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ;

float x_init; 
float y_init; 
float z_init;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  setupMPU6050();
  // put your setup code here, to run once:

}




float sensor_ave(float t){
  float sum;
  int arrey[100];
  int i;
    for(i=0;i<100;i++){
    recordAccelRegisters();
    recordGyroRegisters();
    arrey[i]=t;
    delay(10);
      }
    for(i=0;i<100;i++){
      sum +=arrey[i];
      }
  return sum/100;
  sum = 0;
}
float init_sensor(float XX_ave,float YY_ave, float ZZ_ave){
  x_init = sensor_ave(XX_ave);
  y_init = sensor_ave(YY_ave);
  z_init = sensor_ave(ZZ_ave);
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
  calculateAccelData();
}
 
void calculateAccelData() {
  //読み取った値をgに変換
  gForceX = accelX / 16384.0;
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
  calculateGyroData();
}
 
void calculateGyroData() {
  //読み取った値をdeg/secに変換
  rotX = gyroX / 131.0;
  rotY = gyroY / 131.0;
  rotZ = gyroZ / 131.0;
}
 

 
void loop() {
  recordAccelRegisters();
  recordGyroRegisters();
  float init_sensor(rotX, rotY, rotZ);
  Serial.print(x_init);
  Serial.print("  ");
  Serial.print(y_init);
  Serial.print("  ");
  Serial.print(z_init);
  Serial.print("\n\r");
  delay(1000);
  // put your main code here, to run repeatedly:
}
