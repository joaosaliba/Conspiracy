//#define NDEBUG *uncomment to disable assertions
#include "alien_etemer.hpp"
#include "chair.hpp"
#include "guard.hpp"
#include <assert.h>

#define FILENAME "assets/sprites/etemer_sheet.png"
#define WIDTH 10
#define HEIGHT 22
#define SCREEN_WIDTH 1000
#define SCREEN_INITIAL 0
#define ACTION_SPECIAL_LEFT "special_left"
#define SPRITE_INITIAL_SPECIAL_LEFT 10
#define SPRITE_FINAL_SPECIAL_LEFT 13
#define ACTION_SPECIAL_RIGHT "special_right"
#define SPRITE_INITIAL_SPECIAL_RIGHT 14
#define SPRITE_FINAL_SPECIAL_RIGHT 17
#define TOTAL_TIME_1 1.0
#define TOTAL_TIME_2 0.3
#define VELOCITY_ETEMER 0.15
#define ACTION_IDLE_LEFT "idle_left"
#define ACTION_IDLE_RIGHT "idle_right"
#define NAME_CHARACTER "E"
#define ACTION_LEFT "left"
#define ACTION_RIGHT "right"
#define DISTANCE 60
#define ETEMER_DISTANCE 2.0
#define ANIMATION_NUMBER_1 5
#define ANIMATION_NUMBER_2 0
#define BAR_PERCENT 0.0
#define CENTER_CHARACTER_1 15
#define CENTER_CHARACTER_2 20
#define PLAY_EFECT_1 0
#define PLAY_EFECT_2 1
#define ANIMATION_1 "up"
#define ANIMATION_2 "down"


/** objects included in the alien_etemer.hpp, guard.hpp classes found on lines 1 to
* line 3, where the methods will be responsible for the manipulation and organization 
* of these objects
*@param unsigned double-etemer_position_x
*@param unsigned double-etemer_position_y
*@param unsigned bool-hacking
*@param unsigned bool-editing
*@param unsigned bool-last_action
*@param unsigned bool-is_selected
*@param unsigned bool-in_position
*/

Etemer::Etemer(double etemer_position_x, double etemer_position_y) : 
Alien(FILENAME, etemer_position_x, etemer_position_y, WIDTH, HEIGHT) {
   
    double etemer_position_x = 0.0;
    double etemer_position_y = 0.0;
    bool hacking = true;
    bool editing = true;
    bool last_action = true;
    bool is_selected = true;
    bool in_position = true;

    assert (etemer_position_x !=NULL);
    assert (etemer_position_y !=NULL);
    assert (WIDTH !=NULL);
    assert (WIDTH > 10);
    assert (HEIGHT !=NULL);
    assert (HEIGHT > 22);

    if(etemer_position_x > SCREEN_WIDTH || etemer_position_x < SCREEN_INITIAL) {
        ERROR("Strange Etemer position x");
        exit(-1);
    }else {
       //nothing to do
    }
    if(etemer_position_y > SCREEN_WIDTH || etemer_position_y < SCREEN_INITIAL) {
       ERROR("Strange Etemer position y");
       exit(-1);
     }else {
       //nothing to do
     }

    animator->add_action(ACTION_SPECIAL_RIGHT,SPRITE_INITIAL_SPECIAL_RIGHT,SPRITE_FINAL_SPECIAL_RIGHT);
    animator->add_action(ACTION_SPECIAL_LEFT,SPRITE_INITIAL_SPECIAL_LEFT,SPRITE_FINAL_SPECIAL_LEFT);

    is_selected = true;
    talking = false;
    in_position = false;
}

/**
* Update method 
* <p>movement and special actions of the character, in addition to checking the finishi point</p>
*@param unsigned double-time_elapsed
*@param unsigned bool-in_position 
*@param unsigned double-etemer_in_x
*@param unsigned double-etemer_in_y
*@return void
*/

void Etemer::update(double time_elapsed) {
    
    double time_elapsed = 0.0;
    bool in_position = true;
    double etemer_in_x = 0.0;
    double etemer_in_y = 0.0;
    
    assert (time_elapsed !=NULL);

    if(time_elapsed == -1) {
       ERROR("Strange time ");
       exit(-1);
     }else {
       //nothing to do
     }

    in_position = false;
    if (block_movement) {
        animator->set_total_time(TOTAL_TIME_1);
    }else {
        animator->set_total_time(TOTAL_TIME_2);
    }

    auto etemer_in_y = VELOCITY_ETEMER*time_elapsed;
    auto etemer_in_x = VELOCITY_ETEMER*time_elapsed;

    if(!block_movement && is_selected) {
        walk_in_x(etemer_in_x);
        walk_in_y(etemer_in_y, etemer_in_x);
    }else {
        //nothing to do
    }

    if(etemer_in_x == 0.0 && etemer_in_y == 0.0 && !block_movement) {
        if(idle_animation_number) {
            animator->set_interval(ACTION_IDLE_RIGHT);
        }else {
            animator->set_interval(ACTION_IDLE_LEFT);    
        }   
    }else {
        //nothing to do
    }        

   FinishPoint* finish_point = (FinishPoint*)CollisionManager::
   instance.verify_collision_with_finish_points(this);
    if(finish_point != NULL) {
        if(finish_point->get_alien_names().find(NAME_CHARACTER) != std::string::npos) {
            in_position = true;
        }else {
            in_position = false;
        }
    }else {
        //nothing to do
    }
    move_chair();

    if(CollisionManager::instance.verify_collision_with_cameras(this)) {
        set_enabled(false);
    }else {
        set_enabled(true);
    }
    animator->update();
}

/**
* Special action method 
* <p>movement and special actions of the character, in addition to verify collisions and 
*attributes of movement of the character</p>
*@param unsigned double-etemer_distance 
*@param unsigned bool-talking
*@param unsigned bool-block_movement
*@return void
*/

void Etemer::special_action(GameObject * guard, double etemer_distance) {
    
    double etemer_distance = 0.0; 
    bool talking = true;
    bool block_movement = true;    
    
    assert (etemer_distance !=NULL);

    if(etemer_distance > SCREEN_WIDTH) {
       ERROR("distance greater than allowed");
       exit(-1);
     }else {
       //nothing to do
     }

    if(InputManager::instance.is_key_pressed(InputManager::KEY_PRESS_SPACE) &&
    guard != NULL && is_selected) {
        animator->set_total_time(TOTAL_TIME_1);
        //TODO Change etemer_distance.
        if(!talking && etemer_distance < DISTANCE) {
            talking = true;
            block_movement = true;
        if(((Guard *) (guard))->get_position_x() > get_position_x()) {
                ((Guard *)(guard))->talking_to_etemer(ACTION_LEFT);
        }else {
            ((Guard *)(guard))->talking_to_etemer(ACTION_RIGHT);
        }
        }else {
            talking = false;
            block_movement = false;
    }
    }else{
        //nothing to do
    }

    if(talking) {
        if(((Guard *) (guard))->get_position_x() >= get_position_x()) {
            animator->set_interval(ACTION_SPECIAL_RIGHT);
            idle_animation_number = ANIMATION_NUMBER_1;
        }else {
            animator->set_interval(ACTION_SPECIAL_LEFT);
            idle_animation_number = ANIMATION_NUMBER_2;
        }
        if(((Guard *) (guard))->get_talking_bar_percent() <= BAR_PERCENT) {
            talking = false;
            block_movement = false;
            if(idle_animation_number) {
                animator->set_interval(ACTION_IDLE_RIGHT);
            }else{
                animator->set_interval(ACTION_IDLE_LEFT);
            }
        }else {
            talking = true;
            block_movement = false;
        }
    }else {
        //nothing to do
    }
}

/**
* Draw method 
* <p>draws the animation of the character according to its position</p>
*@param unsigned double-etemer_position_x
*@param unsigned double-etemer_position_y
*@return void
*/

void Etemer::draw() {
    
    double etemer_position_x = 0.0;
    double etemer_position_y = 0.0;

    INFO("Etemer DRAW");
    animator->draw(get_position_x()-CENTER_CHARACTER_1, get_position_y()-CENTER_CHARACTER_2);
    animator->draw_collider(get_position_x(), get_position_y(), get_width(), get_heigth());
}

/**
* Move chair method 
* <p>character move</p>
*@return void
*/

void Etemer::move_chair() {
    std::pair<std::string, GameObject *> chair = CollisionManager::
    instance.verify_collision_with_chairs(this);
    if(chair.second != NULL) {
        if(animator->get_interval().first == chair.first) {
            ((Chair *) (chair.second))->set_moving(true);
            ((Chair *) (chair.second))->set_direction(chair.first);
        }else {
            ((Chair *) (chair.second))->set_moving(false);
        }
    }else {
        //nothing to do
    }
}

/**
* Walk in x method 
* <p>Creates animations of movement and collision in X in the game</p>
*@param unsigned double-etemer_in_x
*@param unsigned double-etemer_position_x
*@return void
*/

void Etemer::walk_in_x(double & etemer_in_x) {
    
    double etemer_in_x = 0.0;
    double etemer_position_x = 0.0;
    
    assert (etemer_in_x !=NULL);

    if(etemer_in_x > SCREEN_WIDTH || etemer_in_x < SCREEN_INITIAL) {
       ERROR("distance Etemer greater than allowed");
       exit(-1);
     }else {
       //nothing to do
     }

    if(InputManager::instance.is_key_pressed(InputManager::KeyPress::KEY_PRESS_RIGHT)) {
        etemer_in_x = etemer_in_x;
        idle_animation_number = ANIMATION_NUMBER_1;
        animator->set_interval(ACTION_RIGHT);
}
    else if(InputManager::instance.is_key_pressed(InputManager::KeyPress::KEY_PRESS_LEFT)) {
        //movement_sound_effect->play(-1);
        etemer_in_x = etemer_in_x * (PLAY_EFECT_1 - PLAY_EFECT_2);
        idle_animation_number = ANIMATION_NUMBER_2;
        animator->set_interval(ACTION_LEFT);
}
    else {
        etemer_in_x = PLAY_EFECT_1;
}
    set_position_x(get_position_x()+etemer_in_x);

    if(CollisionManager::instance.verify_collision_with_walls_and_chairs(this)) {
        set_position_x(get_position_x()+(etemer_in_x*(PLAY_EFECT_1 - PLAY_EFECT_2)));
    }else {
        //nothing to do
    }
}

/**
* Walk in y method 
* <p>Creates animations of movement and collision in Y in the game</p>
*@param unsigned double-etemer_in_y
*@param unsigned double-etemer_position_y
*@return void
*/

void Etemer::walk_in_y(double & etemer_in_y, double etemer_in_x) {
   
    double etemer_in_y = 0.0;
    double etemer_position_y = 0.0;
   
    assert (etemer_in_y !=NULL);
    assert (etemer_in_x !=NULL);

    if(etemer_in_x > SCREEN_WIDTH || etemer_in_x < SCREEN_INITIAL) {
       ERROR("distance Etemer X greater than allowed");
       exit(-1);
     }else {
       //nothing to do
     }
    if(etemer_in_y > SCREEN_WIDTH || etemer_in_y < SCREEN_INITIAL) {
       ERROR("distance Etemer Y greater than allowed");
       exit(-1);
     }else {
       //nothing to do
     }

    if(InputManager::instance.is_key_pressed(InputManager::KeyPress::KEY_PRESS_UP)) {
        etemer_in_y = etemer_in_y * (PLAY_EFECT_1 - PLAY_EFECT_2);
        idle_animation_number = ANIMATION_1;
        if(etemer_in_x == 0) {
                animator->set_interval(ANIMATION_1);
        }else {
            //nothing to do
        }
    }
    else if(engine::InputManager::instance.is_key_pressed(engine::InputManager::KeyPress::
    KEY_PRESS_DOWN)) {
        etemer_in_y = etemer_in_y;
        idle_animation_number = ANIMATION_2;
        if(etemer_in_x == 0) {
            animator->set_interval(ANIMATION_2);
        }else {
            //nothing to do
        }
    }
    else {
        etemer_in_y = PLAY_EFECT_1;
    }
    set_position_y(get_position_y()+etemer_in_y);

    if(CollisionManager::instance.verify_collision_with_walls_and_chairs(this)) {
        set_position_y(get_position_y()+(etemer_in_y*(PLAY_EFECT_1 - PLAY_EFECT_2)));
    }else {
        //nothing to do
    }
}

/**
* Verify Etemer distance method 
* <p>check the guards' etemer_distance</p>
*@param unsigned double-etemer_position_x
*@param unsigned double-etemer_position_y
*@param unsigned double-etemer_distance
*@return void
*/

void Etemer::verify_etemer_distance(GameObject* guard) {
    
    double etemer_position_x = 0.0;
    double etemer_position_y = 0.0;
    double etemer_distance = 0.0;
    
    double etemer_distance = sqrt((pow(get_position_x() - guard->get_position_x(), ETEMER_DISTANCE)) +  
    (pow(get_position_y() - guard->get_position_y(), ETEMER_DISTANCE)));

    if(etemer_distance < DISTANCE){
        special_action(guard, etemer_distance);
    }else {
        //nothing to do
    }
}
