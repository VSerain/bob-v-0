#include "./Geometry.h"

Vector2 intersectLines(Vector2 AP0, Vector2 AP1, Vector2 BP0, Vector2 BP1) {
    double coefLineA = (AP0.y - AP1.y) / (AP0.x - AP1.x);
    double coefLineB = (BP0.y - BP1.y) / (BP0.x - BP1.x);

    double valueLineA = AP1.y - (coefLineA * AP1.x);
    double valueLineB = BP1.y - (coefLineB * BP1.x);

    double Vco = -coefLineB + coefLineA;
    double Vcob = -valueLineB + valueLineA;

    double x = -(Vcob/Vco);
    double y = (coefLineB * x) + valueLineB;

    return Vector2(x,y);
}

Vector2 rotateAroudPoint(Vector2 point, Vector2 centerPoint, double angle) {
    double radAngle = degToRad(angle);
    double newX = cos(radAngle) * (point.x - centerPoint.x) - sin(radAngle) * (point.y - centerPoint.y) + centerPoint.x;
    double newY = sin(radAngle) * (point.x - centerPoint.x) + cos(radAngle) * (point.y - centerPoint.y) + centerPoint.y;
    return Vector2(newX, newY);
}

double degToRad(double angle) {
    return angle * PI / 180;
}

double computeRayByAngle(int width, int length, double angle, int wheelIndex) {
    Vector2 a = Vector2(width/2, length);
    Vector2 b = Vector2(0, 0);
    Vector2 c = Vector2(width, 0);

    Vector2 centralBack = b.add(c).scale(0.5);
    Vector2 botCenter = a.add(centralBack).scale(0.5);
    Vector2 vector = centralBack.subtract(a);
    Vector2 normal = vector.getNormalVector();

    Vector2 flechePoint = rotateAroudPoint(botCenter, a, angle);
    Vector2 intersectPoint = intersectLines(a, flechePoint, botCenter, normal);

    Vector2 i = intersectPoint.add(b).scale(0.5);
    Vector2 iNormal = b.subtract(intersectPoint).getNormalVector().scale(-1);

    double flecheLength = botCenter.subtract(intersectPoint).length();

    Vector2 centerCirclePoint = intersectLines(botCenter, botCenter.add(normal.scale(-1)), i, i.add(iNormal));

    if (wheelIndex == 0) {
        return b.subtract(centerCirclePoint).length();
    } else if (wheelIndex == 1) {
        return c.subtract(centerCirclePoint).length();
    } else {
        return a.subtract(centerCirclePoint).length();
    }
    return -1;
}