//#define NDEBUG *uncomment to disable assertions
#include "alien_varginha.hpp"
#include <assert.h>

#define FILENAME "assets/sprites/varginha_sheet.png"
#define WIDTH 10
#define HEIGHT 15

/** Objects included in the alien_varginha.hpp 
* where the methods will be responsible for the manipulation and organization 
* of these objects
*@param unsigned double-varginha_position_x
*@param unsigned double-varginha_position_y
*@param unsigned bool-is_invisible
*@param unsigned bool-is_selected
*@param unsigned bool-in_position
*@param unsigned bool-turn_off
*/

Varginha::Varginha(double varginha_position_x, double varginha_position_y) : 
Alien(FILENAME, varginha_position_x, varginha_position_y, WIDTH, HEIGHT) {
    
    double varginha_position_x = 0.0;
    double varginha_position_y = 0.0;
    bool-is_invisible = true;
    bool-is_selected = true; //conferir com o professor
    bool in_position = true;
    bool turn_off = true;
    
    assert (varginha_position_x !=NULL);
    assert (etemer_position_y !=NULL);
    assert (WIDTH !=NULL);
    assert (WIDTH > 10);
    assert (HEIGHT !=NULL);
    assert (HEIGHT > 15);
    if(varginha_position_x > 1000 || varginha_position_x < 0) {
        ERROR("Strange Varginha position x");
        exit(-1);
    }else {
       //nothing to do
    }
    if(varginha_position_y > 1000 || varginha_position_y < 0) {
       ERROR("Strange Varginha position y");
       exit(-1);
     }else {
       //nothing to do
     }
    if(WIDTH > 10 || WIDTH < 0) {
       ERROR("Strange width");
       exit(-1);
     }else {
       //nothing to do
     }
    if(HEIGHT > 15 || HEIGHT < 0) {
       ERROR("Strange height");
       exit(-1);
     }else {
       //nothing to do
     }

    animator->add_action("special_right",12,13);
    animator->add_action("special_left",10,11);
    animator->add_action("invisible_right", 13, 13);
    animator->add_action("invisible_left", 11, 11);
    animator->add_action("action_right", 17, 19);
    animator->add_action("action_left", 14, 16);
    is_invisible = false;
    is_selected = false;
    in_position = false;
    turn_off = false;

    timer_turn = new Timer();
    timer_turn->start();
}

/**
* Update method 
* <p>movement and special actions of the character, in addition to checking the finishi point</p>
*@param unsigned double-time_elapsed
*@param unsigned bool-in_position
*@param unsigned double-varginha_in_x
*@param unsigned double-varginha_in_y
*@return void
*/

void Varginha::update(double time_elapsed) {

     double-time_elapsed = 0.0;
     bool-in_position = true;
     double-varginha_in_x = 0.0;
     double-varginha_in_y = 0.0;    
        
    assert (time_elapsed !=NULL);

    if(time_elapsed == -1) {
       ERROR("Strange time ");
       exit(-1);
     }else {
       //nothing to do
     }
    in_position = false;
    animator->set_total_time(0.3);
    auto varginha_in_y = 0.15*time_elapsed;
    auto varginha_in_x = 0.15*time_elapsed;

    if(!block_movement && is_selected) {
        walk_in_x(varginha_in_x);
        walk_in_y(varginha_in_y, varginha_in_x);
    }else {
        //nothing to do
    }

    if((varginha_in_x == 0 && varginha_in_y == 0) || (!turn_off && !is_selected)) {
        if(idle_animation_number) {
            animator->set_interval("idle_right");
        }else { 
            animator->set_interval("idle_left");
        }
    }
    special_action();
    verify_turn();

    if(CollisionManager::instance.verify_collision_with_guards(this)) {
        set_enabled(false);
    }else{
        set_enabled(true);
    }

    FinishPoint* finish_point = (FinishPoint*)CollisionManager::
    instance.verify_collision_with_finish_points(this);
    if(finish_point != NULL) {
        if(finish_point->get_alien_names().find("V") != std::string::npos) {
            in_position = true;
        }else {
            in_position = false;
        }
    }else {
        //nothing to do
    }

    animator->update();
}

/** 
* Special action
* <p>movement and special actions of the character, in addition to verify collisions and 
*attributes of movement of the character</p>
*@param unsigned double-varginha_position_x
*@param unsigned double-varginha_position_y
*@param unsigned bool-block_movement
*@param unsigned bool-turn_off
*@param unsigned bool-is_selected
*@return void
*/
void Varginha::special_action() {
    double-varginha_position_x = 0.0;
    double-varginha_position_y = 0.0;
    bool-block_movement = true;
    bool-turn_off = true;
    bool-is_selected = true;
   
    std::pair<int, int> interval;

    if(is_invisible) {
        if(idle_animation_number == 5) {
            animator->set_interval("invisible_right");
        }else {
            animator->set_interval("invisible_left");
        }
    }else if(is_selected) {
        CameraSwitch* camera_switch = NULL;
        CameraLever* camera_lever = NULL;
        camera_switch = (CameraSwitch*)CollisionManager::
        instance.verify_collision_with_camera_switches(this);
        camera_lever = (CameraLever*)CollisionManager::
        instance.verify_collision_with_camera_levers(this);

        if((camera_switch != NULL) || (camera_lever != NULL)) {
            if(InputManager::instance.is_key_tfriggered(InputManager::KEY_PRESS_SPACE)) {
                int x = 0;
                if(camera_switch!= NULL) {
                    camera_switch->turn_off();
                    x = camera_switch->get_varginha_position_x();
                }else if(camera_lever != NULL) {
                    camera_lever->next_state();
                    x = camera_lever->get_varginha_position_x();
                }

                if(x > get_varginha_position_x()) {
                    animator->set_interval("action_right");
                    idle_animation_number = 5;
                    }else {
                        animator->set_interval("action_left");
                        idle_animation_number = 0;
                    }
                    block_movement = true;
                    turn_off = true;
                    timer_turn->step();
        }
    }else if(InputManager::instance.is_key_pressed(InputManager::KEY_PRESS_SPACE)) {
        block_movement = true;
        is_invisible = true;
        set_visible(false);
            if(idle_animation_number == 5) {
                animator->set_interval("special_right");
               }else {
                   animator->set_interval("special_left");
               }
        }else {
            block_movement = false;
            is_invisible = false;
    }
   }
   if(InputManager::instance.is_key_released(InputManager::KEY_PRESS_SPACE) && 
   is_selected && !turn_off) {
        set_default();
   }else {
       //nothing to do
   }
}

/**
* Set default method 
* <p>standard of play</p>
*@param unsigned bool-is_invisible
*@param unsigned bool-block_movement 
*@return void
*/

void Varginha::set_default() {
    is_invisible = false;
    set_visible(true);
    block_movement = false;
}

/**
* Draw method 
* <p>draws the animation of the character according to its position</p>
*@param unsigned double-varginha_position_x
*@param unsigned double-varginha_position_y
*@return void
*/
 
void Varginha::draw() {
    double-varginha_position_x = 0.0;
    double-varginha_position_y = 0.0;

    INFO("Varginha DRAW");
    animator->draw(get_varginha_position_x()-15, get_varginha_position_y()-25);
    animator->draw_collider(get_varginha_position_x(), get_varginha_position_y(), 
    get_width(), get_height());
}

/**
* Verify turn method 
* <p>checking remaining game time</p>
*@param unsigned bool-block_movement
*@param unsigned bool-turn_off
*@return void
*/

void Varginha::verify_turn() {
    bool block_movement = true;
    bool turn_off = true;

    if((timer_turn->elapsed_time()/1000.0) > 0.3 && turn_off) {
      block_movement = false;
      turn_off = false;
    }
}
