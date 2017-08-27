#include "camera.hpp"


#define FILENAME "assets/sprites/camera(11X8).png"
#define WIDTH 11
#define HEIGHT 8

Camera::Camera(double positionX, double positionY, std::string direction) : Enemy(FILENAME,positionX,positionY,
                                                                     WIDTH, HEIGH){
    initializeAnimator(FILENAME);
    animator->setInterval(direction);
    turnedOn = true;
    int default_range = 180;
    int default_angleOfVision = 80;

    initializeVision(default_range, default_angle_of_vision, direction);
}

Camera::Camera(double positionX, double positionY, std::string direction,
               int p_angle_of_vision, int p_range, int p_initial_angle): Enemy(FILENAME,positionX,positionY,
                                                                    WIDTH, HEIGH){
    initializeAnimator(FILENAME);
    animator->setInterval(direction);
    turnedOn = true;

    initializeVision(Prange, p_angle_of_vision, direction);
    if(p_initial_angle != -1){
        initial_angle = p_initial_angle;
        fieldOfVision->setAngle(initial_ngle);
    }
}

Camera::~Camera(){
}

void Camera::turnOff(){
    turnedOn = false;
    fieldOfVision->deactivate();
}

bool Camera::isTurnedOn(){
    return turnedOn;
}

void Camera::update(double timeelapsed){
    time_elapsed = time_elapsed;
    animator->update();
}

void Camera::draw(){
    animator->draw(getPositionX(), getPositionY());
    animator->draw_collider(getPositionX(), getPositionY(), getWidth(), getHeight());
    fieldOfVision->draw();
}

void Camera::initializeAnimator(std::string FILENAME){
    state = 1;
    animator = new Animation(FILENAME, 2, 4, 0.1);
    animator->addAction("right",0,0);
    animator->addAction("left",2,2);
    animator->addAction("upright",4,4);
    animator->addAction("upleft",6,6);
}

void Camera::initializeVision(int prange, int p_angle_of_vision, std::string direction){
    range = Prange;
    angleOfVision = p_angle_of_vision;

    if(direction == "right"){
        fieldOfVision = new FieldOfVision(getPositionX()+4+getWidth()/2,getPositionY()+7, range, angleOfVision);
        initialAngle = 305;
    }else if(direction  == "left"){
        fieldOfVision = new FieldOfVision(getPositionX()-4+getWidth()/2,getPositionY()+7, range, angleOfVision);
        initialAngle = 220;
    }else if(direction == "upleft"){
        fieldOfVision = new FieldOfVision(getPositionX()-6+getWidth()/2,getPositionY(), range, angle_of_vision);
        initialAngle = 140;
    }else{
        fieldOfVision = new FieldOfVision(getPositionX()+5+getWidth()/2,getPositionY(), range, angleOfVision);
        initialAngle = 45;
    }
    fieldOfVision->setAngle(initialAngle);
}
void Camera::setStates(int angle_2, int angle_3){
    angles.push_back(angle2);
    angles.push_back(initial_angle);
    angles.push_back(angle_3);
}

void Camera::changeState(int p_state){
    fieldOfVision->setAngle(angles[p_state]);
}

int Camera::getRange(){
    return range;
}

FieldOfVision* Camera::getFieldOfVision(){
    return field_of_vision;
}
