#include "main.h"

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
Pose2D::Pose2D(double x, double y, double heading) {
    setPose(x, y, heading);
}

/**
 * @brief Default constructor for Pose2D.
 * Sets the x, y, and heading to 0
 */     
Pose2D::Pose2D() {
    Pose2D(0, 0, 0);
}

/**
 * @brief Resets the pose of the robot to (0, 0, 0)
 */     
void Pose2D::reset() { 
    setPose(0, 0, 0);
}

/**
 * @brief Set the pose of the robot
 * 
 * @param x the new x coordinate of the robot in inches
 * @param y the new y coordinate of the robot in inches
 * @param heading the new heading of the robot in radians
 */
void Pose2D::setPose(double x, double y, double heading) {
    this->x = x;
    this->y = y;
    this->heading = heading;

    std::clamp(this->x, -72.0, 72.0);
    std::clamp(this->y, -72.0, 72.0);
    std::clamp(this->heading, 0.0, 2 * M_PI);

    pros::Task::notify();
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
double Pose2D::getX() {
    while (pros::Task::notify_take(true, 500));
    return x;
} 

/**
 * @brief Get the y coordinate
 * 
 * @return the y coordinate in inches
 */
double Pose2D::getY() {
    while (pros::Task::notify_take(true, 500));
    return y;
}

/**
 * @brief Get the heading
 * 
 * @return the heading in radians
 */
double Pose2D::getHeading() {
    while (pros::Task::notify_take(true, 500)):
    return heading;
}

/**
 * @brief Get the distance between this Pose2D and a given Pose2D
 * 
 * @param pose the other Pose2D to calculate the distance from
 * 
 * @return the distance between the poses in inches.
 */
double Pose2D::getDistance(Pose2D pose) {
    double xDistance = this->x - pose.x;
    double yDistance = this->y - pose.y;

    return sqrt(xDistance*xDistance + yDistance*yDistance);  
    

}

void Pose2D::trackPose(void *param){
    while(pros::Task::notify){
        
    }
}
