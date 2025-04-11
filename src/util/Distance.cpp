#include "utilHeaders/Distance.hpp"
#include <format>

Distance::Distance(double in) {
    this->distIN = in;
}

Distance::Distance() {
    this->distIN = 0;
}

Distance Distance::fromIN(double inches) {
    return Distance(inches);
}

Distance Distance::fromFT(double ft) {
    return Distance(ft * 12);
}

Distance Distance::fromYD(double yd) {
    return Distance(yd * 36);
}

double Distance::asIN() {
    return this->distIN;
}

double Distance::asFT() {
    return this->distIN / 12;
}

double Distance::asYD() {
    return this->distIN / 36;
}

std::string Distance::to_string() {
    return std::format("{} Inches", distIN);
}
