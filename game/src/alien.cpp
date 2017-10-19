//#define NDEBUG *uncomment to disable assertions
#include "alien.hpp"
#include <assert.h>

#define SCREEN_WIDTH 1000
#define SCREEN_INITIAL 0
#define IMAGE_PATH_BILU "assets/sprites/bilu_sheet.png"
#define IMAGE_PATH_VARGINHA "assets/sprites/varginha_sheet.png"
#define IMAGE_PATH_ETEMER "assets/sprites/etemer_sheet.png"
#define SOUND_PATH "assets/sounds/FOOTSTEP.wav"
#define SOUND_1 "EFFECT"
#define TIME_SOUND_1 128
#define ALIEN_NAME_1 "Bilu"
#define ALIEN_NAME_2 "Varginha"
#define ALIEN_NAME_3 "Etemer"
#define ANIMATION_1 2
#define ANIMATION_2 10
#define ANIMATION_3 0.5
#define ACTION_RIGHT "right"
#define ACTION_INITIAL_RIGHT 6
#define ACTION_FINAL_RIGHT 9
#define ACTION_LEFT "left"
#define ACTION_INITIAL_LEFT 1
#define ACTION_FINAL_LEFT 4
#define ANIMATION_1 "up"
#define ANIMATION_1_INITIAL 6
#define ANIMATION_1_FINAL 9
#define ANIMATION_2 "down"
#define ANIMATION_2_INITIAL 1
#define ANIMATION_2_FINAL 4
#define ACTION_IDLE_RIGHT "idle_right"
#define ACTION_IDLE_INITIAL_RIGHT 5
#define ACTION_IDLE_FINAL_RIGHT 5
#define ACTION_IDLE_LEFT "idle_left"
#define ACTION_IDLE_INITIAL_LEFT 0
#define ACTION_IDLE_FINAL_LEFT 0
#define ACTION_IDLE_UP "idle_up"
#define ACTION_IDLE_INITIAL_UP 5
#define ACTION_IDLE_FINAL_UP 5
#define ACTION_IDLE_DOWN "idle_down"
#define ACTION_IDLE_INITIAL_DOWN 0
#define ACTION_IDLE_FINAL_DOWN 0
#define ANIMATION_NUMBER_1 5
#define ANIMATION_NUMBER_2 0
#define PLAY_EFECT_1 0
#define PLAY_EFECT_2 1

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
    
    double alien_position_x = 0.0;
    double alien_position_y = 0.0
    int width = 0;
    int height = 0;
    bool block_movement = true;
    bool in_position  = true;  
    
    assert (alien_position_x !=NULL);
    assert (alien_position_x !=NULL);
    assert (width !=NULL);
    assert (height !=NULL);

    // Verifies the position x of the character
    if(alien_position_x > SCREEN_WIDTH || alien_position_x < SCREEN_INITIAL) {
        ERROR("Strange Alien position x");
        exit(-1);
    }else {
       //nothing to do
    }
    // Verifies the position y of the character
    if(alien_position_y > SCREEN_WIDTH || alien_position_y < SCREEN_INITIAL) {
       ERROR("Strange Alien position y");
       exit(-1);
    }else {
       //nothing to do
    }
    
    //compare which character it is, if is Bilu
    if(objectName.compare(IMAGE_PATH_BILU) == 0) {
        alienName = ALIEN_NAME_1;
    //compare which character it is, if is Varginha    
    }else if(objectName.compare(IMAGE_PATH_VARGINHA) == 0) {
        alienName = ALIEN_NAME_2;
    //compare which character it is, if is Etemer
    }else if(objectName.compare(IMAGE_PATH_ETEMER) == 0) {
        alienName = ALIEN_NAME_3;
    }
    animator = new Animation(objectName, ANIMATION_1, ANIMATION_2, ANIMATION_3);

    animator->add_action(ACTION_RIGHT,ACTION_INITIAL_RIGHT,ACTION_FINAL_RIGHT);
    animator->add_action(ACTION_LEFT,ACTION_INITIAL_LEFT,ACTION_FINAL_LEFT);
    animator->add_action(ANIMATION_1,ANIMATION_1_INITIAL,ANIMATION_1_FINAL);
    animator->add_action(ANIMATION_2,ANIMATION_2_INITIAL,ANIMATION_2_FINAL);
    animator->add_action(ACTION_IDLE_RIGHT,ACTION_IDLE_INITIAL_RIGHT,
    ACTION_IDLE_FINAL_RIGHT);
    animator->add_action(ACTION_IDLE_LEFT,ACTION_IDLE_INITIAL_LEFT,ACTION_IDLE_FINAL_LEFT);
    animator->add_action(ACTION_IDLE_UP,ACTION_IDLE_INITIAL_UP,ACTION_IDLE_FINAL_UP);
    animator->add_action(ACTION_IDLE_DOWN,ACTION_IDLE_INITIAL_DOWN,ACTION_IDLE_FINAL_DOWN);


    idle_animation_number = ANIMATION_NUMBER_1;
    block_movement = false;
    in_position = false;
    movement_sound_effect = new Audio(SOUND_PATH, SOUND_1, TIME_SOUND_1);
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
    
    double alien_in_x = 0.0;
    double alien_position_x = 0.0;
    
    assert (alien_in_x !=NULL);
    // Verifies the alien_in_x of the character
    if(alien_in_x > SCREEN_WIDTH || alien_in_x < SCREEN_INITIAL) {
        ERROR("Strange Alien position x");
        exit(-1);
    }else {
       //nothing to do
    }
    //Chech if instance
    if(InputManager::instance.is_key_pressed(InputManager::KeyPress::KEY_PRESS_RIGHT)) {
        alien_in_x = alien_in_x;
        idle_animation_number = ANIMATION_NUMBER_1;
        animator->set_interval(ACTION_RIGHT);
    //Chech if instance    
    if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_RIGHT)) {
        inc_x = inc_x;
        idle_animation_number = ANIMATION_NUMBER_1;
        animator->set_interval(ACTION_RIGHT);
    }
    //Chech if instance 
    else if(InputManager::instance.is_key_pressed(InputManager::KeyPress::KEY_PRESS_LEFT)) {
        //movement_sound_effect->play(-1);
        alien_in_x = alien_in_x * (PLAY_EFECT_1 - PLAY_EFECT_2);
        idle_animation_number = ANIMATION_NUMBER_2;
        animator->set_interval(ACTION_LEFT);
        inc_x = inc_x * (PLAY_EFECT_1 - PLAY_EFECT_2);
        idle_animation_number = ANIMATION_NUMBER_2;
        animator->set_interval(ACTION_LEFT);
    }
    // If you do not receive an action
    else {
        alien_in_x = PLAY_EFECT_1;
    }
    set_alien_position_x(get_alien_position_x()+alien_in_x);
    //Chech if instance was collision
    if(CollisionManager::instance.verify_collision_with_walls_and_chairs(this)) {
        set_alien_position_x(get_alien_position_x()+(alien_in_x*(PLAY_EFECT_1 - PLAY_EFECT_2)));
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

    double alien_in_x = 0.0;
    double alien_in_y = 0.0;
    double alien_position_x = 0.0;
    double alien_position_y = 0.0;
    
    assert (alien_in_y !=NULL);
    assert (alien_in_x !=NULL);
    // Verifies the alien_in_x of the character
    if(alien_in_x > SCREEN_WIDTH || alien_in_x < SCREEN_INITIAL) {
        ERROR("Strange Alien position x");
        exit(-1);
    }else {
       //nothing to do
    }
    // Verifies the alien_in_y of the character
    if(alien_in_y > SCREEN_WIDTH || alien_in_y < SCREEN_INITIAL) {
        ERROR("Strange Alien position y");
        exit(-1);
    }else {
       //nothing to do
    }

    if(InputManager::instance.is_key_pressed(InputManager::KeyPress::KEY_PRESS_UP)) {
        alien_in_y = alien_in_y * (PLAY_EFECT_1 - PLAY_EFECT_2);
        idle_animation_number = ANIMATION_NUMBER_1;
        // Check if alien_in_x is equals 0
        if(alien_in_x == 0){
            animator->set_interval(ANIMATION_1);
        }else {
            //nothing to do
        }
    }
    else if(engine::InputManager::
    instance.is_key_pressed(engine::InputManager::KeyPress::KEY_PRESS_DOWN)) {
        alien_in_y = alien_in_y;
        idle_animation_number = ANIMATION_NUMBER_2;
        // Check if alien_in_x is equals 0, receives action down
        if(alien_in_x == 0){
            animator->set_interval(ANIMATION_2);
            if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_UP)) {
                inc_y = inc_y * (PLAY_EFECT_1 - PLAY_EFECT_2);
                idle_animation_number = ANIMATION_NUMBER_1;
                // Check if inc_x is equals 0, receives action up
                if(inc_x == 0){
                animator->set_interval(ANIMATION_1);
                }else {
                    //nothing to do
                }
            }else {
                //nothing to do
            }
        else if(engine::InputManager::instance.isKeyPressed(engine::InputManager::KeyPress::
        KEY_PRESS_DOWN)) {
            inc_y = inc_y;
            idle_animation_number = ANIMATION_NUMBER_2;
            // Check if alien_in_x is equals 0, receives action down
            if(inc_x == 0){
                animator->set_interval(ANIMATION_2);
            }else {
                //nothing to do
            }
        //Assigns a default
        }else {
            alien_in_y = PLAY_EFECT_1;
        }
    set_alien_position_y(get_alien_position_y()+alien_in_y);
    // Instace verify collision
    if(CollisionManager::instance.verify_collision_with_walls_and_chairs(this)) {
        set_alien_position_y(get_alien_position_y()+(alien_in_y*(PLAY_EFECT_1 - PLAY_EFECT_2)));
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

    double alien_position_x = 0.0;
    double alien_position_y = 0.0;    

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
