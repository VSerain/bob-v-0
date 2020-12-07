#include <Arduino.h>

#ifndef DCMOTOR_H
#define DCMOTOR_H


class DCMotor {
    public:
        DCMotor(int speedPin, int doorAPin, int doorBpin);
        void load();
        void stop();
        void setSpeed(float speed);
        float getSpeed();

    private: 
        int _speedPin;
        int _doorAPin;
        int _doorBPin;
        float _speed;
};

#endif
