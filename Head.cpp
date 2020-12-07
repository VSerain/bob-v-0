#include "./Head.h"

Head::Head(int pinServo, int echoPin, int triggerPin) {
    this->echoPin = echoPin;
    this->triggerPin = triggerPin;
    this->servo = AbstarctServo(pinServo);
};

void Head::load() {
    this->servo.load();
    pinMode(this->triggerPin, OUTPUT);
    pinMode(this->echoPin, INPUT);
}

void Head::setRotation(int rotation) {
    this->servo.rotate(rotation * -1);
}

double Head::getDistance(int headRotation) {
    this->setRotation(headRotation);
    delay(100);
    double distance = this->measureDistanceCm();
    delay(50);
    return distance * 10 ; // Transform to mm
}

int Head::getBestRotation(int maxRotation, int rotationStep) {
    double bestDistance = 0.0;
    int bestRotation = 0;
    this->setRotation(-maxRotation);
    delay(100);

    for (int i = -maxRotation; i <= maxRotation + 1; i+= rotationStep) {
        double distance = this->getDistance(i);
        if (distance > bestDistance || (distance > 1000 && bestRotation != 0 && abs(i) > abs(bestRotation))) {
            bestDistance = distance;
            bestRotation = i;
        }
    }

    this->setRotation(0);
    delay(100);
    return bestRotation;
}

int Head::getBestRotation() {
    const int rotationStep = 15;
    const int maxRotation = 45;
    return this->getBestRotation(maxRotation, rotationStep);
}

double Head::measureDistanceCm() {
    return measureDistanceCm(19.307);
}

double Head::measureDistanceCm(float temperature) {
    digitalWrite(this->triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(this->triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->triggerPin, LOW);
    unsigned long durationMicroSec = pulseIn(this->echoPin, HIGH);

    double speedOfSoundInCmPerMs = 0.03313 + 0.0000606 * temperature; // Cair ≈ (331.3 + 0.606 ⋅ ϑ) m/s
    double distanceCm = durationMicroSec / 2.0 * speedOfSoundInCmPerMs;
    
    if(distanceCm > 400 || distanceCm == 0) {
        return 400;
    } 
    else {
        return distanceCm;
    }
}