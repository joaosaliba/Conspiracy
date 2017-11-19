#include "camera.hpp"


#define FILENAME "assets/sprites/camera(11X8).png"
#define WIDTH 11
#define HEIGHT 8

Camera::Camera(double position_x, double position_y, std::string direction) : Enemy(FILENAME,position_x,position_y,
                                                                     WIDTH, HEIGHT){
    initializeAnimator(FILENAME);
    animator->set_interval(direction);
    turnedOn = true;
    int default_range = 180;
    int default_angleOfVision = 80;

    initializeVision(default_range, default_angleOfVision, direction);
}

Camera::Camera(double position_x, double position_y, std::string direction,
               int p_angleOfVision, int p_range, int p_initialAngle): Enemy(FILENAME,position_x,position_y,
                                                                     WIDTH, HEIGHT){
    initializeAnimator(FILENAME);
    animator->set_interval(direction);
    turnedOn = true;

    initializeVision(p_range, p_angleOfVision, direction);
    if(p_initialAngle != -1){
        initialAngle = p_initialAngle;
        fieldOfVision->setAngle(initialAngle);
    }
}

Camera::~Camera(){
}

void Camera::turn_off(){
    turnedOn = false;
    fieldOfVision->deactivate();
}

bool Camera::isTurnedOn(){
    return turnedOn;
}

void Camera::update(double timeElapsed){
    timeElapsed = timeElapsed;
    animator->update();
}

void Camera::draw(){
    animator->draw(get_position_x(), get_position_y());
    animator->draw_collider(get_position_x(), get_position_y(), get_width(), get_height());
    fieldOfVision->draw();
}

void Camera::initializeAnimator(std::string filename){
    state = 1;
    animator = new Animation(filename, 2, 4, 0.1);
    animator->add_action("right",0,0);
    animator->add_action("left",2,2);
    animator->add_action("upright",4,4);
    animator->add_action("upleft",6,6);
}

void Camera::initializeVision(int p_range, int p_angleOfVision, std::string direction){
    range = p_range;
    angleOfVision = p_angleOfVision;

    if(direction == "right"){
        fieldOfVision = new FieldOfVision(get_position_x()+4+get_width()/2,get_position_y()+7, range, angleOfVision);
        initialAngle = 305;
    }else if(direction  == "left"){
        fieldOfVision = new FieldOfVision(get_position_x()-4+get_width()/2,get_position_y()+7, range, angleOfVision);
        initialAngle = 220;
    }else if(direction == "upleft"){
        fieldOfVision = new FieldOfVision(get_position_x()-6+get_width()/2,get_position_y(), range, angleOfVision);
        initialAngle = 140;
    }else{
        fieldOfVision = new FieldOfVision(get_position_x()+5+get_width()/2,get_position_y(), range, angleOfVision);
        initialAngle = 45;
    }
    fieldOfVision->setAngle(initialAngle);
}
void Camera::setStates(int angle2, int angle3){
    angles.push_back(angle2);
    angles.push_back(initialAngle);
    angles.push_back(angle3);
}

void Camera::changeState(int p_state){
    fieldOfVision->setAngle(angles[p_state]);
}

int Camera::getRange(){
    return range;
}

FieldOfVision* Camera::getFieldOfVision(){
    return fieldOfVision;
}
