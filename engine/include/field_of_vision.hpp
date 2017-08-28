#ifndef FIELD_OF_VISION_HPP
#define FIELD_OF_VISION_HPP

#include "line.hpp"
#include "animation_manager.hpp"
#include <vector>
#include <math.h>
#include "audio.hpp"

namespace engine{
    class FieldOfVision{
    public:
        FieldOfVision(double x, double y, int range, double total_angle);
        ~FieldOfVision();
        void updateCenter(double x, double y);
        void draw();
        void incrementAngle(double angle_increment);
        void setAngle(double angle);
        int getRange();
        void deactivate();
        int getAngle();
        bool isActive();
        std::vector<Line*> getLines();
        void playEffect();
    private:
        Line* center_line;
        Audio* catch_effect;
        std::vector<Line*> lines;
        std::pair<double,double> center;
        void resetLines();
        void createLines(double x, double y, int range);
        int range;
        double total_angle;
        int number_of_lines;
        bool active;
    };
}
#endif
