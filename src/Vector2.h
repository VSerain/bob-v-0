#include <Arduino.h>;

#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2 {
    public: 
        Vector2(double x, double y);

        double x;
        double y;

        Vector2 add(Vector2 otherVector);
        Vector2 subtract(Vector2 otherVector);
        Vector2 scale(double scale);
        Vector2 getNormalVector();
        Vector2 normalize();
        double length(); 
};

#endif
