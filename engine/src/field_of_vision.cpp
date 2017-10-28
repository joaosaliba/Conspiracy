/**class to object of field_of_vision, where you can find some variables, files, others objects
 *and meths to the same.
 */

#include "field_of_vision.hpp"

using namespace engine;

FieldOfVision::FieldOfVision(double x, double y, int size, double angle) {
    range = size;
    total_angle = angle;

    catch_effect = new Audio("assets/sounds/GUARDAVIU.wav", "EFFECT", 128);
    active = true;
    //not including center_line
    number_of_lines = 10;
    create_lines(x,y,range);
}
int FieldOfVision::get_angle() {
    return center_line->get_angle();
}
void FieldOfVision::reset_lines() {
    //free(center_line);
    for(auto line: lines) {
        free(line);
    }
    lines.clear();
}

void FieldOfVision::deactivate() {
    active = false;
}
bool FieldOfVision::is_active() {
    return active;
}

void FieldOfVision::create_lines(double x, double y, int size) {
    reset_lines();
    center_line = new Line(x,y,size, 0);

    double angle_inc = ((double)total_angle/2.0)/((double)number_of_lines/2.0);
    for(double i = 0, line_angle = angle_inc; i<number_of_lines/2; i+=1, line_angle += angle_inc) {
        Line* new_upper_line = new Line(center_line);
        new_upper_line->rotate_line(line_angle);
        lines.push_back(new_upper_line);

        Line* new_lower_line = new Line(center_line);
        new_lower_line->rotate_line(-line_angle);
        lines.push_back(new_lower_line);
    }
}
void FieldOfVision::update_center(double inc_x, double inc_y) {
    center_line->update_position(inc_x,inc_y);
    for(auto line: lines) {
        line->update_position(inc_x,inc_y);
    }fiel
}

void FieldOfVision::draw() {
    if(active) {
        AnimationManager::instance.addFieldOfVision(this);
    }
}

void FieldOfVision::increment_angle(double angle) {
    center_line->rotate_line(angle);
    for(auto line:lines) {
        line->rotate_line(angle);
    }
}

void FieldOfVision::set_angle(double angle) {
    center_line->change_angle_to(angle);
    double angle_inc = ((double)total_angle/2.0)/((double)number_of_lines/2.0);

    double line_angle = angle;
    int i = 0;
    bool inverteu = false;
    for(auto line:lines) {

        if(i >= number_of_lines/2 && !inverteu) {
            line_angle = angle;
            angle_inc *= (-1);
            inverteu = true;
        }

        line_angle -= angle_inc;
        line->change_angle_to(line_angle);
        i++;
    }
}

std::vector<Line*> FieldOfVision::get_lines() {

    std::vector<Line*> lines_return;
    lines_return.push_back(center_line);

    for(auto line:lines) {
        lines_return.push_back(line);
    }

    return lines_return;
}

int FieldOfVision::get_range() {
    return range;
}

void FieldOfVision::play_effect() {
    catch_effect->play(0);
}
