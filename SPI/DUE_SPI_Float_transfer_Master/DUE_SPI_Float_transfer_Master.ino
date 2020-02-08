/*
 * SPIマスタ(Arduino UNOの時)
 * SS   - Pin8    //複数選択可 ex) Pin7,Pin6...
 * MOSI - Pin11   //変更不可
 * MISO - Pin12   //変更不可
 * SCK  - Pin13   //変更不可
 */
 
#include <SPI.h>
 
#define SSPin 4
 
void setup() {
  Serial.begin (9600); 
  Serial.println("MasterSetup Start");
  
  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE2));   //  引数：  4Mhz , 最上位ビット(MSB)から送信で設定 , アイドル5Vで0V→5Vの変化で送信するモード   
  SPI.begin(SSPin);  //開始
  
  Serial.println("SPI_Setting End");
  Serial.println("MasterSetup End");
}



 typedef union
{
 char rcv[4];
 float rcv_val;
 
} RECIVE_DATA;

RECIVE_DATA rcv_data;
 
void loop() {
  
  Serial.println("Main Start");
  delay(1000);
  
    while(1){
      
    OnecSPI();//SPI通信関数
    
    //データ確認
    Serial.println(rcv_data.rcv_val);
    delay(1000);
    }
}

void OnecSPI(){
  
  SPI.transfer(SSPin, 0, SPI_CONTINUE);            // 1byte送受信 //値は受け取らない
  
  delayMicroseconds(100);                                  //Slave割り込みの計算完了待ち
  rcv_data.rcv[0] = SPI.transfer(SSPin, 1, SPI_CONTINUE);   // 1byte送受信 //値を受け取る
  delayMicroseconds(100);                                  //Slave割り込みの計算完了待ち
  rcv_data.rcv[1] = SPI.transfer(SSPin, 2, SPI_CONTINUE);   // 1byte送受信 //値を受け取る
  delayMicroseconds(100);                                  //Slave割り込みの計算完了待ち
  rcv_data.rcv[2] = SPI.transfer(SSPin, 3, SPI_CONTINUE);   // 1byte送受信 //値を受け取る
  delayMicroseconds(100);                                  //Slave割り込みの計算完了待ち
  rcv_data.rcv[3] = SPI.transfer(SSPin, 255 ,SPI_LAST);     // 1byte送受信 //値を受け取る
  }
 
/*
 * SSピンの設定
 * Lowでマスタからの通信が有効（セレクト）
 * (Highではマスタから通信出来ない(無視される）セレクト解除の状態)
 */
