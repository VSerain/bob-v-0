#include <Arduino.h>;
#include "./Vector2.h";

#ifndef GEOMERTY_H
#define GEOMERTY_H

Vector2 intersectLines(Vector2 AP0, Vector2 AP1, Vector2 BP0, Vector2 BP1);
Vector2 rotateAroudPoint(Vector2 point, Vector2 centerPoint, double angle, int wheelIndex);
double computeRayByAngle(int width, int length, double angle, int wheelIndex);
double degToRad(double angle);

#endif
