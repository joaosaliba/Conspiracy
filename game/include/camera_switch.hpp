#ifndef CAMERA_SWITCH_HPP
#define CAMERA_SWITCH_HPP

#include "engine.hpp"
#include "audio.hpp"

using namespace engine;

/**
* the class camera_switch recive an camera_switch public class where the parameters to be defined
* received, such as position, type, and methods. The attributes that will be defined
*public,private and protected
*/

class CameraSwitch: public GameObject{
public:
    CameraSwitch(double positionX, double positionY, std::string direction);
    ~CameraSwitch();
    void update(double timeElapsed);
    void draw();
    bool isWorking();
    void turnOff();
private:
    Audio* switchEfffect = nullptr;
    Animation* animator = nullptr;
    bool working;
};

#endif
