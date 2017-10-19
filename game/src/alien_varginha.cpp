//#define NDEBUG *uncomment to disable assertions
#include "alien_varginha.hpp"
#include <assert.h>

#define FILENAME "assets/sprites/varginha_sheet.png"
#define WIDTH 10
#define HEIGHT 15
#define SCREEN_WIDTH 1000
#define SCREEN_INITIAL 0
#define SPECIAL_LEFT "special_left"
#define SPRITE_INITIAL_SPECIAL_LEFT 10
#define SPRITE_FINAL_SPECIAL_LEFT 11
#define SPECIAL_RIGHT "special_right"
#define SPRITE_INITIAL_SPECIAL_RIGHT 12
#define SPRITE_FINAL_SPECIAL_RIGHT 13
#define INVISIBLE_SPECIAL_LEFT "invisible_left"
#define SPRITE_INITIAL_INVISIBLE_LEFT 11
#define SPRITE_FINAL_INVISIBLE_LEFT 11
#define INVISIBLE_SPECIAL_RIGHT "invisible_right"
#define SPRITE_INITIAL_INVISIBLE_RIGHT 13
#define SPRITE_FINAL_INVISIBLE_RIGHT 13
#define ACTION_SPECIAL_LEFT "action_left"
#define ACTION_INITIAL_LEFT 14
#define ACTION_FINAL_LEFT 16 
#define ACTION_SPECIAL_RIGHT "action_right"
#define ACTION_INITIAL_RIGHT 17
#define ACTION_FINAL_RIGHT 19 
#define TOTAL_TIME_1 0.3
#define VELOCITY_VARGINHA 0.15
#define ACTION_IDLE_LEFT "idle_left"
#define ACTION_IDLE_RIGHT "idle_right"
#define NAME_CHARACTER "V"
#define ANIMATION_NUMBER_1 5
#define ANIMATION_NUMBER_2 0
#define CENTER_CHARACTER_1 15
#define CENTER_CHARACTER_2 25


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

    // Verifies the position x of the character Varginha
    if(varginha_position_x > SCREEN_WIDTH || varginha_position_x < SCREEN_INITIAL) {
        ERROR("Strange Varginha position x");
        exit(-1);
    }else {
       //nothing to do
    }
    // Verifies the position y of the character Varginha
    if(varginha_position_y > SCREEN_WIDTH || varginha_position_y < SCREEN_INITIAL) {
       ERROR("Strange Varginha position y");
       exit(-1);
     }else {
       //nothing to do
     }

    animator->add_action(SPECIAL_RIGHT,SPRITE_INITIAL_SPECIAL_RIGHT,SPRITE_FINAL_SPECIAL_RIGHT);
    animator->add_action(SPECIAL_LEFT,SPRITE_INITIAL_SPECIAL_LEFT,SPRITE_FINAL_SPECIAL_LEFT);
    animator->add_action(INVISIBLE_SPECIAL_RIGHT,SPRITE_INITIAL_INVISIBLE_RIGHT,
    SPRITE_FINAL_INVISIBLE_RIGHT);
    animator->add_action(INVISIBLE_SPECIAL_LEFT,SPRITE_INITIAL_INVISIBLE_LEFT,
    SPRITE_FINAL_INVISIBLE_LEFT);
    animator->add_action(ACTION_SPECIAL_RIGHT,ACTION_INITIAL_RIGHT,ACTION_FINAL_RIGHT);
    animator->add_action(ACTION_SPECIAL_LEFT,ACTION_INITIAL_LEFT,ACTION_FINAL_LEFT);
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
    
    //check the elapsed time
    if(time_elapsed == -1) {
       ERROR("Strange time ");
       exit(-1);
     }else {
       //nothing to do
     }
    in_position = false;
    animator->set_total_time(TOTAL_TIME_1);
    auto varginha_in_y = VELOCITY_VARGINHA*time_elapsed;
    auto varginha_in_x = VELOCITY_VARGINHA*time_elapsed;

    //checks conditions to move the player Varginha 
    if(!block_movement && is_selected) {
        walk_in_x(varginha_in_x);
        walk_in_y(varginha_in_y, varginha_in_x);
    }else {
        //nothing to do
    }

    //Chech if instance was selected
    if((varginha_in_x == 0 && varginha_in_y == 0) || (!turn_off && !is_selected)) {
        
        // If idle_animation_number true, receives actions
        if(idle_animation_number) {
            animator->set_interval(ACTION_IDLE_RIGHT);
        //Assigns a default, and animator receives actions
        }else { 
            animator->set_interval(ACTION_IDLE_LEFT);
        }
    }
    special_action();
    verify_turn();
    // If collision, receives actions
    if(CollisionManager::instance.verify_collision_with_guards(this)) {
        set_enabled(false);
    //Assigns a default, and animator receives actions
    }else{
        set_enabled(true);
    }

    FinishPoint* finish_point = (FinishPoint*)CollisionManager::
    instance.verify_collision_with_finish_points(this);
    //Check if the finish point is different from null
    if(finish_point != NULL) {
        if(finish_point->get_alien_names().find(NAME_CHARACTER) != std::string::npos) {
            in_position = true;
        //Assigns a default in_position true
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

    // Check is_invisible
    if(is_invisible) {
        // Check if idle_animation_number is equals 5
        if(idle_animation_number == ANIMATION_NUMBER_1) {
            animator->set_interval(INVISIBLE_SPECIAL_RIGHT);
        // If you do not receive an action
        }else {
            animator->set_interval(INVISIBLE_SPECIAL_LEFT);
        }
    // Check is_invisible
    }else if(is_selected) {
        CameraSwitch* camera_switch = NULL;
        CameraLever* camera_lever = NULL;
        camera_switch = (CameraSwitch*)CollisionManager::
        instance.verify_collision_with_camera_switches(this);
        camera_lever = (CameraLever*)CollisionManager::
        instance.verify_collision_with_camera_levers(this);
        
        // Check camera_switch is different from null or camera_lever
        if((camera_switch != NULL) || (camera_lever != NULL)) {
            if(InputManager::instance.is_key_tfriggered(InputManager::KEY_PRESS_SPACE)) {
                int x = 0;
                // Check camera_switch is different from null
                if(camera_switch!= NULL) {
                    camera_switch->turn_off();
                    x = camera_switch->get_varginha_position_x();
                 // Check camera_lever is different from null
                }else if(camera_lever != NULL) {
                    camera_lever->next_state();
                    x = camera_lever->get_varginha_position_x();
                }
                 // Check x it's bigger than get_varginha_position_x
                if(x > get_varginha_position_x()) {
                    animator->set_interval(ACTION_SPECIAL_RIGHT);
                    idle_animation_number = ANIMATION_NUMBER_1;
                    // If you do not receive an action
                    }else {
                        animator->set_interval(ACTION_SPECIAL_LEFT);
                        idle_animation_number = ANIMATION_NUMBER_2;
                    }
                    block_movement = true;
                    turn_off = true;
                    timer_turn->step();
        }
    }else if(InputManager::instance.is_key_pressed(InputManager::KEY_PRESS_SPACE)) {
        block_movement = true;
        is_invisible = true;
        set_visible(false);
            // Check if animation_number is equals 5
            if(idle_animation_number == ANIMATION_NUMBER_1) {
                animator->set_interval(SPECIAL_RIGHT);
               // If you do not receive an action
               }else {
                   animator->set_interval(SPECIAL_LEFT);
               }
        // If you do not receive an action
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
    animator->draw(get_varginha_position_x()-CENTER_CHARACTER_1, 
    get_varginha_position_y()-CENTER_CHARACTER_2);
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
    // Check conditions
    if((timer_turn->elapsed_time()/1000.0) > TOTAL_TIME_1 && turn_off) {
      block_movement = false;
      turn_off = false;
    }
}
