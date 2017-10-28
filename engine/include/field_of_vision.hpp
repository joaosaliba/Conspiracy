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

        int get_range();


        int get_angle();
        void set_angle(double angle);
        void increment_angle(double angle_increment);

        bool is_active();
        void deactivate();

        std::vector<Line*> get_lines();

        void play_effect();
    private:
        Audio* catch_effect;

        bool active;
        int number_of_lines;
        std::pair<double,double> center;
        Line* center_line;
        std::vector<Line*> lines;
        void reset_lines();
        void create_lines(double x, double y, int range);

        int range;
        double total_angle;
    };
}
#endif
