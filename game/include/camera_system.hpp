#ifndef CAMERA_SYSTEM_HPP
#define CAMERA_SYSTEM_HPP

#include "camera.hpp"
#include "camera_switch.hpp"
#include "camera_lever.hpp"

using namespace engine;

class CameraSystem: public GameObject{
public:
    CameraSystem(Camera* camera, CameraSwitch* camera_switch);
    CameraSystem(Camera* camera, CameraSwitch* camera_switch, CameraLever* camera_lever);
    ~CameraSystem();
    void update(double timeElapsed);
    void draw();
    Camera* getCamera();
    CameraLever* getCameraLever();
    CameraSwitch* getCameraSwitch();
private:
    Camera* camera;
    CameraSwitch* camera_switch;
    CameraLever* camera_lever;
    int lastLeverState;
};

#endif
