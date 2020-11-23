#include "./Head.h"

Head::Head(int pinServo, int echoPin, int triggerPin) : distanceSensor(triggerPin, echoPin) {
    this->echoPin = echoPin;
    this->triggerPin = echoPin;
    this->servo = AbstarctServo(pinServo);
};

void Head::load() {
    this->servo.load();
}

void Head::setRotation(int rotation) {
    this->servo.rotate(rotation * -1);

}

double Head::getDistance(int headRotation) {
    this->setRotation(headRotation);
    delay(100);
    double distance = this->distanceSensor.measureDistanceCm();
    return distance == -1 ? INFINITY : distance * 10 ; // Transform to mm
}

int Head::getBestRotation(int maxRotation, int rotationStep) {
    double bestDistance = 0.0;
    int bestRotation = 0;
    this->setRotation(-maxRotation);
    delay(500);

    for (int i = -maxRotation; i <= maxRotation; i+= rotationStep) {
        double distance = this->getDistance(i);
        if (distance > bestDistance || (distance > 1000 && abs(i) > abs(bestRotation))) {
            bestDistance = distance;
            bestRotation = i;
        }
    }

    this->setRotation(0);
    return bestRotation;
}

int Head::getBestRotation() {
    const int rotationStep = 15;
    const int maxRotation = 45;
    return this->getBestRotation(maxRotation, rotationStep);
}
