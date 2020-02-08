/*
 * SPIマスタ(Arduino UNOの時)
 * SS   - Pin8    //複数選択可 ex) Pin7,Pin6...
 * MOSI - Pin11   //変更不可
 * MISO - Pin12   //変更不可
 * SCK  - Pin13   //変更不可
 */
 
#include <SPI.h>
 
#define SSPin 8
 
void setup() {
  Serial.begin (9600); 
  Serial.println("Master");
 
  pinMode(SSPin,OUTPUT); //SSピンを出力設定
 
  SPI.setBitOrder(MSBFIRST);            //最上位ビット(MSB)から送信
  SPI.setClockDivider(SPI_CLOCK_DIV4);  //通信速度をデフォルト
  SPI.setDataMode(SPI_MODE2);           //アイドル5Vで0V→5Vの変化で送信する
  SPI.begin();  //開始
}


 unsigned char rcv[2];
 
void loop() {
    
    OnecSPI();
    //データ確認
    Serial.print(rcv[0]);
    Serial.println(rcv[1]);
    delay(1000);
}

void OnecSPI(){
    //このSlaveをセレクトする
    //（マスタ通信は有効です）
  digitalWrite(SS, LOW);
  SPI.transfer(0);            // 1byte送受信 //値は受け取らない
  delayMicroseconds(100);     //Slave割り込みの計算完了待ち
  rcv[0] = SPI.transfer(1);   // 1byte送受信 //値を受け取る
  delayMicroseconds(100);     //Slave割り込みの計算完了待ち
  rcv[1] = SPI.transfer(255); // 1byte送受信 //値を受け取る
  digitalWrite(SS, HIGH);     //slaveとの通信を無効に
  }
 
/*
 * SSピンの設定
 * Lowでマスタからの通信が有効（セレクト）
 * (Highではマスタから通信出来ない(無視される）セレクト解除の状態)
 */
