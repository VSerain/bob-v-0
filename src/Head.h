#include "./AbstarctServo.h";

#ifndef HEAD_H
#define HEAD_H

class Head {
    public:
        Head(int pinServo, int echoPin, int trigerPin);
        void load();
        void setRotation(int rotation);
        double getDistance(int headRotation);
        int getBestRotation(int maxRotation, int rotationStep);
        int getBestRotation();
    
    private:
        int echoPin;
        int triggerPin;

        double measureDistanceCm();
        double measureDistanceCm(float temperature);
        AbstarctServo servo = NULL;
};
#endif
