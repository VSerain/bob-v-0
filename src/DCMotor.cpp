#include "./DCMotor.h";

DCMotor::DCMotor(int pwmMotorPin, int doorAPin, int doorBPin) {
    if (pwmMotorPin > 13) {
        Serial.println("Please use PWM for connect motor");
        return;
    }
    this->_speedPin = pwmMotorPin;
    this->_doorAPin = doorAPin;
    this->_doorBPin = doorBPin;
}

void DCMotor::load() {
    pinMode(this->_speedPin, OUTPUT);
    pinMode(this->_doorAPin, OUTPUT);
    pinMode(this->_doorBPin, OUTPUT);

    this->stop();
}

void DCMotor::stop() {
    digitalWrite(this->_doorAPin, HIGH); 
    digitalWrite(this->_doorBPin, HIGH);
}

void DCMotor::setSpeed(float speed) {
    float lastSpeed = this->_speed;
    this->_speed = speed;
    if (speed > 0.2) {
        digitalWrite(this->_doorAPin, HIGH); 
        digitalWrite(this->_doorBPin, LOW);
    } else if (speed < -0.2) {
        digitalWrite(this->_doorAPin, LOW); 
        digitalWrite(this->_doorBPin, HIGH);
    } else {
        this->stop();
    }

    analogWrite(this->_speedPin, min(255, (int) abs(speed * (float) 255)));
}

float DCMotor::getSpeed() {
    return this->_speed;
}
