#include "main.h"
using namespace okapi;

void testAuto() {

    // chassis->setMaxVelocity((10.0/4.0)*chassis->getMaxVelocity());
    // chassis->setGains(       
    //     {0.001, 0, 0.00004},
    //     {0.0012, 0, 0.00002},
    //     {0.0005, 0, 0.0000}
    // );
    print(1,0,"TestAuto has started");
    turnAngle(90.0);
    turnAngle(90.0);
    turnAngle(90.0);
    turnAngle(90.0);
    turnAngle(90.0);
    print(1,0,"TestAuto has finished");

    // chassis->setMaxVelocity(0.4*chassis->getMaxVelocity());
    // chassis->setGains(
    //     {0.005, 0, 0.00012},
    //     {0.005, 0, 0.00012},
    //     {0.001, 0, 0.0000}
    // );
}
