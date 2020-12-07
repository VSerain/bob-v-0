#include "./Manager.h"

const int MAX_SPEED = 150;
const int BOT_LENGTH = 160;
const int BOT_WIDTH = 80;
const int WHEEL_RAY = 65;

Manager::Manager(Head head, AbstarctServo frontWheel, DCMotor leftMotor, DCMotor rightMotor, int debug): head(head), frontWheel(frontWheel), leftMotor(leftMotor), rightMotor(rightMotor) {
    this->debug = debug;
    if (debug == 1) {
        Serial.begin(9600);
    }
    this->setMotorsSpeed(1);
}

int Manager::loop() {
    // Step 1 get front distance
    double distance = this->head.getDistance(0);
    if (distance < 50) {
        this->setMotorsSpeed(0); // Stop Motors 
        delay(500);

        distance = this->head.getDistance(0); // Recompute distance after stoping

        int futurRotation = this->head.getBestRotation(75, 15); // Find the best rotation (max distance)
        if (futurRotation == 0) return 1;

        this->turn(futurRotation * -1, -1, BOT_LENGTH); // reverse gear
        this->setMotorsSpeed(0.2); // not stop motor
    }
    else if (distance < 600) {
        this->setMotorsSpeed(0.4);
        int futurRotation = this->head.getBestRotation(30, 30); // Find the best rotation (max distance)

        this->turn(futurRotation, 0.4, BOT_LENGTH);
    }
    else {
        float speed = max(0.4, distance / 1200);
        this->setMotorsSpeed(speed);
        int futurRotation = this->head.getBestRotation(20, 20); // Find the best rotation (max distance)
        this->turn(futurRotation, speed, BOT_LENGTH);
    }
    return 0;
}

void Manager::turn(int rotation, double speed, double distance) {
    this->frontWheel.rotate(rotation);
    double speedMotorRight = this->computeDifferentielSpeed(rotation, 0, speed);
    double speedMotorLeft = this->computeDifferentielSpeed(rotation, 1, speed);

    if (speed > 0) {
        distance = distance / 4;
    }

    long waitTime = this->computeDelayWithDistance(distance, speed);

    if (speed < 0) {
        double anglePercentage = abs(rotation) / 0.9 / 100;
        waitTime = waitTime * anglePercentage;
        if (rotation > 0) {
            speedMotorLeft = speed;
            speedMotorRight = speed * -1;
        }
        else {
            speedMotorLeft = speed * -1;
            speedMotorRight = speed;
        }
    }

    this->leftMotor.setSpeed(speedMotorLeft);
    this->rightMotor.setSpeed(speedMotorRight);
    delay(waitTime);
    this->frontWheel.rotate(0);
    this->head.setRotation(0);
}

long Manager::computeDelayWithDistance(double distance, double speed) {
    if (distance == INFINITY || distance > 800) {
        distance = 800;
    }

    if (distance < 2) {
        distance = 100;
    }

    double rpm = MAX_SPEED * (speed > 0 ? speed : speed * -1);
    double currentRealSpeed = rpm * (WHEEL_RAY * PI) / 60 / 1000; // mm/ms
    return distance / currentRealSpeed;
}

double Manager::computeDifferentielSpeed(int angle, int side, double speed) {
    double rayon = computeRayByAngle(BOT_WIDTH, BOT_LENGTH, angle, 2);
    double vExt = speed * ((rayon + BOT_WIDTH/2) / rayon);
    double vInt = speed * ((rayon - BOT_WIDTH/2) / rayon);

    if (side == 0 && angle > 0) return vInt;
    if (side == 1 && angle < 0) return vInt;

    return vExt;
}

double Manager::computeDifferentielSpeed(int rotation, int side) {
    return this->computeDifferentielSpeed(rotation, side, 100);
}

void Manager::setMotorsSpeed(double speed) {
    if (speed == 0.0) {
        this->leftMotor.setSpeed(this->leftMotor.getSpeed() > 0 ? -1.0 : 1.0);
        this->rightMotor.setSpeed(this->rightMotor.getSpeed() > 0 ? -1.0 : 1.0);
        delay(50);
    }
    this->leftMotor.setSpeed(speed);
    this->rightMotor.setSpeed(speed);
}
