#pragma once

#include <string>

class Distance {
    private:
        double distIN;
    public:
        /** Do not use */
        Distance(double inches);
        /** Do not use */
        Distance();
        /** Create an distance from an inch value /*/
        static Distance fromIN(double inches);
        /** Create a distance value from a feet value */
        static Distance fromFT(double ft);
        /** Create a distance from a yard value */
        static Distance fromYD(double yd);

        double asIN();
        double asFT();
        double asYD();

        std::string to_string();

        //Additive Stuff
        Distance operator+(Distance const& other) {
            return Distance(distIN + other.distIN);
        }
        Distance operator-(Distance const& other) {
            return Distance(distIN - other.distIN);
        }
        Distance operator*(Distance const& other) {
            return Distance(distIN * other.distIN);
        }
        Distance operator/(Distance const& other) {
            return Distance(distIN / other.distIN);
        }
};

inline Distance operator ""_in(long double ins) {
    return Distance::fromIN(ins);
}

inline Distance operator ""_ft(long double feet) {
    return Distance::fromFT(feet);
}

inline Distance operator ""_yd(long double yards) {
    return Distance::fromYD(yards);
}

inline Distance operator ""_in(unsigned long long ins) {
    return Distance::fromIN(ins);
}

inline Distance operator ""_ft(unsigned long long feet) {
    return Distance::fromFT(feet);
}

inline Distance operator ""_yd(unsigned long long yards) {
    return Distance::fromYD(yards);
}