/*
 * SPIスレーブ(Arduino UNOの時)
 * SS   - Pin10 //変更不可
 * MOSI - Pin11 //変更不可
 * MISO - Pin12 //変更不可
 * SCK  - Pin13 //変更不可
 */
 
#include <SPI.h>
#include <Wire.h>
#include <VL53L1X.h>
 
VL53L1X sensor;
 
#define SHUT 6
int *leng;
int leng_data[3];

//----------------------SPI_init_start--------------------------------
byte ch;

typedef union   //共用体を宣言　//float型 = 4byte 、1byteづつ送信
{
 char snd[2];   //4byte分（char型＝1byte）
 int snd_val;
} SEND_DATA;

SEND_DATA snd_data; //共用体を定義
//----------------------SPI_init_end--------------------------------

void setup() {
//----------------------vl53l1x_Setting_start------------------
pinMode(13,OUTPUT);
digitalWrite(13,HIGH);
pinMode(SHUT, OUTPUT);

digitalWrite(SHUT, LOW);

delay(100);
Wire.begin();

pinMode(SHUT, INPUT);
delay(150);
sensor.init();
delay(100);
sensor.setAddress((uint8_t)23);
sensor.setTimeout(100);
sensor.setDistanceMode(VL53L1X::Long);//VL53L1X::Short, VL53L1X::Medium, or VL53L1X::Long
 
sensor.startContinuous(5);

digitalWrite(13,LOW);
//----------------------vl53l1x_Setting_end------------------
//----------------------SPI_Setting_start------------------
  pinMode(MISO,OUTPUT); //MISOを出力
 
  SPI.setBitOrder(MSBFIRST);            //最上位ビット(MSB)から送信
  SPI.setClockDivider(SPI_CLOCK_DIV4);  //通信速度をデフォルト
  SPI.setDataMode(SPI_MODE2);            //アイドル5Vで0V→5Vの変化で送信する
  SPCR |= _BV(SPE);
     
  SPI.attachInterrupt(); 
//----------------------SPI_Setting_end------------------

}

//----------------------SPI_Function_start---------------------

 
// SPI割り込み処理
ISR(SPI_STC_vect)
{
  ch = SPDR;    //SPIの受信バッファから取得 （受信した値を取得）
  
  snd_data.snd_val = *leng; //送信する値
  
  switch(ch){ //受信した番号で送信する値を指定（0から順に送信されてくる。0～3以外は無視）
    case 0:
      SPDR = snd_data.snd[0];
      break;
    case 1:
      SPDR = snd_data.snd[1];
      break;
    }
}
//----------------------SPI_Function_end---------------------

void loop(){
  while(1){
    leng_data[0] = sensor.readRangeContinuousMillimeters();
    leng_data[1] = sensor.readRangeContinuousMillimeters();
    leng_data[2] = sensor.readRangeContinuousMillimeters();

    if(leng_data[0]>=leng_data[1]){ 
      if(leng_data[0]>=leng_data[2]){
        if(leng_data[1]>=leng_data[2]){ 
          leng =&leng_data[1];
        }
        else{leng = &leng_data[2];}
      }
      else{leng = &leng_data[0];}   
    }
    else{
      if(leng_data[1]>=leng_data[2]){
        if(leng_data[0]>=leng_data[2]){
          leng = &leng_data[0];
          }
        else{leng = &leng_data[2];}
      }
      else{leng = &leng_data[1];}
    }
  }  
}
