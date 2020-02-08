/*
 * SPIスレーブ(Arduino UNOの時)
 * SS   - Pin10 //変更不可
 * MOSI - Pin11 //変更不可
 * MISO - Pin12 //変更不可
 * SCK  - Pin13 //変更不可
 */
 
#include <SPI.h>
 
void setup() {
  pinMode(MISO,OUTPUT); //MISOを出力

  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE2));
  /*
  SPI.setBitOrder(MSBFIRST);            //最上位ビット(MSB)から送信
  SPI.setClockDivider(SPI_CLOCK_DIV4);  //通信速度をデフォルト
  SPI.setDataMode(SPI_MODE2);            //アイドル5Vで0V→5Vの変化で送信する
  */
  SPCR |= _BV(SPE);
     
  SPI.attachInterrupt(); 
}

byte ch;
float t=0;

typedef union   //共用体を宣言　//float型 = 4byte 、1byteづつ送信
{
 char snd[4];   //4byte分（char型＝1byte）
 float snd_val;
} SEND_DATA;

SEND_DATA snd_data; //共用体を定義
 
// SPI割り込み処理
ISR(SPI_STC_vect)
{
  ch = SPDR;    //SPIの受信バッファから取得 （受信した値を取得）
  
  snd_data.snd_val = t; //送信する値
  
  switch(ch){ //受信した番号で送信する値を指定（0から順に送信されてくる。0～3以外は無視）
    case 0:
      SPDR = snd_data.snd[0];
      break;
    case 1:
      SPDR = snd_data.snd[1];
      break;
    case 2:
      SPDR = snd_data.snd[2];
      break;
    case 3:
      SPDR = snd_data.snd[3];
      break;
    }
}
 
void loop() {
  t = t + 0.01;
  delay(10);
  // put your main code here, to run repeatedly:
}
