/**
 * @file door_switch.cpp
 * @brief class to object of door_switch, where you can find some values, files,
 * others objects used in this class and methods to the same.
 * @copyright  GNU GENERAL PUBLIC LICENSE.
 */

 //#define NDEBUG *uncomment to disable assertions

#include "door_switch.hpp"
#include <assert.h>
#define MAX_STRANGE_DOOR_VALUE 1000
#define MIN_STRANGE_DOOR_VALUE 0
/**
 * @brief DoorSwitch object constructor.
 * @param[in] double-door_switch_x it sets the x coordinate of the object.
 * @param[in] double-door_switch_y it sets the y coordinate of the object.
 * @param[in] int-door_switch_width it sets the width dimension of the object.
 * @param[in] int-door_switch_height it sets the height dimension of the object.
 *
 */

DoorSwitch::DoorSwitch(std::string object_name, double door_switch_position_x, double door_switch_position_y,
                                     int door_switch_width, int door_switch_height) : GameObject(object_name,
                                                                         door_switch_position_x,
                                                                         door_switch_position_y,
                                                                         door_switch_width,
                                                                         door_switch_height) {

    assert (door_switch_position_x != NULL);
    assert (door_switch_position_y != NULL);
    assert (door_switch_width != NULL);
    assert (door_switch_height != NULL);
//this part verify if the value of door_switch_position_x and y is strange and return a error
    if(door_switch_position_x > MAX_STRANGE_DOOR_VALUE || door_switch_position_x < MIN_STRANGE_DOOR_VALUE) {
        ERROR("Strange door switch position");
        exit(-1);
    }else {
        //nothing to do
    }
    if(door_switch_position_y > MAX_STRANGE_DOOR_VALUE || door_switch_position_y < MIN_STRANGE_DOOR_VALUE) {
        ERROR("Strange door switch position");
        exit(-1);
    }else {
        //nothing to do
    }
    //this part verify if the door_switch_width is strange and return a error
    if(door_switch_width > 500 || door_switch_width < MIN_STRANGE_DOOR_VALUE) {
        ERROR("Strange camera width");
        exit(-1);
    }else {
        //nothing to do
    }
    //this part verify if the door_switch_height is strange and return a error
    if(door_switch_height > 500 || door_switch_height < MIN_STRANGE_DOOR_VALUE) {
        ERROR("Strange camera height");
        exit(-1);
    }else {
        //nothing to do
    }

    animator = new Animation(object_name, 1, 6, 0.5);

    hacking_effect = new Audio("assets/sounds/PCNOISE.wav", "EFFECT", 60);
    hacking_bar = new ProgressBar(door_switch_position_x-7, door_switch_position_y-10, 45, 5, 0.002);

    animator->add_action("beingHacked", 1,5);
    animator->add_action("idle", 0, 0);
    pressed = false;
}

/**
  *    @brief door_switch object destructor.
 */

DoorSwitch::~DoorSwitch(){}

/**
* @brief Method update
* <p>This method update the state of the door switch</p>
* @param[in] double-time_elapsed
* @return void
*/

void DoorSwitch::update(double time_elapsed) {
    assert (time_elapsed != NULL);

    if(time_elapsed == NULL) {
        ERROR("we didnt find the atrribute time_elapsed");
        exit(-1);
    }else {
      //nothing to do
    }

    time_elapsed = time_elapsed;
    animator->update();
    //this part cerify if is pressed and update passing the time_elapsed
    if(is_pressed())) {
        hacking_bar->update(time_elapsed);
    }
}

/**
* @brief Method draw
* <p>This method draw the door switch</p>
* @return void
*/

void DoorSwitch::draw() {
    INFO("DoorSwitch DRAW");
    //if the switch is pressed, he set the status "beingHacked"
    if(is_pressed()) {
        animator->set_interval("beingHacked");
        AnimationManager::instance.addProgressBar(hacking_bar);
        //put the status false for pressed in the first flux condition or true to the others
        if(hacking_bar->get_percent() <= 0.0) {
            pressed = false;
            set_enabled(false);
        }else {
            pressed = true;
            set_enabled(true);
        }
    }else {
        animator->set_interval("idle");
    }
    //and draw the switch getiing the position x and y
    animator->draw(get_door_switch_position_x(), get_door_switch_position_y());
}

Animation * DoorSwitch::getAnimation() {
  return animator;
}

/**
* @brief Method animate
* <p>This method make the "pressed" equal true</p>
* @return void
*/

void DoorSwitch::animate() {
    pressed = true;
}

/**
* @brief Method stop_animation
* <p>This method put pressed equal false</p>
* @return void
*/

void DoorSwitch::stop_animation() {
    pressed = false;
}

/**
* @brief Method is_pressed
* <p>This method return the state of pressed</p>
* @return bool-pressed
*/

bool DoorSwitch::is_pressed() {
    return pressed;
}

/**
* @brief Method play_effect
* <p>This method activate a effect called play(2)</p>
* @return void
*/

void DoorSwitch::play_effect() {
    hacking_effect->play(2);
}

/**
* @brief Method stop_effect
* <p>This method call a other method that stop the effect</p>
* @return void
*/

void DoorSwitch::stop_effect() {
    hacking_effect->stop();
}

/**
* @brief Method get_hacking_bar_percent
* <p>This method active a method called get_percent</p>
* @return double-percent
*/

double DoorSwitch::get_hacking_bar_percent() {
    return hacking_bar->get_percent();

}

/**
* @brief Method reset_percent_progress
* <p>This method call a method that reset the percent</p>
* @return void
*/

void DoorSwitch::reset_hacking_progress() {
    hacking_bar->reset_percent();
}
