#include "main.h"
#define toRad(angle) angle * (M_PI/180)
#define toDeg(angle) angle * (180/M_PI)
Angle::Angle(double degrees) {
    this->angleDeg = degrees;
}

Angle Angle::fromDeg(double degrees) {
    Angle(degrees * 1);
}

Angle Angle::fromRad(double radians) {
    Angle(toDeg(radians));
}

double Angle::asRad() {
    return toRad(this->angleDeg);
}

double Angle::asDeg() {
    return this->angleDeg;
}

