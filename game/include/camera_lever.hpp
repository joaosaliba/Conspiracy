#ifndef CAMERA_LEVER_HPP
#define CAMERA_LEVER_HPP

#include "engine.hpp"

using namespace engine;
/**
*objective : this class is responsable to instace  the variables 
* for being used in camera_lever cpp
*/
class CameraLever: public GameObject{
public:
    CameraLever(double camera_lever_position_x, double camera_lever_position_y, std::string camera_lever_direction);
    ~CameraLever();
    void update(double timeElapsed);// update the camera lever durign time
    void draw();// draw the lever of camerar
    int getState();
    void nextState(); //  references for the camera lever state
private:
    Animation* animator;
    int state;
    int stateInc;
};

#endif
