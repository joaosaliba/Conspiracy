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
    CameraSwitch(double position_x, double position_y, std::string direction);
    ~CameraSwitch();
    void update(double time_elapsed);
    void draw();
    bool isWorking();
    void turn_off();
private:
    Audio* switchEfffect = nullptr;
    Animation* animator = nullptr;
    bool working;
};

#endif
