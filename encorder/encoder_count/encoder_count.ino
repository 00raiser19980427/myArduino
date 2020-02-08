#define ENC_A 2
#define ENC_B 3

volatile byte pos; 
volatile int EncCount = 0;

 
void setup() {
  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);
 
  attachInterrupt(digitalPinToInterrupt(ENC_A), ENC_READ, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_B), ENC_READ, CHANGE);
 
  Serial.begin(38400);
}
 
 
void loop() {}
 
 
void ENC_READ() {  
  pos = ((pos & B00000011) << 2) + (!digitalRead(ENC_B) << 1) + !digitalRead(ENC_A);
  switch(pos){
      //反時計回り
      case B00000010 : 
      case B00001011 : 
      case B00001101 : 
      case B00000100 :
        EncCount--;
        Serial.println(EncCount); 
             
        break;
      //時計回り
      case B00000001 : 
      case B00000111 : 
      case B00001110 : 
      case B00001000 : 
        EncCount++; 
        Serial.println(EncCount);   
        break;
    }

  }
