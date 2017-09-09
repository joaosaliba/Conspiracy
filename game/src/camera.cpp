#include "camera.hpp"


#define FILENAME "assets/sprites/camera(11X8).png"
#define WIDTH 11
#define HEIGHT 8

/**class to object of camera, where you can find some values and meths to the same.
 *
 */

Camera::Camera(double position_x, double position_y, std::string direction) : Enemy(FILENAME,position_x,position_y,
                                                                 WIDTH, HEIGHT){
    initialize_animator(FILENAME);
    animator->set_interval(direction);
    turned_on = true;
    int default_range = 180;
    int default_angle_of_vision = 80;

    initialize_vision(default_range, default_angle_of_vision, direction);
}

Camera::Camera(double position_x, double position_y, std::string direction,
               int p_angle_of_vision, int p_range, int p_initial_angle): Enemy(FILENAME,position_x,
                                                                     position_y,
                                                                     WIDTH, HEIGHT){
    initialize_animator(FILENAME);
    animator->set_interval(direction);
    turned_on = true;

    initialize_vision(p_range, p_angle_of_vision, direction);
    if(p_initial_angle != -1){
        initial_angle = p_initial_angle;
        fieldOfVision->set_angle(initial_angle);
    }
}

Camera::~Camera() {
}

void Camera::turn_off() {
    turned_on = false;
    fieldOfVision->deactivate();
}

bool Camera::is_turned_on() {
    return turned_on;
}

void Camera::update(double time_elapsed) {
    time_elapsed = time_elapsed;
    animator->update();
}

void Camera::draw() {
    animator->draw(get_position_x(), get_position_y());
    animator->draw_collider(get_position_x(), get_position_y(), get_width(), get_height());
    fieldOfVision->draw();
}

void Camera::initialize_animator(std::string filename) {
    state = 1;
    animator = new Animation(filename, 2, 4, 0.1);
    animator->add_animation("right",0,0);
    animator->add_animation("left",2,2);
    animator->add_animation("upright",4,4);
    animator->add_animation("upleft",6,6);
}

void Camera::initialize_vision(int p_range, int p_angle_of_vision, std::string direction) {
    range = p_range;
    angle_of_vision = p_angle_of_vision;

    if(direction == "right") {
        fieldOfVision = new fieldOfVision(get_position_x()+4+get_width()/2,get_position_y()+7, range, angle_of_vision);
        initial_angle = 305;
    }else if(direction  == "left") {
        fieldOfVision = new fieldOfVision(get_position_x()-4+get_width()/2,get_position_y()+7, range, angle_of_vision);
        initial_angle = 220;
    }else if(direction == "upleft") {
        fieldOfVision = new fieldOfVision(get_position_x()-6+get_width()/2,get_position_y(), range, angle_of_vision);
        initial_angle = 140;
    }else {
        fieldOfVision = new fieldOfVision(get_position_x()+5+get_width()/2,get_position_y(), range, angle_of_vision);
        initial_angle = 45;
    }
    fieldOfVision->set_angle(initial_angle);
}
void Camera::set_states(int angle2, int angle3) {
    angles.push_back(angle2);
    angles.push_back(initial_angle);
    angles.push_back(angle3);
}

void Camera::change_state(int p_state){
    fieldOfVision->set_angle(angles[p_state]);
}

int Camera::get_range(){
    return range;
}

fieldOfVision* Camera::get_fieldOfVision(){
    return fieldOfVision;
}
