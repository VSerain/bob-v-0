#include <Arduino.h>
#include <Servo.h>

#ifndef ABSTARCTSERVO_H
#define ABSTARCTSERVO_H

class AbstarctServo {
    public:
        AbstarctServo(int servoPin);
        void load();
        void rotate(int rotation);
        int getCurrentRotation();
        int offset;

    private: 
        int servoPin;
        int rotation;
        Servo servo;
};

#endif
