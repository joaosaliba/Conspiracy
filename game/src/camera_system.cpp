#include "camera_system.hpp"

using namespace engine;

CameraSystem::CameraSystem(Camera* p_camera, CameraSwitch* p_camera_switch){
    camera = p_camera;
    camera_switch = p_camera_switch;
    camera_lever = NULL;
    last_lever_state = 1;
}

CameraSystem::CameraSystem(Camera* p_camera, CameraSwitch* p_camera_switch,
                           CameraLever* p_camera_lever) {

    camera = p_camera;
    camera_switch = p_camera_switch;
    camera_lever = p_camera_lever;
}

void CameraSystem::update(double time_elapsed) {
    camera->update(time_elapsed);
    camera_switch->update(time_elapsed);

    if(camera_lever != NULL) {
        camera_lever->update(time_elapsed);
        if(camera_lever->getState() != last_lever_state) {
            last_lever_state = camera_lever->getState();
            camera->changeState(camera_lever->getState());
        }
    }
    if(!camera_switch->isWorking() && camera->isTurnedOn()){
       camera->turnOff();
    }
}
void CameraSystem::draw() {
    camera->draw();
    camera_switch->draw();

    if(camera_lever != NULL) {
       camera_lever->draw();
    }
}
Camera* CameraSystem::getCamera() {
    return camera;
}

CameraSwitch* CameraSystem::getCameraSwitch() {
    return camera_switch;
}

CameraLever* CameraSystem::getCameraLever() {
    return camera_lever;
}
