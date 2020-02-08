#ifndef GYRO_H_
#define GYRO_H_

class gyro{
  public:
    void setupMPU6050();
    void sensor_read();
    void sensor_init();
    volatile void deg_integral();
    void sampling_10();

    volatile float degZ=0;

  
  private:

    long GyroX  , GyroY  , GyroZ ;
    long sum_sensInit;
    long bunsan_sensInit;
    long Data_s_sensInit[100];
    long ave_sensInit = 0;
    long HyoujunHensa_sensInit = 0 ;
    const byte HyoujunHensa_Baisu = 2 ;

    long sum_samp ;
    long ave_samp;
    long use_sampSum;
    int namber_of_use;
    int jud_samp;
    long samp_s[10];
    long abs_samp_s[10]; 
    volatile long sampling_10_re = 0;

    int i_sump;
    int t_sump;
  };


#endif
