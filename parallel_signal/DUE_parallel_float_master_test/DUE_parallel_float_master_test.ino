
int num = 0;
union RECIVE{
  float rec;
  unsigned char data[4];
};
char para_speed = 1000;//約para_speed*4 microsecでfloat型(8bit*4)を受信

union RECIVE recive;


void setup() {
  Serial.begin(9600);
  
  //0~3の番号送信する
  pinMode(40,OUTPUT);//1桁目
  pinMode(41,OUTPUT);//2桁目

  //8bit受信する
  pinMode(30,INPUT_PULLUP);//1桁目
  pinMode(31,INPUT_PULLUP);//2桁目
  pinMode(32,INPUT_PULLUP);//3桁目
  pinMode(33,INPUT_PULLUP);//4桁目
  pinMode(34,INPUT_PULLUP);//5桁目
  pinMode(35,INPUT_PULLUP);//6桁目
  pinMode(36,INPUT_PULLUP);//7桁目
  pinMode(37,INPUT_PULLUP);//8桁目

  pinMode(53,OUTPUT);
  digitalWrite(53,HIGH);

}
void para(){
    digitalWrite(40,LOW);
    digitalWrite(41,LOW);
    digitalWrite(53,LOW);
    delay(10);
    
    recive.data[0] = digitalRead(30)  +  (digitalRead(31)<<1)  +  (digitalRead(32)<<2)  +  (digitalRead(33)<<3)  +  (digitalRead(34)<<4)  +  (digitalRead(35)<<5)  +  (digitalRead(36)<<6)  +  (digitalRead(37)<<7);
    digitalWrite(53,HIGH);
    
    digitalWrite(40,HIGH);
    digitalWrite(41,LOW);
    digitalWrite(53,LOW);
    delay(10);

    recive.data[0] = digitalRead(30)  +  (digitalRead(31)<<1)  +  (digitalRead(32)<<2)  +  (digitalRead(33)<<3)  +  (digitalRead(34)<<4)  +  (digitalRead(35)<<5)  +  (digitalRead(36)<<6)  +  (digitalRead(37)<<7);
    digitalWrite(53,HIGH);
    
    digitalWrite(40,LOW);
    digitalWrite(41,HIGH);
    digitalWrite(53,LOW);
    delay(10);

    recive.data[0] = digitalRead(30)  +  (digitalRead(31)<<1)  +  (digitalRead(32)<<2)  +  (digitalRead(33)<<3)  +  (digitalRead(34)<<4)  +  (digitalRead(35)<<5)  +  (digitalRead(36)<<6)  +  (digitalRead(37)<<7);
    digitalWrite(53,HIGH);
    
    digitalWrite(40,HIGH);
    digitalWrite(41,HIGH);
    digitalWrite(53,LOW);
    delay(10);
    
    recive.data[0] = digitalRead(30)  +  (digitalRead(31)<<1)  +  (digitalRead(32)<<2)  +  (digitalRead(33)<<3)  +  (digitalRead(34)<<4)  +  (digitalRead(35)<<5)  +  (digitalRead(36)<<6)  +  (digitalRead(37)<<7);
    digitalWrite(53,HIGH);

    Serial.println(recive.data[0]);
  
  }

/*
void para(){
    //送る数値を準備(0)
    digitalWrite(40,LOW);
    digitalWrite(41,LOW);
    //通信開始（送信）
    digitalWrite(53,LOW);
    //slaveの準備待ち
    delayMicroseconds(para_speed);
    //受信
    recive.data[0] = digitalRead(30)  +  (digitalRead(31)<<1)  +  (digitalRead(32)<<2)  +  (digitalRead(33)<<3)  +  (digitalRead(34)<<4)  +  (digitalRead(35)<<5)  +  (digitalRead(36)<<6)  +  (digitalRead(37)<<7);
    //通信終了
    digitalWrite(53,HIGH);

    //delayMicroseconds(1);//通信を完全にHIGHにするため...

    //送る数値を準備(1)
    digitalWrite(40,HIGH);
    digitalWrite(41,LOW);
    //通信開始（送信）
    digitalWrite(53,LOW);
    //slaveの準備待ち
    delayMicroseconds(para_speed);
    //受信
    recive.data[1] = digitalRead(30)  +  (digitalRead(31)<<1)  +  (digitalRead(32)<<2)  +  (digitalRead(33)<<3)  +  (digitalRead(34)<<4)  +  (digitalRead(35)<<5)  +  (digitalRead(36)<<6)  +  (digitalRead(37)<<7);
    //通信終了
    digitalWrite(53,HIGH);

    //delayMicroseconds(1);//通信を完全にHIGHにするため...
    
    //送る数値を準備(2)
    digitalWrite(40,LOW);
    digitalWrite(41,HIGH);
    //通信開始（送信）
    digitalWrite(53,LOW);
    //slaveの準備待ち
    delayMicroseconds(para_speed);
    //受信
    recive.data[2] = digitalRead(30)  +  (digitalRead(31)<<1)  +  (digitalRead(32)<<2)  +  (digitalRead(33)<<3)  +  (digitalRead(34)<<4)  +  (digitalRead(35)<<5)  +  (digitalRead(36)<<6)  +  (digitalRead(37)<<7);
    //通信終了
    digitalWrite(53,HIGH);

    //delayMicroseconds(1);//通信を完全にHIGHにするため...

    //送る数値を準備(3)
    digitalWrite(40,HIGH);
    digitalWrite(41,HIGH);
    //通信開始（送信）
    digitalWrite(53,LOW);
    //slaveの準備待ち
    delayMicroseconds(para_speed);
    //受信
    recive.data[3] = digitalRead(30)  +  (digitalRead(31)<<1)  +  (digitalRead(32)<<2)  +  (digitalRead(33)<<3)  +  (digitalRead(34)<<4)  +  (digitalRead(35)<<5)  +  (digitalRead(36)<<6)  +  (digitalRead(37)<<7);
    //通信終了
    digitalWrite(53,HIGH);
    
    Serial.println(recive.rec);
}
*/
void loop() {
  para();
  delay(1000);
}
