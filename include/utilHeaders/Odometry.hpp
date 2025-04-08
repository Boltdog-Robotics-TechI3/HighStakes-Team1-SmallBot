#pragma once

#include "utilHeaders/Pose2D.hpp"
#include "utilHeaders/Chassis.hpp"

class Odometry {
    private:
        Pose2D pose;

    public:
        Odometry(Chassis chassis);
    
};