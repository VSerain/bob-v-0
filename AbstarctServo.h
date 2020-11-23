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

    private: 
        int servoPin;
        int rotation;
        int offset;
        Servo servo;
};

#endif
