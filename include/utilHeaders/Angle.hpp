class Angle {
    private:
        double angleDeg;
        Angle(double degrees);
    public:
    /** Create an angle from a degree value */
        static Angle fromDeg(double degrees);
    /** Create an angle from a radian value */
        static Angle fromRad(double radians);
    /** Get Angle as Degrees */
        double asDeg();
    /** Get Angle as Radians */
        double asRad();
};

inline Angle operator "" _degs(long double degrees) {
    return Angle::fromDeg(degrees);
}
inline Angle operator "" _rads(long double rad) {
    return Angle::fromRad(rad);
}

inline Angle operator "" _degs(unsigned long long degrees) {
    return Angle::fromDeg(degrees);
}
inline Angle operator "" _rads(unsigned long long rad) {
    return Angle::fromRad(rad);
}