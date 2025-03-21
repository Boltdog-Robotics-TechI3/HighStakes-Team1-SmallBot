#define toRad(angle) angle * (M_PI/180)
#define toDeg(angle) angle * (180/M_PI)
Angle::Angle(double degrees) {
    this->angleDeg = degrees;
}

Angle Angle::fromDeg(double degrees) {
    return Angle::Angle(double degrees);
}

Angle Angle::fromRad(double radians) {
    return Angle::Angle(toDeg(radians));
}

double Angle::asRad() {
    return toRad(this->angleDeg);
}

double Angle::asDeg() {
    return this->angleDeg;
}

