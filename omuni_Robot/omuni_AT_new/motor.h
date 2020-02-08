#ifndef MOTOR_H_
#define MOTOR_H_

class motor {
  public:
    void MotorPin_init(byte PWM ,byte DIRE);
    void SetDuty(int Duty);
  private:
    byte *DirectionPin;
    byte *PwmPin;    
};

#endif
