/**
 *   @file camera_switch.cpp
 *    @brief Manage the camera switch in the game.
 *    @copyright  GNU GENERAL PUBLIC LICENSE.
 */
#include "camera_switch.hpp"
#include <assert.h>
//#define NDEBUG *uncomment to disable assertions

using namespace engine;
#define FILENAME "assets/sprites/cenary/switch_cameras(14X16).png"
#define WIDTH 14 //  define the width to 14
#define HEIGHT 16 //  define the height to 16
#define ADJUSTX 10 // deine the variable adjustx to 10
#define DOUBLE 2
/**
 *    @brief Camemera switch object constructor.
 *    @param[in] positionX it sets the x coordinate of the object.
 *    @param[in] positionY it sets the y coordinate of the object.
 *    @param[in] width it sets the width dimension of the object.
 *    @param[in] height it sets the height dimension of the object.
 *    @param[in] direction set the new direct of the camera lever
 *
 */
CameraSwitch::CameraSwitch(double positionX, double positionY, std::string direction) : GameObject(FILENAME,positionX - ADJUSTX,positionY - ADJUSTX,
                                                                     WIDTH+ADJUSTX*DOUBLE, HEIGHT+ADJUSTX*DOUBLE){
    assert ( positionX != NULL);
    assert ( positionY != NULL);
    animator = new Animation(FILENAME, 1, 2, 0.1);
    switchEfffect = new Audio("assets/sounds/TURNOFFCAMERA.wav", "EFFECT", 128);

    animator->addAction("on", 0,0);
    animator->addAction("off",1,1);
    animator->setInterval("on");
    direction = direction;
    working = true;
    INFO("Constructor CameraSwitch");
}
/**
*    @brief check the camera switch if it working.
*/
bool CameraSwitch::isWorking(){
  return working;
  INFO("Check if working CameraSwitch");
}
/**
 *   @brief draws the animation of the button according to its position
 *   @return void
 */
void CameraSwitch::draw(){
    animator->draw_instant(getPositionX()+ADJUSTX, getPositionY()+ADJUSTX);
    animator->draw_collider(getPositionX(), getPositionY(), getWidth(), getHeight());
    INFO("draw CameraSwitch");
}
/**
*    @brief update the camera switch  decoring the time.
*    @param[in] timeElapsed its about the time
*/
void CameraSwitch::update(double timeElapsed){
    assert ( timeElapsed != NULL);
    timeElapsed = timeElapsed;
    animator->update();
    INFO("update CameraSwitch");
}

/**
*    @brief change the camera switch to off.
*/
void CameraSwitch::turnOff(){
    if(animator->getInterval().first!="off"){
        working = false;
        animator->setInterval("off");
        switchEfffect->play(0);
    }
    else{
      //nothing to do
    }
    INFO("Turn Off CameraSwitch");
}
