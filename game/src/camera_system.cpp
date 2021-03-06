
/**
 *   @file camera_system.cpp
 *    @brief Manage the camera system in the game and creat the relationship between camera lever and came switch.
 *    @copyright  GNU GENERAL PUBLIC LICENSE.
 */
 #include "camera_system.hpp"
 #include <assert.h>
 //#define NDEBUG *uncomment to disable assertions

using namespace engine;
/**
 *    @brief Camemera system object constructor.
 *    @param[in] p_camera it sets camera pointer.
 *    @param[in] p_camera_switch it sets the camera switch pointer.
 *
 */

CameraSystem::CameraSystem(Camera* p_camera, CameraSwitch* p_camera_switch){
    camera = p_camera;
    camera_switch = p_camera_switch;
    camera_lever = NULL;
    last_lever_state = 1;
    INFO("Constructor CameraSystem");
}

/**
 *    @brief Camemera system object constructor.
 *    @param[in] p_camera it sets camera pointer.
 *    @param[in] p_camera_switch it sets the camera switch pointer.
 *     @param[in] p_camera_lever it sets the camera lever pointer
 */

CameraSystem::CameraSystem(Camera* p_camera, CameraSwitch* p_camera_switch, CameraLever* p_camera_lever){
    camera = p_camera;
    camera_switch = p_camera_switch;
    camera_lever = p_camera_lever;
    INFO("Constructor CameraSystem");
}

/**
 *   @brief draws the animation of the Camera System according to its position
 *   @return void
 */
void CameraSystem::draw(){
    assert ( timeElapsed != NULL);
    camera->draw();
    camera_switch->draw();
    if(camera_lever != NULL){
        camera_lever->draw();
    }
    else{
      //nothing to do
    }
    INFO("draw CameraSystem");
}

/**
*    @brief update the camera system  decoring the time.
*    @param[in] timeElapsed its about the time
*/
void CameraSystem::update(double timeElapsed){
  assert(last_lever_state > –2147483648 || last_lever_state < 2147483648);
    camera->update(timeElapsed);
    camera_switch->update(timeElapsed);
    if(camera_lever != NULL){
     camera_lever->update(timeElapsed);
        if(camera_lever->getState() != last_lever_state){
            last_lever_state = camera_lever->getState();
            camera->changeState(camera_lever->getState());
        }
        else{
          // nothing to do
        }
    }
    else{
      // nothing to do
    }
    if(!camera_switch->isWorking() && camera->isTurnedOn()){
         camera->turnOff();
    }
    else{
      // nothing to do
    }
    INFO("update CameraSystem");
}


/**
 *   @brief get the actual camera system
 *   @return camera switch
 */

CameraSwitch* CameraSystem::getCameraSwitch(){
  if (camera_switch == NULL){
    ERROR("Failed to start window manager");
      exit(-1);
  }
  else{
    return camera_switch;
  }
  INFO("Get System in CameraSystem");
}
/**
 *   @brief   get the actual camera system
 *   @return camera
 */
Camera* CameraSystem::getCamera(){
  if (camera == NULL){
    ERROR("Failed to start window manager");
      exit(-1);
  }
  else{
    return camera;
  }
  INFO("getCamera CameraSystem");
}

/**
 *   @brief  get the actual camera lever
 *   @return camera
 */
CameraLever* CameraSystem::getCameraLever(){
  if (camera_lever == NULL){
    ERROR("Failed to start window manager");
      exit(-1);
  }
  else{
    return camera_lever;
  }
  INFO("Get Camera lerver in CameraSystem");
}
