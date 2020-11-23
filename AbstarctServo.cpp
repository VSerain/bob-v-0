#include "./AbstarctServo.h"

AbstarctServo::AbstarctServo(int servoPin) {
    this->servoPin = servoPin;
    this->offset = -5;
};

void AbstarctServo::load() {
    this->servo.attach(this->servoPin);
    this->rotate(0);
}

void AbstarctServo::rotate(int rotation) {
    this->rotation = rotation;

    this->servo.write(90 + this->offset + rotation);
}

int AbstarctServo::getCurrentRotation() {
    return this->rotation;
}
