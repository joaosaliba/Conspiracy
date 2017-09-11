/**class to object of field_of_vision, where you can find some variables, files, others objects
 *and meths to the same.
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
        void update_center(double x, double y);
        void draw();
        void increment_angle(double angle_increment);
        void set_angle(double angle);
        int get_range();
        void deactivate();
        int get_angle();
        bool is_active();
        std::vector<Line*> get_lines();
        void play_effect();
    private:
        Line* center_line;
        Audio* catch_effect;
        std::vector<Line*> lines;
        std::pair<double,double> center;
        void reset_lines();
        void create_lines(double x, double y, int range);
        int range;
        double total_angle;
        int number_of_lines;
        bool active;
    };
}
#endif
