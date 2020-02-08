void setup() {
  // put your setup code here, to run once:
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  analogWriteResolution(12);
}

void motor(int xx){ 
  if(xx >= 0){
  analogWrite(11,xx);
  analogWrite(12,0);
  }
  if(xx < 0){
  xx = -xx;
  analogWrite(11,0);
  analogWrite(12,xx);
  }
}
int t=0;

void loop() {
  while(1){
    motor(t);
    t++;
    delay(10);
  }
}
