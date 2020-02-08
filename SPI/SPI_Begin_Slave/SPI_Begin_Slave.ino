/*
 * SPIスレーブ
 * SS   - Pin10
 * MOSI - Pin11
 * MISO - Pin12
 * SCK  - Pin13
 */
 
#include <SPI.h>
 
void setup() {
  pinMode(MISO,OUTPUT); //MISOを出力
 
  SPI.setBitOrder(MSBFIRST);  //最上位ビット(MSB)から送信
  SPI.setClockDivider(SPI_CLOCK_DIV4);  //通信速度をデフォルト
  SPI.setDataMode(SPI_MODE2);   //アイドル5Vで0V→5Vの変化で送信する
  SPCR |= _BV(SPE);
     
  SPI.attachInterrupt(); 
}
 
// SPI割り込み処理
ISR(SPI_STC_vect)
{
  byte ch = SPDR;    //SPIの受信バッファから取得
  SPDR = ch;  //送信バッファに書き込む
}
 
void loop() {
  // put your main code here, to run repeatedly:
}
