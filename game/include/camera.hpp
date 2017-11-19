#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "engine.hpp"
#include "input_manager.hpp"
#include "animation.hpp"
#include "enemy.hpp"
#include "field_of_vision.hpp"

using namespace engine;

class Camera: public Enemy{
public:
    Camera(double position_x, double position_y, std::string direction);
    Camera(double position_x, double position_y, std::string direction, int angleOfVision, int range, int initialAngle);
    ~Camera();
    void update(double time_elapsed);
    void draw();
    int getRange();
    void turn_off();
    bool isTurnedOn();
    void setStates(int angle2, int angle3);
    void changeState(int state);
    FieldOfVision* getFieldOfVision();
private:
    void initializeVision(int p_range, int p_angleOfVision, std::string direction);
    void initializeAnimator(std::string filename);
    int range;
    bool turnedOn;
    std::vector<int> angles;
    int angleOfVision;
    int initialAngle;
    int state;
    FieldOfVision* fieldOfVision;
    Animation* animator;
};

#endif
