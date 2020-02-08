#define ENC_A 2
#define ENC_B 3

volatile byte pos;  //volatile...プログラムの途中で割り込みが発生すると、実行途中だったプログラム内の（レジスタに格納された）変数は消滅してしまう。～～
                    //～～それを防ぐために、volatileをつけ、割り込み発生時に変数をスタック上に一旦退避させる。
 
void setup() {
  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);
 
  attachInterrupt(digitalPinToInterrupt(ENC_A), ENC_READ, CHANGE);//digitalPinToInterrupt(pin)...pinを割り込み専用の番号に変更してくれる。～～
  attachInterrupt(digitalPinToInterrupt(ENC_B), ENC_READ, CHANGE);//～～UNOの割り込みpinは2,3だが、attachInterrupt()では2pin→0,3pin→1という番号が割り振られている。
 
  Serial.begin(38400);
}
 
 
void loop() {}
 
 
void ENC_READ() {
  byte cur = (!digitalRead(ENC_B) << 1) + !digitalRead(ENC_A);  //下二桁を現在値に
  byte old = pos & B00000011;       //posの下二桁だけを有効（&B00000011）にしてoldへ代入
                                    //&B00011111なら下5桁が有効、1(true)の桁が有効になる
                                    //B011111101 & B11000111 は B01000101となる
  
  if (cur == 3) cur = 2;            //　11 10 00 01 11 10 → 3 2 0 1 3 2　なので、2 3 0 1 2 3 の順に変更させる（単に見やすくするための処理）～～
  else if (cur == 2) cur = 3;       //～～　                                     〃
 
  if (cur != old)                   //　前回と今回（oldとcur）の値が違うときのみ実行
  {
    //------------------------------------------サンプルプログラムはクリック付きのエンコーダーのため、ココから下は参考にならない...--------------------------------------
    bool rote = 0;
    if (cur == 3 && old == 0) rote = 0; //  一つ飛ばしてしまっている際はエラー→回転数は0として処理
    else if (cur == 0 && old == 3) rote = 0; //  一つ飛ばしてしまっている際はエラー→回転数は0として処理
    else if (cur > old) rote = 1;
 
    pos = (old << 2) + cur;
 
    const char vector[2] = {'<', '>'};
    Serial.print(vector[rote]);
    Serial.println(pos + (1 << 7), BIN);
    if (cur == 0) Serial.println();
  }
  }
