//#define NDEBUG *uncomment to disable assertions
#include "alien.hpp"
#include <assert.h>

/** Objects included in the alien.hpp
* where the methods will be responsible for the manipulation and organization
* of these objects
*@param unsigned double-alien_position_x
*@param unsigned double-alien_position_y
*@param unsigned int-width
*@param unsigned int-height
*@param unsigned bool-block_movement
*@param unsigned bool-in_position
*/

Alien::Alien(std::string objectName, double alien_position_x, double alien_position_y,int width,
int height) :
GameObject(objectName,alien_position_x,alien_position_y,width, height) {
    assert (alien_position_x !=NULL);
    assert (alien_position_x !=NULL);
    assert (width !=NULL);
    assert (height !=NULL);

    if(objectName.compare("assets/sprites/bilu_sheet.png") == 0) {
        alienName = "Bilu";
    }else if(objectName.compare("assets/sprites/varginha_sheet.png") == 0) {
        alienName = "Varginha";

    }else if(objectName.compare("assets/sprites/etemer_sheet.png") == 0) {
        alienName = "Etemer";
    }
    animator = new Animation(objectName, 2, 10, 0.5);

    animator->add_action("right",6,9);
    animator->add_action("left",1,4);
    animator->add_action("up",6,9);
    animator->add_action("down",1,4);
    animator->add_action("idle_right",5,5);
    animator->add_action("idle_left",0,0);
    animator->add_action("idle_up",5,5);
    animator->add_action("idle_down",0,0);

    idle_animation_number = 5;
    block_movement = false;
    in_position = false;
    movement_sound_effect = new Audio("assets/sounds/FOOTSTEP.wav", "EFFECT", 128);
}

Alien::~Alien() {
}

/**
* Walk in x method
* <p>Creates animations of movement and collision in X in the game</p>
*@param unsigned double-alien_in_x
*@param unsigned double-alien_position_x
*@return void
*/

void Alien::walk_in_x(double & alien_in_x) {
    assert (alien_in_x !=NULL);

    if(InputManager::instance.is_key_pressed(InputManager::KeyPress::KEY_PRESS_RIGHT)) {
        alien_in_x = alien_in_x;
        idle_animation_number = 5;
        animator->set_interval("right");
    if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_RIGHT)) {
        inc_x = inc_x;
        idle_animation_number = 5;
        animator->set_interval("right");
    }
    else if(InputManager::instance.is_key_pressed(InputManager::KeyPress::KEY_PRESS_LEFT)) {
        //movement_sound_effect->play(-1);
        alien_in_x = alien_in_x * (0-1);
        idle_animation_number = 0;
        animator->set_interval("left");
        inc_x = inc_x * (0-1);
        idle_animation_number = 0;
        animator->set_interval("left");
    }
    else {
        alien_in_x = 0;
    }
    set_alien_position_x(get_alien_position_x()+alien_in_x);
    if(CollisionManager::instance.verify_collision_with_walls_and_chairs(this)) {
        set_alien_position_x(get_alien_position_x()+(alien_in_x*(0-1)));
        }else {
            //nothing to do
        }
    }else {
        //nothing to do
    }   

/**
* Walk in y method
* <p>Creates animations of movement and collision in Y in the game</p>
*@param unsigned double-alien_in_x
*@param unsigned double-alien_in_y
*@param unsigned double-alien_position_x
*@param unsigned double-alien_position_y
*@return void
*/

void Alien::walk_in_y(double & alien_in_y, double alien_in_x) {
    assert (alien_in_y !=NULL);
    assert (alien_in_x !=NULL);

    if(InputManager::instance.is_key_pressed(InputManager::KeyPress::KEY_PRESS_UP)) {
        alien_in_y = alien_in_y * (0-1);
        idle_animation_number = 5;
        if(alien_in_x == 0){
            animator->set_interval("up");
        }else {
            //nothing to do
        }
    }
    else if(engine::InputManager::
    instance.is_key_pressed(engine::InputManager::KeyPress::KEY_PRESS_DOWN)) {
        alien_in_y = alien_in_y;
        idle_animation_number = 0;
        if(alien_in_x == 0){
            animator->set_interval("down");
            if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_UP)) {
                inc_y = inc_y * (0-1);
                idle_animation_number = 5;
                if(inc_x == 0){
                animator->set_interval("up");
                }else {
                    //nothing to do
                }
            }else {
                //nothing to do
            }
        else if(engine::InputManager::instance.isKeyPressed(engine::InputManager::KeyPress::
        KEY_PRESS_DOWN)) {
            inc_y = inc_y;
            idle_animation_number = 0;
            if(inc_x == 0){
                animator->set_interval("down");
            }else {
                //nothing to do
            }
        }else {
            alien_in_y = 0;
        }
    set_alien_position_y(get_alien_position_y()+alien_in_y);
    if(CollisionManager::instance.verify_collision_with_walls_and_chairs(this)) {
        set_alien_position_y(get_alien_position_y()+(alien_in_y*(0-1)));
    }else {
        //nothing to do
    }
}

/**
* Draw method
* <p>draws the animation of the character according to its position</p>
*@param unsigned double-alien_position_x
*@param unsigned double-alien_position_y
*@return void
*/

void Alien::draw() {
    INFO("ALIEN DRAW");
    animator->draw(get_alien_position_x(), get_alien_position_y());
}

Animation * Alien::get_animation() {
  return animator;
}

/**
* Set alien selected
* <p>selected character</p>
*@param unsigned bool-is_selected
*   @return void
*/

void Alien::set_alien_selected() {
    is_selected = true;
}

/**
* Set alien deselect
* <p>unselected character</p>
*@return void
*/

void Alien::set_alien_deselect() {
    is_selected = false;
}

/**
* Is in position method
* <p>character position</p>
*@return bool
*/

bool Alien::is_in_position() {
    return in_position;
}
