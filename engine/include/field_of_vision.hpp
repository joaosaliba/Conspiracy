/**
 * @file progress_bar.cpp
 * @brief class to object of progress_bar, where you can find some values, files,
 * others objects used in this class and methods to the same.
 * @copyright  GNU GENERAL PUBLIC LICENSE.
 */

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

        int getRange();


        int getAngle();
        void setAngle(double angle);
        void incrementAngle(double angle_increment);

        bool isActive();
        void deactivate();

        std::vector<Line*> getLines();

        void play_effect();
    private:
        Audio* catch_effect;

        bool active;
        int number_of_lines;

        std::pair<double,double> center;
        Line* center_line;
        std::vector<Line*> lines;

        void resetLines();
        void createLines(double x, double y, int range);

        int range;
        double total_angle;
    };
}
#endif
