#pragma once

class Angle {
    private:
        double angleDeg;
    public:
    /** Do not use */
        Angle(double degrees);
    /** Do not use */
        Angle();
    /** Create an angle from a degree value */
        static Angle fromDeg(double degrees);
    /** Create an angle from a radian value */
        static Angle fromRad(double radians);
    /** Get Angle as Degrees */
        double asDeg();
    /** Get Angle as Radians */
        double asRad();
    /** To String Function */
        string to_string();
        //Additive Stuff
        Angle operator+(Angle const& other) {
            return Angle(angleDeg + other.angleDeg);
        }
        Angle operator-(Angle const& other) {
            return Angle(angleDeg + other.angleDeg);
        }
        Angle operator*(Angle const& other) {
            return Angle(angleDeg * other.angleDeg);
        }
        Angle operator/(Angle const& other) {
            return Angle(angleDeg / other.angleDeg);
        }
        Angle operator==(Angle const& other) {
            return angleDeg == other.angleDeg;
        }
};

inline Angle operator "" _deg(long double degrees) {
    return Angle::fromDeg(degrees);
}
inline Angle operator "" _rad(long double rad) {
    return Angle::fromRad(rad);
}

inline Angle operator "" _deg(unsigned long long degrees) {
    return Angle::fromDeg(degrees);
}
inline Angle operator "" _rad(unsigned long long rad) {
    return Angle::fromRad(rad);
}