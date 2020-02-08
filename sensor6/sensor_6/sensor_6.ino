#include <Wire.h>

 
float accelX, accelY, accelZ;
float gyroX, gyroY, gyroZ;


void setup() {
  Serial.begin(9600);
  Wire.begin();
  setupMPU6050();
  Serial.print("OK_setup\n\r");
  delay(1000);
}

void loop() {
  while(1){
  accel_read_start();
  gyro_read_start();
  Serial.print("accelX = ");
  Serial.print(accelX);
  Serial.print("  ");
  Serial.print("accelY = ");
  Serial.print(accelY);
  Serial.print("  ");
  Serial.print("accelZ = ");
  Serial.print(accelZ);
  
  Serial.print("          ");
  
  Serial.print("gyroX = ");
  Serial.print(gyroX);
  Serial.print("  ");
  Serial.print("gyroY = ");
  Serial.print(gyroY);
  Serial.print("  ");
  Serial.print("gyroZ = ");
  Serial.print(gyroZ);
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
 
void recordAccelRegisters() { //read value of accel-sensor
  long accX,accY,accZ;
  Wire.beginTransmission(0b1101000);
  Wire.write(0x3B); // Accel Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000, 6); //Request Accel Registers (3B - 40)
  while (Wire.available() < 6);
  accX = Wire.read() << 8 | Wire.read(); //Store first two bytes into accelX
  accY = Wire.read() << 8 | Wire.read(); //Store middle two bytes into accelY
  accZ = Wire.read() << 8 | Wire.read(); //Store last two bytes into accelZ
  accelX = (float(accX) / 16384.0)*9.8; //change to gravitational acceleration(m/s^2)
  accelY = (float(accY) / 16384.0)*9.8; //change to gravitational acceleration(m/s^2)
  accelZ = (float(accZ) / 16384.0)*9.8; //change to gravitational acceleration(m/s^2)
}

void accel_read_start(){  //so recordAccelRegisters() couse of bug
  recordAccelRegisters();
  }


void recordGyroRegisters() {  //read value of gyro-sensor
  long gX, gY, gZ;
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x43); //Starting register for Gyro Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000, 6); //Request Gyro Registers (43 - 48)
  while (Wire.available() < 6);
  gX = Wire.read() << 8 | Wire.read(); //Store first two bytes into accelX
  gY = Wire.read() << 8 | Wire.read(); //Store middle two bytes into accelY
  gZ = Wire.read() << 8 | Wire.read(); //Store last two bytes into accelZ
  gyroX = float(gX) / 131.0; //change to deg/sec
  gyroY = float(gY) / 131.0; //change to deg/sec
  gyroZ = float(gZ) / 131.0; //change to deg/sec
}

void gyro_read_start(){        //so recordGyroRegisters() couse of bug
  recordGyroRegisters(); 
  }
