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
 
  SPI.setBitOrder(MSBFIRST);            //最上位ビット(MSB)から送信
  SPI.setClockDivider(SPI_CLOCK_DIV4);  //通信速度をデフォルト
  SPI.setDataMode(SPI_MODE2);            //アイドル5Vで0V→5Vの変化で送信する
  SPCR |= _BV(SPE);
     
  SPI.attachInterrupt(); 
}

byte ch;
 
// SPI割り込み処理
ISR(SPI_STC_vect)
{
  ch = SPDR;    //SPIの受信バッファから取得
  switch(ch){
    case 0:
      SPDR = 100;
      break;
    case 1:
      SPDR = 200;
      break;
    }
}
 
void loop() {
  // put your main code here, to run repeatedly:
}
