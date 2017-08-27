#include "field_of_vision.hpp"

using namespace engine;

FieldOfVision::FieldOfVision(double x, double y, int size, double angle){
    range = size;
    total_angle = angle;

    catch_effect = new Audio("assets/sounds/GUARDAVIU.wav", "EFFECT", 128);
    active = true;
    //not including centerLine
    number_of_lines = 10;
    createLines(x,y,range);
}
int FieldOfVision::getAngle(){
    return center_line->getAngle();
}
void FieldOfVision::resetLines(){
    //free(centerLine);
    for(auto line: lines){
        free(line);
    }
    lines.clear();
}

void FieldOfVision::deactivate(){
    active = false;
}
bool FieldOfVision::isActive(){
    return active;
}

void FieldOfVision::createLines(double x, double y, int size){
    resetLines();
    center_line = new Line(x,y,size, 0);

    double angle_inc = ((double)total_angle/2.0)/((double)number_of_lines/2.0);
    for(double i = 0, line_angle = angle_inc; i<number_of_lines/2; i+=1, line_angle += angle_inc) {
        Line* new_upper_line = new Line(center_line);
        new_upper_line->rotateLine(line_angle);
        lines.push_back(new_upper_line);

        Line* new_lower_line = new Line(center_line);
        new_lower_line->rotateLine(-line_angle);
        lines.push_back(new_lower_line);
    }
}
void FieldOfVision::updateCenter(double inc_x, double inc_y){
    center_line->updatePosition(inc_x,inc_y);
    for(auto line: lines){
        line->updatePosition(inc_x,inc_y);
    }
}

void FieldOfVision::draw(){
    if(active){
        AnimationManager::instance.addFieldOfVision(this);
    }
}

void FieldOfVision::incrementAngle(double angle){
    center_line->rotateLine(angle);
    for(auto line:lines){
        line->rotateLine(angle);
    }
}

void FieldOfVision::setAngle(double angle){
    center_line->changeAngleTo(angle);
    double angle_inc = ((double)total_angle/2.0)/((double)number_of_lines/2.0);

    double line_angle = angle;
    int i = 0;
    bool inverteu = false;
    for(auto line:lines){
        if(i >= number_of_lines/2 && !inverteu){
            line_angle = angle;
            angle_inc *= (-1);
            inverteu = true;
        }
        line_angle -= angle_inc;
        line->changeAngleTo(line_angle);
        i++;
    }
}

std::vector<Line*> FieldOfVision::getLines(){
    std::vector<Line*> lines_return;
    lines_return.push_back(center_line);
    for(auto line:lines){
        lines_return.push_back(line);
    }
    return lines_return;
}

int FieldOfVision::getRange(){
    return range;
}

void FieldOfVision::playEffect(){
    catch_effect->play(0);
}
