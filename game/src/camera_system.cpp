#include "camera_system.hpp"

using namespace engine;

CameraSystem::CameraSystem(Camera* p_camera, CameraSwitch* p_cameraSwitch){
    camera = p_camera;
    camera_switch = p_cameraSwitch;
    camera_lever = NULL;
    last_lever_state = 1;
}

CameraSystem::CameraSystem(Camera* p_camera, CameraSwitch* p_cameraSwitch,
                           CameraLever* p_cameraLever) {

    camera = p_camera;
    camera_switch = p_cameraSwitch;
    camera_lever = p_cameraLever;
}

void CameraSystem::update(double timeElapsed) {
    camera->update(timeElapsed);
    camera_switch->update(timeElapsed);

    if(camera_lever != NULL) {
        camera_lever->update(timeElapsed);
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
