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
        if((send_num.sns[0] & 0b00000001)==0b00000001){REG_PIOD_SODR |= (0x01 << 9);}   //pin30 //digitalWite(30,HIGH)
          else{REG_PIOD_CODR |= (0x01 << 9);}                                                   //digitalWite(30,LOW)
        if((send_num.sns[0] & 0b00000010)==0b00000010){REG_PIOA_SODR |= (0x01 << 7);}   //pin31
          else{REG_PIOA_CODR |= (0x01 << 7);}                                         
        if((send_num.sns[0] & 0b00000100)==0b00000100){REG_PIOD_SODR |= (0x01 << 10);}  //pin32  
          else{REG_PIOD_CODR |= (0x01 << 10);}
        if((send_num.sns[0] & 0b00001000)==0b00001000){REG_PIOC_SODR |= (0x01 << 1);}   //pin33
          else{REG_PIOC_CODR |= (0x01 << 1);}
        if((send_num.sns[0] & 0b00010000)==0b00010000){REG_PIOC_SODR |= (0x01 << 2);}   //pin34
          else{REG_PIOC_CODR |= (0x01 << 2);}
        if((send_num.sns[0] & 0b00100000)==0b00100000){REG_PIOC_SODR |= (0x01 << 3);}   //pin35
          else{REG_PIOC_CODR |= (0x01 << 3);}
        if((send_num.sns[0] & 0b01000000)==0b01000000){REG_PIOC_SODR |= (0x01 << 4);}   //pin36
          else{REG_PIOC_CODR |= (0x01 << 4);}
        if((send_num.sns[0] & 0b10000000)==0b10000000){REG_PIOC_SODR |= (0x01 << 5);}   //pin37
          else{REG_PIOC_CODR |= (0x01 << 5);}
        break;

      case 1:
        if((send_num.sns[1] & 0b00000001)==0b00000001){REG_PIOD_SODR |= (0x01 << 9);}   //pin30 //digitalWite(30,HIGH)
          else{REG_PIOD_CODR |= (0x01 << 9);}                                                   //digitalWite(30,LOW)
        if((send_num.sns[1] & 0b00000010)==0b00000010){REG_PIOA_SODR |= (0x01 << 7);}   //pin31
          else{REG_PIOA_CODR |= (0x01 << 7);}                                         
        if((send_num.sns[1] & 0b00000100)==0b00000100){REG_PIOD_SODR |= (0x01 << 10);}  //pin32  
          else{REG_PIOD_CODR |= (0x01 << 10);}
        if((send_num.sns[1] & 0b00001000)==0b00001000){REG_PIOC_SODR |= (0x01 << 1);}   //pin33
          else{REG_PIOC_CODR |= (0x01 << 1);}
        if((send_num.sns[1] & 0b00010000)==0b00010000){REG_PIOC_SODR |= (0x01 << 2);}   //pin34
          else{REG_PIOC_CODR |= (0x01 << 2);}
        if((send_num.sns[1] & 0b00100000)==0b00100000){REG_PIOC_SODR |= (0x01 << 3);}   //pin35
          else{REG_PIOC_CODR |= (0x01 << 3);}
        if((send_num.sns[1] & 0b01000000)==0b01000000){REG_PIOC_SODR |= (0x01 << 4);}   //pin36
          else{REG_PIOC_CODR |= (0x01 << 4);}
        if((send_num.sns[1] & 0b10000000)==0b10000000){REG_PIOC_SODR |= (0x01 << 5);}   //pin37
          else{REG_PIOC_CODR |= (0x01 << 5);}
        break;
        
      case 2:
        if((send_num.sns[2] & 0b00000001)==0b00000001){REG_PIOD_SODR |= (0x01 << 9);}   //pin30 //digitalWite(30,HIGH)
          else{REG_PIOD_CODR |= (0x01 << 9);}                                                   //digitalWite(30,LOW)
        if((send_num.sns[2] & 0b00000010)==0b00000010){REG_PIOA_SODR |= (0x01 << 7);}   //pin31
          else{REG_PIOA_CODR |= (0x01 << 7);}                                         
        if((send_num.sns[2] & 0b00000100)==0b00000100){REG_PIOD_SODR |= (0x01 << 10);}  //pin32  
          else{REG_PIOD_CODR |= (0x01 << 10);}
        if((send_num.sns[2] & 0b00001000)==0b00001000){REG_PIOC_SODR |= (0x01 << 1);}   //pin33
          else{REG_PIOC_CODR |= (0x01 << 1);}
        if((send_num.sns[2] & 0b00010000)==0b00010000){REG_PIOC_SODR |= (0x01 << 2);}   //pin34
          else{REG_PIOC_CODR |= (0x01 << 2);}
        if((send_num.sns[2] & 0b00100000)==0b00100000){REG_PIOC_SODR |= (0x01 << 3);}   //pin35
          else{REG_PIOC_CODR |= (0x01 << 3);}
        if((send_num.sns[2] & 0b01000000)==0b01000000){REG_PIOC_SODR |= (0x01 << 4);}   //pin36
          else{REG_PIOC_CODR |= (0x01 << 4);}
        if((send_num.sns[2] & 0b10000000)==0b10000000){REG_PIOC_SODR |= (0x01 << 5);}   //pin37
          else{REG_PIOC_CODR |= (0x01 << 5);}
        break;
        
      case 3:
        if((send_num.sns[3] & 0b00000001)==0b00000001){REG_PIOD_SODR |= (0x01 << 9);}   //pin30 //digitalWite(30,HIGH)
          else{REG_PIOD_CODR |= (0x01 << 9);}                                                   //digitalWite(30,LOW)
        if((send_num.sns[3] & 0b00000010)==0b00000010){REG_PIOA_SODR |= (0x01 << 7);}   //pin31
          else{REG_PIOA_CODR |= (0x01 << 7);}                                         
        if((send_num.sns[3] & 0b00000100)==0b00000100){REG_PIOD_SODR |= (0x01 << 10);}  //pin32  
          else{REG_PIOD_CODR |= (0x01 << 10);}
        if((send_num.sns[3] & 0b00001000)==0b00001000){REG_PIOC_SODR |= (0x01 << 1);}   //pin33
          else{REG_PIOC_CODR |= (0x01 << 1);}
        if((send_num.sns[3] & 0b00010000)==0b00010000){REG_PIOC_SODR |= (0x01 << 2);}   //pin34
          else{REG_PIOC_CODR |= (0x01 << 2);}
        if((send_num.sns[3] & 0b00100000)==0b00100000){REG_PIOC_SODR |= (0x01 << 3);}   //pin35
          else{REG_PIOC_CODR |= (0x01 << 3);}
        if((send_num.sns[3] & 0b01000000)==0b01000000){REG_PIOC_SODR |= (0x01 << 4);}   //pin36
          else{REG_PIOC_CODR |= (0x01 << 4);}
        if((send_num.sns[3] & 0b10000000)==0b10000000){REG_PIOC_SODR |= (0x01 << 5);}   //pin37
          else{REG_PIOC_CODR |= (0x01 << 5);}
        break;
      }
}

void setup() {
  attachInterrupt(digitalPinToInterrupt(13), inter, FALLING); //LOWで割り込み
  
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
  send_num.sn = -93381.53;
}
