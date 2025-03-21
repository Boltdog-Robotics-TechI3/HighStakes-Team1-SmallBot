#include "main.h"

class Pose2D {
    public: 
        double x;
        double y;
        double heading;

        public:
            Pose2D(double x, double y, double heading) {
                this->x = x;
                this->y = y;
                this->heading = heading;
            }

            Pose2D() {
                Pose2D(0, 0, 0);
            }

            void reset() { 
                x = 0;
                y = 0;
                heading = 0;
            }
            
            void setPose(double x, double y, double heading) {
                this->x = x;
                this->y = y;
                this->heading = heading;
            }

            void setPose(Pose2D pose) {
                this->x = pose.x;
                this->y = pose.y;
                this->heading = pose.heading;
            }


            /**
             * @brief Get 
             */
            double getX() {
                return x;
            } 

            double getY() {
                return y;
            }

            /**
             * @brief Get the distance between this Pose2D and a given Pose2D
             * 
             * @param pose the other Pose2D to calculate the distance from.a64l
             * 
             * @return the distance between the poses in inches.
             */
            double getDistance(Pose2D pose) {
                double xDistance = this->x - pose.x;
                double yDistance = this->y - pose.y;

                return sqrt(xDistance*xDistance + yDistance*yDistance);      
            }

        
};