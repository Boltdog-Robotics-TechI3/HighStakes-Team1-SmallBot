#include "main.h"
using namespace okapi;

void testAuto() {
    // chassis->moveDistance(2_ft);
    chassis->setMaxVelocity((10.0/4.0)*chassis->getMaxVelocity());
    chassis->setGains(       
        {0.001, 0, 0.00004},
        {0.0012, 0, 0.00002},
        {0.0005, 0, 0.0000}
    );

    chassis->turnAngle(90_deg);

    chassis->setMaxVelocity(0.4*chassis->getMaxVelocity());
    chassis->setGains(
        {0.005, 0, 0.00012},
        {0.005, 0, 0.00012},
        {0.001, 0, 0.0000}
    );
}
