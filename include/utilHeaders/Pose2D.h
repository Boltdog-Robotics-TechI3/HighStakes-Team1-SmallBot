#include "main.h"

/**
 * Class representing a 2D pose of the robot. It contains the x, y coordinates and the heading of the robot. 
 * x and y are constrained by the field size (-6ft to 6ft), and heading is constrained to be between 0 and 360 degrees.
 */
class Pose2D {
    private: 
        double x;
        double y;
        double heading;

    public:
        /**
         * @brief Constructor for Pose2D.
         * 
         * @param x the x coordinate of the robot in inches
         * @param y the y coordinate of the robot in inches
         * @param heading the heading of the robot in radians
         */
        Pose2D(double x, double y, double heading);

        /**
         * @brief Default constructor for Pose2D.
         * Sets the x, y, and heading to 0
         */
        Pose2D();

        /**
         * @brief Resets the pose of the robot to (0, 0, 0)
         */
        void reset();

        /**
         * @brief Set the pose of the robot
         * 
         * @param x the new x coordinate of the robot in inches
         * @param y the new y coordinate of the robot in inches
         * @param heading the new heading of the robot in radians
         */
        void setPose(double x, double y, double heading);

        /**
         * @brief Set the pose of the robot
         * 
         * @param pose the new pose of the robot
         */
        void setPose(Pose2D pose);

        /**
         * @brief Get the x coordinate
         * 
         * @return the x coordinate in inches
         */
        double getX();

        /**
         * @brief Get the y coordinate
         * 
         * @return the y coordinate in inches
         */
        double getY(); 

        /**
         * @brief Get the heading
         * 
         * @return the heading in radians
         */
        double getHeading();

        /**
         * @brief Get the distance between this Pose2D and a given Pose2D
         * 
         * @param pose the other Pose2D to calculate the distance from
         * 
         * @return the distance between the poses in inches.
         */
        double getDistance(Pose2D pose);

        void trackPose(void *param);
};