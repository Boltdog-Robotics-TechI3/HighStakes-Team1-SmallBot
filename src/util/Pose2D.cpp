#include <algorithm>
#include <cmath>

#include "utilHeaders/Pose2D.hpp"

/**
 * Method Definitions for the Pose2D class. C++ is really stupid.
 */
/**
 * @brief Constructor for Pose2D.
 * 
 * @param x the x coordinate of the robot in inches
 * @param y the y coordinate of the robot in inches
 * @param heading the heading of the robot in radians
 */
 Pose2D::Pose2D(Distance x, Distance y, Angle heading)
 : x(Distance::fromIN(std::clamp(x.asIN(), -72.0, 72.0))),
   y(Distance::fromIN(std::clamp(y.asIN(), -72.0, 72.0))),
   heading(Angle::fromDeg(std::clamp(heading.asDeg(), 0.0, 360.0))) {
 // no need to call setPose
}

/**
 * @brief Default constructor for Pose2D.
 * Sets the x, y, and heading to 0
 */     
Pose2D::Pose2D() {
    Pose2D(0_in, 0_in, 0_deg);
}

/**
 * @brief Resets the pose of the robot to (0, 0, 0)
 */     
void Pose2D::reset() { 
    setPose(0_in, 0_in, 0_deg);
}

/**
 * @brief Set the pose of the robot
 * 
 * @param x the new x coordinate of the robot in inches
 * @param y the new y coordinate of the robot in inches
 * @param heading the new heading of the robot in radians
 */
void Pose2D::setPose(Distance x, Distance y, Angle heading) {
    this->x = Distance::fromIN(std::clamp(x.asIN(), -72.0, 72.0));
    this->y = Distance::fromIN(std::clamp(y.asIN(), -72.0, 72.0));
    this->heading = Angle::fromDeg(std::clamp(heading.asDeg(), 0.0, 360.0));
    // pros::Task::notify();
}

/**
 * @brief Set the pose of the robot
 * 
 * @param pose the new pose of the robot
 */
void Pose2D::setPose(Pose2D pose) {
    setPose(pose.getX(), pose.getY(), pose.getHeading());
}

/**
 * @brief Get the x coordinate
 * 
 * @return the x coordinate in inches
 */
Distance Pose2D::getX() {
    // while (pros::Task::notify_take(true, 500));
    return x;
} 

/**
 * @brief Get the y coordinate
 * 
 * @return the y coordinate in inches
 */
Distance Pose2D::getY() {
    // while (pros::Task::notify_take(true, 500));
    return y;
}

/**
 * @brief Get the heading
 * 
 * @return the heading in radians
 */
Angle Pose2D::getHeading() {
    // while (pros::Task::notify_take(true, 500)):
    return heading;
}

/**
 * @brief Get the distance between this Pose2D and a given Pose2D
 * 
 * @param pose the other Pose2D to calculate the distance from
 * 
 * @return the distance between the poses in inches.
 */
Distance Pose2D::getDistance(Pose2D pose) {
    auto xDistance = this->x - pose.x;
    auto yDistance = this->y - pose.y;

    return Distance::fromIN(sqrt((xDistance*xDistance + yDistance*yDistance).asIN()));  
}

Angle Pose2D::getAngleTo(Pose2D pose) {
    auto xDistance = pose.x - this->x;
    auto yDistance = pose.y - this->y;

    return Angle::fromRad(atan2(xDistance.asIN(), yDistance.asIN())) - Angle::fromRad(atan2(x.asIN(), y.asIN()));
}

void Pose2D::setPolar(Distance radius, Angle theta) {
    setPose(radius * cos(theta.asRad()), radius * sin(theta.asRad()), theta);
}

void Pose2D::rotate(Angle angle) {
    double magnitude = sqrt((x*x).asIN() + (y*y).asIN());
    double theta = (atan2(x.asIN(), y.asIN()));

    theta += angle.asRad();

    setPolar(Distance::fromIN(magnitude), Angle::fromRad(theta));
}