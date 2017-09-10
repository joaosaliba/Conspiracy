#ifndef CAMERA_SYSTEM_HPP
#define CAMERA_SYSTEM_HPP

#include "camera.hpp"
#include "camera_switch.hpp"
#include "camera_lever.hpp"

using namespace engine;
/**Class responsable to the camera object system,
*where you can find some values and meth to the same
*/

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
    int last_lever_state;
};

#endif
