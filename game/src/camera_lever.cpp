/**
 *   @file camera_lever.cpp
 *    @brief Manage the camera lever in the game.
 *    @copyright  GNU GENERAL PUBLIC LICENSE.
 */

#include "camera_lever.hpp"
#include <assert.h>

using namespace engine;

#define FILENAME "assets/sprites/cenary/alavanca_sheet(17X20).png"
#define WIDTH 20 // define the valor of the width like 20
#define HEIGHT 20// define the valor of the height like 20
/**
 *    @brief Camemera lever object constructor.
 *    @param[in] camera_lever_position_x it sets the x coordinate of the object.
 *    @param[in] camera_lever_position_y it sets the y coordinate of the object.
 *    @param[in] width it sets the width dimension of the object.
 *    @param[in] height it sets the height dimension of the object.
 *    @param[in] camera_lever_direction set the new direct of the camera lever
 *
 */
CameraLever::CameraLever(double camera_lever_position_x, double camera_lever_position_y, std::string camera_lever_direction) : GameObject(FILENAME,camera_lever_position_x,camera_lever_position_y,
                                                                     WIDTH, HEIGHT){
    assert ( camera_lever_position_x != NULL);
    assert ( camera_lever_position_y != NULL);
    animator = new Animation(FILENAME, 1, 3, 0.1);
    animator->addAction("up", 2,2);
    animator->addAction("mid",1,1);
    animator->addAction("down", 0,0);
    animator->setInterval("mid");
    camera_lever_direction = camera_lever_direction;
    stateInc = 1;
    state = 1;
}
/**
 *   @brief draws the animation of the button according to its position
 *   @return void
 */
void CameraLever::draw(){
    animator->draw(getPositionX(), getPositionY());
    animator->draw_collider(getPositionX(), getPositionY(), getWidth(), getHeight());
}
/**
*    @brief update the camera lever  decoring the time.
*    @param[in] timeElapsed its about the time
*/
void CameraLever::update(double timeElapsed){
    assert ( timeElapsed != NULL);  
    timeElapsed = timeElapsed;
    animator->update();
}
/**
 *   @brief check the atual state of the camera lever
 *   @return [int] state
 */
int CameraLever::getState(){
    return state;
}
/**
 *   @brief set the next possible state of the camera lever
 *   @return void
 */
void CameraLever::nextState(){
    if(state >= 2 || state <= 0){
        stateInc *= -1;
    }
    else{
        //nothing to do
    }
    state += stateInc;
    switch(state){
        case 0: animator->setInterval("up"); break;
        case 1: animator->setInterval("mid"); break;
        case 2: animator->setInterval("down"); break;
    }
}
