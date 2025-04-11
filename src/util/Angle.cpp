#include <math.h>

#include "utilHeaders/Angle.hpp"
#include <format>

#define toRad(angle) angle * (M_PI/180)
#define toDeg(angle) angle * (180/M_PI)

Angle::Angle(double degrees) {
    this->angleDeg = degrees;
}

Angle::Angle() {
    this->angleDeg = 0;
}

Angle Angle::fromDeg(double degrees) {
    return Angle(degrees * 1);
}

Angle Angle::fromRad(double radians) {
    return Angle(toDeg(radians));
}

double Angle::asRad() {
    return toRad(this->angleDeg);
}

std::string Angle::to_string() {
    return std::format("{} Degrees", angleDeg);
}

double Angle::asDeg() {
    return this->angleDeg;
}