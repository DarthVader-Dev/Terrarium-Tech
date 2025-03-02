#ifndef motionsensor_h
#define motionsensor_h
class MotionSensor {
  private: byte pin;
  public: 
    MotionSensor(byte pin);
    void init();
    


};

#endif