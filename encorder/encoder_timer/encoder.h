#ifndef ENCODER_H_
#define ENCODER_H_

class encoder {

  public:
    void EncPin(byte pinA , byte pinB);
    void EncCount();
    volatile int Count;
  private:
    byte EncA;
    byte EncB;
    volatile int EncState;
    
};

#endif
