#include "door.hpp"
#include <assert.h>

/** Objects included in the door.hpp 
* where the methods will be responsible for the manipulation and organization 
* of these objects
*/

Door::Door(std::string objectName, double door_position_x, double door_position_y,
           int width, int height, std::string door_side) : GameObject(objectName,
                                                                     position_x,
                                                                     position_y,
                                                                     width,
                                                                     height) {
    assert (door_position_x !=NULL);
    assert (door_position_y !=NULL);
    assert (width !=NULL);
    assert (height !=NULL);                                                                    

    if(doorSide.compare("DOWN") == 0) {
        animator = new Animation(objectName, 1, 4, 0.5);
        animator->add_action("closed", 0,0);
        animator->add_action("open",1,3);
    }else if(doorSide.compare("RIGHT") == 0) {
        animator = new Animation(objectName, 1, 8, 0.5);
        animator->add_action("closed", 0,0);
        animator->add_action("open",1,3);
    }else if(doorSide.compare("LEFT") == 0) {
        animator = new Animation(objectName, 1, 8, 0.5);
        animator->add_action("closed", 4,4);
        animator->add_action("open",5,7);
    }

    side = door_side;
    door_effect = new Audio("assets/sounds/DOOR.wav", "EFFECT", 90);

    animator->set_draw_size(width,height);
    open = false;
}

Door::~Door() {
}

/** 
*   movement and special actions of the door, in addition animation
*   @return void
*/

void Door::update(double time_elapsed) {
    assert (time_elapsed !=NULL);

    time_elapsed = time_elapsed;
    if(animator->get_current_position_frame()!=3 && animator->get_current_position_frame()!=7) {
        animator->update();
    }
    if(is_open()) {
        animator->set_interval("open");
    }else {
        animator->set_interval("closed");
    }
}

/** 
*   draws the animation of the door
*   @return void
*/

void Door::draw() {
    INFO("Door DRAW");
    animator->draw(get_position_x(), get_position_y());
    animator->draw_collider(get_position_x(), get_position_y(), get_width(), get_height());
}

Animation * Door::get_animation() {
    return animator;
}

bool Door::is_open() {
    return open;
}

/** 
*   draws the animation of the open door
*   @return void
*/

void Door::set_open(bool door_status) {
    assert (door_status !=NULL);
    open = door_status;
}

/** 
*   draws the play effect of the door
*   @return void
*/

void Door::play_effect() {
    door_effect->play(0);
}

std::string Door::get_door_side() {
    return side;
}
