#include "main.h"

/** 
 *  A class representation of a tracking wheel. 
 */

class TrackingWheel {
    private:
        double wheelDiameter; // inches
        int wheelOrientation; // 0 for horizontal, 1 for vertical, 2 for diagonal
        pros::Rotation encoder; // The rotation sensor object representing the encoder for the wheel
        Pose2D offset; // A pose2D object representing the offset of the wheel from the tracking center of the robot

    public:
        /**
         * Creates a new tracking wheel object.
         * 
         * @param rotationSensorPort the port ID of the rotation sensor representing the encoder for the wheel
         * @param offset the offset of the wheel from the tracking center of the robot as a Pose2D object. Left/Backwards is negative, Forwards/Right is positive. 0 radians is a horizontal wheel, π/2 radians is a vertical wheel, and any other angle is a diagonal wheel.
         * @param wheelDiameter the diameter of the wheel in inches
         */
        TrackingWheel(int rotationSensorPort, Pose2D offset, double wheelDiameter);

        /**
         * Gets the distance the wheel has turned from its starting position in wheel rotations
         * 
         * @return the distance the wheel has turned in wheel rotations
         */
        double getWheelRotations(); // rotations

        /**
         * Gets the distance the wheel has turned from its starting position in inches
         * 
         * @return the distance the wheel has turned in inches
         */
        double getWheelDistance(); // inches

        /**
         * Get the x coordinate of the wheel offset from the tracking center of the robot in inches (positive is right, negative is left)
         * 
         * @return the x coordinate of the wheel offset in inches
         */
        double getWheelOffsetX(); // inches

        /**
         * Get the y coordinate of the wheel offset from the tracking center of the robot in inches (positive is forwards, negative is backwards)
         * 
         * @return the y coordinate of the wheel offset in inches
         */
        double getWheelOffsetY(); // inches

        /**
         * Get the angle of the tracking wheel in radians (0 radians is horizontal, π/2 radians is vertical, and any other angle is diagonal)
         * 
         * @return the angle of the wheel offset in radians
         */
        double getWheelOffsetAngle(); // radians




};