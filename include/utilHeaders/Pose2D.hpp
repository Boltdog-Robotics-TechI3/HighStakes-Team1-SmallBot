#include "utilHeaders/Angle.hpp"
#include "utilHeaders/Distance.hpp"

/**
 * Class representing a 2D pose of the robot. It contains the x, y coordinates and the heading of the robot. 
 * x and y are constrained by the field size (-6ft to 6ft), and heading is constrained to be between 0 to 2π radians (0 to 360 degrees).
 */
class Pose2D {
    private: 
        Distance x;
        Distance y;
        Angle heading;

    public:
        /**
         * @brief Constructor for Pose2D.
         * 
         * @param x the x coordinate of the robot in inches
         * @param y the y coordinate of the robot in inches
         * @param heading the heading of the robot in radians
         */
        Pose2D(Distance x, Distance y, Angle heading);

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
        void setPose(Distance x, Distance y, Angle heading);

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
        Distance getX();

        /**
         * @brief Get the y coordinate
         * 
         * @return the y coordinate in inches
         */
        Distance getY(); 

        /**
         * @brief Get the heading
         * 
         * @return the heading in radians
         */
        Angle getHeading();

        /**
         * @brief Get the distance between this Pose2D and a given Pose2D
         * 
         * @param pose the other Pose2D to calculate the distance from
         * 
         * @return the distance between the poses in inches.
         */
        Distance getDistance(Pose2D pose);
};