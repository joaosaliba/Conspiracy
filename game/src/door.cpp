/**
 * @file door.cpp
 * @brief class to object of door, where you can find some values, files,
 * others objects used in this class and methods to the same.
 * @copyright  GNU GENERAL PUBLIC LICENSE.
 */

//#define NDEBUG *uncomment to disable assertions

#include "door.hpp"
#include <assert.h>

/**
 * @brief Door object constructor.
 * @param[in] double-position_x it sets the x coordinate of the object.
 * @param[in] double-position_y it sets the y coordinate of the object.
 * @param[in] int-width it sets the width dimension of the object.
 * @param[in] int-height it sets the height dimension of the object.
 * @param[in] direction set the new direct of the camera lever
 *
 */

Door::Door(std::string object_name, double position_x, double position_y,
           int width, int height, std::string door_side) : GameObject(object_name,
                                                                     position_x,
                                                                     position_y,
                                                                     width,
                                                                     height){

    assert (position_x != NULL);
    assert (position_y != NULL);
    assert (width != NULL);
    assert (height != NULL);

    if(door_side.compare("DOWN") == 0) {
        animator = new animation(object_name, 1, 4, 0.5);
        animator->add_action("closed", 0,0);
        animator->add_action("open",1,3);
    }else if(door_side.compare("RIGHT") == 0) {
        animator = new animation(object_name, 1, 8, 0.5);
        animator->add_action("closed", 0,0);
        animator->add_action("open",1,3);
    }else if(door_side.compare("LEFT") == 0) {
        animator = new animation(object_name, 1, 8, 0.5);
        animator->add_action("closed", 4,4);
        animator->add_action("open",5,7);
    }

    side = door_side;
    door_effect = new Audio("assets/sounds/DOOR.wav", "EFFECT", 90);

    animator->set_draw_size(width,height);
    open = false;
}

/**
  *    @brief Door object destructor.
 */

Door::~Door(){}

/**
* @brief Method update
* <p>This method update the state of the door</p>
* @return void
*/

void Door::update(double time_elapsed) {
    assert (time_elapsed != NULL);
    time_elapsed = time_elapsed;
    if(animator->get_current_position_frame()!=3 && animator->get_current_position_frame() != 7){
        animator->update();
    }
    if(is_open()) {
        animator->set_interval("open");
    }else{
        animator->set_interval("closed");
    }
}

/**
* @brief Method draw
* <p>This method use animator to draw the door</p>
* @return void
*/

void Door::draw() {
    INFO("Door DRAW");
    animator->draw(get_position_x(), get_position_y());
    animator->draw_collider(get_position_x(), get_position_y(), get_width(), get_height());
}

/**
* @brief Method get_animation
* @return void
*/

animation * Door::get_animation() {
  return animator;
}

/**
* @brief Method is_open
* <p>This method return the open state of the door</p>
* @return bool-open
*/

bool Door::is_open() {
        return open;
}

/**
* @brief Method set_open
* <p>This method put the status equal the door status</p>
* @return void
*/

void Door::set_open(bool status) {
    assert (status != NULL);
    open = status;
}

/**
* @brief Method update
* @return void
*/

void Door::play_effect() {
    door_effect->play(0);
}

/**
* @brief Method update
* @return void
*/

std::string Door::get_door_side() {
    return side;
}
