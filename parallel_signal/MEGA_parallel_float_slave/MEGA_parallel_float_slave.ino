int rec = 0;
union SEND_NUM{
  float  sn;
  char sns[4];
  };
  
union SEND_NUM send_num;


void inter(){ 
    //受信した数値を読み取る
    rec = digitalRead(40)  +  (digitalRead(41)<<1);

    //送信する数値を準備
    switch(rec){
      case 0:
        if((send_num.sns[0] & 0b00000001)==0b00000001){PORTC |= 0b10000000;}   //pin30 //digitalWite(30,HIGH)
          else{PORTC &= ~ 0b10000000;}                                                   //digitalWite(30,LOW)
        if((send_num.sns[0] & 0b00000010)==0b00000010){PORTC |= 0b01000000;}   //pin31
          else{PORTC &= ~ 0b01000000;}                                         
        if((send_num.sns[0] & 0b00000100)==0b00000100){PORTC |= 0b00100000;}  //pin32  
          else{PORTC &= ~ 0b00100000;}
        if((send_num.sns[0] & 0b00001000)==0b00001000){PORTC |= 0b00010000;}   //pin33
          else{PORTC &= ~ 0b00010000;}
        if((send_num.sns[0] & 0b00010000)==0b00010000){PORTC |= 0b00001000;}   //pin34
          else{PORTC &= ~ 0b00001000;}
        if((send_num.sns[0] & 0b00100000)==0b00100000){PORTC |= 0b00000100;}   //pin35
          else{PORTC &= ~ 0b00000100;}
        if((send_num.sns[0] & 0b01000000)==0b01000000){PORTC |= 0b00000010;}   //pin36
          else{PORTC &= ~ 0b00000010;}
        if((send_num.sns[0] & 0b10000000)==0b10000000){PORTC |= 0b10000001;}   //pin37
          else{PORTC &= ~ 0b00000001;}
        Serial.print(rec);
        break;

      case 1:
        if((send_num.sns[1] & 0b00000001)==0b00000001){PORTC |= 0b10000000;}   //pin30 //digitalWite(30,HIGH)
          else{PORTC &= ~ 0b10000000;}                                                   //digitalWite(30,LOW)
        if((send_num.sns[1] & 0b00000010)==0b00000010){PORTC |= 0b01000000;}   //pin31
          else{PORTC &= ~ 0b01000000;}                                         
        if((send_num.sns[1] & 0b00000100)==0b00000100){PORTC |= 0b00100000;}  //pin32  
          else{PORTC &= ~ 0b00100000;}
        if((send_num.sns[1] & 0b00001000)==0b00001000){PORTC |= 0b00010000;}   //pin33
          else{PORTC &= ~ 0b00010000;}
        if((send_num.sns[1] & 0b00010000)==0b00010000){PORTC |= 0b00001000;}   //pin34
          else{PORTC &= ~ 0b00001000;}
        if((send_num.sns[1] & 0b00100000)==0b00100000){PORTC |= 0b00000100;}   //pin35
          else{PORTC &= ~ 0b00000100;}
        if((send_num.sns[1] & 0b01000000)==0b01000000){PORTC |= 0b00000010;}   //pin36
          else{PORTC &= ~ 0b00000010;}
        if((send_num.sns[1] & 0b10000000)==0b10000000){PORTC |= 0b10000001;}   //pin37
          else{PORTC &= ~ 0b00000001;}
        Serial.print(rec);
        break;
        
      case 2:
        if((send_num.sns[2] & 0b00000001)==0b00000001){PORTC |= 0b10000000;}   //pin30 //digitalWite(30,HIGH)
          else{PORTC &= ~ 0b10000000;}                                                   //digitalWite(30,LOW)
        if((send_num.sns[2] & 0b00000010)==0b00000010){PORTC |= 0b01000000;}   //pin31
          else{PORTC &= ~ 0b01000000;}                                         
        if((send_num.sns[2] & 0b00000100)==0b00000100){PORTC |= 0b00100000;}  //pin32  
          else{PORTC &= ~ 0b00100000;}
        if((send_num.sns[2] & 0b00001000)==0b00001000){PORTC |= 0b00010000;}   //pin33
          else{PORTC &= ~ 0b00010000;}
        if((send_num.sns[2] & 0b00010000)==0b00010000){PORTC |= 0b00001000;}   //pin34
          else{PORTC &= ~ 0b00001000;}
        if((send_num.sns[2] & 0b00100000)==0b00100000){PORTC |= 0b00000100;}   //pin35
          else{PORTC &= ~ 0b00000100;}
        if((send_num.sns[2] & 0b01000000)==0b01000000){PORTC |= 0b00000010;}   //pin36
          else{PORTC &= ~ 0b00000010;}
        if((send_num.sns[2] & 0b10000000)==0b10000000){PORTC |= 0b10000001;}   //pin37
          else{PORTC &= ~ 0b00000001;}
        Serial.print(rec);
        break;
        
      case 3:
        if((send_num.sns[3] & 0b00000001)==0b00000001){PORTC |= 0b10000000;}   //pin30 //digitalWite(30,HIGH)
          else{PORTC &= ~ 0b10000000;}                                                   //digitalWite(30,LOW)
        if((send_num.sns[3] & 0b00000010)==0b00000010){PORTC |= 0b01000000;}   //pin31
          else{PORTC &= ~ 0b01000000;}                                         
        if((send_num.sns[3] & 0b00000100)==0b00000100){PORTC |= 0b00100000;}  //pin32  
          else{PORTC &= ~ 0b00100000;}
        if((send_num.sns[3] & 0b00001000)==0b00001000){PORTC |= 0b00010000;}   //pin33
          else{PORTC &= ~ 0b00010000;}
        if((send_num.sns[3] & 0b00010000)==0b00010000){PORTC |= 0b00001000;}   //pin34
          else{PORTC &= ~ 0b00001000;}
        if((send_num.sns[3] & 0b00100000)==0b00100000){PORTC |= 0b00000100;}   //pin35
          else{PORTC &= ~ 0b00000100;}
        if((send_num.sns[3] & 0b01000000)==0b01000000){PORTC |= 0b00000010;}   //pin36
          else{PORTC &= ~ 0b00000010;}
        if((send_num.sns[3] & 0b10000000)==0b10000000){PORTC |= 0b10000001;}   //pin37
          else{PORTC &= ~ 0b00000001;}
        Serial.println(rec);
        break;
      }
}

void setup() {
  attachInterrupt(digitalPinToInterrupt(2), inter, FALLING); //LOWで割り込み
  Serial.begin(9600);
  pinMode(40,INPUT_PULLUP);
  pinMode(41,INPUT_PULLUP);

  pinMode(30,OUTPUT);
  pinMode(31,OUTPUT);
  pinMode(32,OUTPUT);
  pinMode(33,OUTPUT);
  pinMode(34,OUTPUT);
  pinMode(35,OUTPUT);
  pinMode(36,OUTPUT);
  pinMode(37,OUTPUT);
}

void loop() {  
  send_num.sn = -1;
}
