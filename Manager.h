#include <Arduino.h>;
#include "./DCMotor.h";
#include "./AbstarctServo.h";
#include "./Head.h";
#include "Geometry.h";
#include "Vector2.h";

#ifndef MANAGER_H
#define MANAGER_H

class Manager {
    public:
        Manager(Head head, AbstarctServo frontWheel, DCMotor leftMotor, DCMotor rightMotor, int debug);
        int loop();
        void turn(int rotation, double speed, double distance);
    private:
        int debug;
        Head head;
        AbstarctServo frontWheel;
        DCMotor leftMotor;
        DCMotor rightMotor;

        void setMotorsSpeed(double speed);
        long computeDelayWithDistance(double distance, double speed);
        double computeDifferentielSpeed(int rotation, int side, double speed);
        double computeDifferentielSpeed(int rotation, int side);
};

#endif
