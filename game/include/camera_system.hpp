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

    Camera* getCamera();
    CameraLever* getCameraLever();
    CameraSwitch* getCameraSwitch();
private:
  void update(double time_elapsed);
  void draw();
    Camera* camera = nullptr; // creat a objecte from camera
    CameraSwitch* camera_switch = nullptr;// creat a objecte from camera_switch
    CameraLever* camera_lever = nullptr; // creat a objecte from camera_lever
    int last_lever_state; //  creat a variable  that saves the last lever state
};

#endif
