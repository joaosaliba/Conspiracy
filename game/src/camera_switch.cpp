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
 *    @param[in] position_x it sets the x coordinate of the object.
 *    @param[in] position_y it sets the y coordinate of the object.
 *    @param[in] width it sets the width dimension of the object.
 *    @param[in] height it sets the height dimension of the object.
 *    @param[in] direction set the new direct of the camera lever
 *
 */
CameraSwitch::CameraSwitch(double position_x, double position_y, std::string direction) : GameObject(FILENAME,position_x - ADJUSTX,position_y - ADJUSTX,
                                                                     WIDTH+ADJUSTX*DOUBLE, HEIGHT+ADJUSTX*DOUBLE){
    assert ( position_x != NULL);
    assert ( position_y != NULL);
    animator = new Animation(FILENAME, 1, 2, 0.1);
    switchEfffect = new Audio("assets/sounds/turn_offCAMERA.wav", "EFFECT", 128);

    animator->add_action("on", 0,0);
    animator->add_action("off",1,1);
    animator->set_interval("on");
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
    animator->draw_instant(get_position_x()+ADJUSTX, get_position_y()+ADJUSTX);
    animator->draw_collider(get_position_x(), get_position_y(), get_width(), get_height());
    INFO("draw CameraSwitch");
}
/**
*    @brief update the camera switch  decoring the time.
*    @param[in] time_elapsed its about the time
*/
void CameraSwitch::update(double time_elapsed){
    assert ( time_elapsed != NULL);
    time_elapsed = time_elapsed;
    animator->update();
    INFO("update CameraSwitch");
}

/**
*    @brief change the camera switch to off.
*/
void CameraSwitch::turn_off(){
    if(animator->getInterval().first!="off"){
        working = false;
        animator->set_interval("off");
        switchEfffect->play(0);
    }
    else{
      //nothing to do
    }
    INFO("Turn Off CameraSwitch");
}
