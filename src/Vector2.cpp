#include "./Vector2.h"

Vector2::Vector2(double x, double y) {
    this->x = x;
    this->y = y;
}

Vector2 Vector2::add(Vector2 otherVector) {
    return Vector2(this->x + otherVector.x, this->y + otherVector.y);
}

Vector2 Vector2::subtract(Vector2 otherVector) {
    return Vector2(this->x - otherVector.x, this->y - otherVector.y);
}

Vector2 Vector2::scale(double scale) {
    return Vector2(this->x * scale , this->y * scale);
}

Vector2 Vector2::getNormalVector() {
    return Vector2(-this->y, this->x).normalize();
}

double Vector2::length() {
    double uv = this->x * this->x + this->y * this->y;
    return sqrt(uv);
}

Vector2 Vector2::normalize() {
    double vectorLength = this->length();
    return Vector2(this->x / vectorLength, this->y / vectorLength);
}
