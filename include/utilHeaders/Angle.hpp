class Angle {
    private:
        double angleDeg;
        Angle(double degrees);
    public:
    /** Create an angle from a degree value */
        static Angle fromDegrees(double degrees);
    /** Create an angle from a radian value */
        static Angle fromRad(double radians);
    /** Get Angle as Degrees */
        double asDeg();
    /** Get Angle as Radians */
        double asRad();
};

Angle operator "" _degs(double degrees) {
    return Angle::fromDegrees(degrees);
}

Angle operator "" _rads(double rad) {
    return Angle::fromRad(rad);
}