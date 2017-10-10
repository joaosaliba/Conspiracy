//#define NDEBUG *uncomment to disable assertions
#include "alien_bilu.hpp"
#include "collision_manager.hpp"
#include "paper.hpp"
#include "door_switch.hpp"
#include <assert.h>

#define FILENAME "assets/sprites/bilu_sheet.png"
#define WIDTH 19
#define HEIGHT 22

/** Objects included in the alien_bilu.hpp, door_switch.hpp classes found on lines 1 to
* line 4, where the methods will be responsible for the manipulation and organization
* of these objects
*@param unsigned double-bilu_position_x
*@param unsigned double-bilu_position_y
*@param unsigned bool-hacking
*@param unsigned bool-editing
*@param unsigned bool-last_action
*@param unsigned bool-is_selected
*@param unsigned bool-in_position
*/

Bilu::Bilu(double bilu_position_x, double bilu_position_y) :
Alien(FILENAME, bilu_position_x, bilu_position_y, WIDTH, HEIGHT) {
   
    double bilu_position_x = 0.0;
    double bilu_position_y = 0.0;
    bool hacking = true;
    bool editing = true;
    bool last_action = true;
    bool is_selected = true;
    bool in_position = true;  
   
    assert (bilu_position_x !=NULL);
    assert (bilu_position_y !=NULL);
    assert (WIDTH !=NULL);
    assert (WIDTH > 19);
    assert (HEIGHT !=NULL);
    assert (HEIGHT > 22);
    
    //verifies the position x of the character Bilu
    if(bilu_position_x > 1000 || bilu_position_x < 0) {
        ERROR("Strange Bilu position x");
        exit(-1);
    }else {
       //nothing to do
    }

    //verifies the position y of the character Bilu
    if(bilu_position_y > 1000 || bilu_position_y < 0) {
       ERROR("Strange Bilu position y");
       exit(-1);
     }else {
       //nothing to do
     }

    //verifies the width of the character Bilu
    if(WIDTH > 19 || WIDTH < 0) {
       ERROR("Strange width");
       exit(-1);
     }else {
       //nothing to do
     }

    //verifies the height of the character Bilu 
    if(HEIGHT > 22 || HEIGHT < 0) {
       ERROR("Strange height");
       exit(-1);
     }else {
       //nothing to do
     }          
    animator->add_action("special_right",14,17);
    animator->add_action("special_left",10,13);

    hacking = false;
    editing = false;
    last_action = false;
    is_selected = false;
    in_position = false;
}

/**
* Update method
* <p>movement and special actions of the character, in addition to checking the finishi point</p>
*@param unsigned double-time_elapsed
*@param unsigned bool-in_position
*@return void
*/

void Bilu::update(double time_elapsed) {
    
    double time_elapsed = 0.0;
    bool in_position = true;
    
    assert ( time_elapsed != NULL);

    //check the elapsed time
    if(time_elapsed == -1) {
       ERROR("Strange time ");
       exit(-1);
     }else {
       //nothing to do
     }

    in_position = false;
    animator->set_total_time(0.3);
    auto move_bilu_in_y = 0.15*time_elapsed;
    auto move_bilu_in_x = 0.15*time_elapsed;

    //checks conditions to move the player Bilu
    if(!block_movement && is_selected) {
        walk_in_x(move_bilu_in_x);
        walk_in_y(move_bilu_in_y, move_bilu_in_x);
    }else {
        //nothing to do
    }

    //check atributes to move the player Bilu
    if(move_bilu_in_x == 0 && move_bilu_in_y == 0) {
        //if idle animation number
        if(idle_animation_number) {
            animator->set_interval("idle_right");
        //Assigns a default animator
        }else {
            animator->set_interval("idle_left");
        //check atributes to move the player Bilu
        if(move_bilu_in_x == 0 && move_bilu_in_y == 0) {
                //if idle animation number
                if(idle_animation_number) {
                        animator->set_interval("idle_right");
                //Assigns a default animator
               }else {
                        animator->set_interval("idle_left");
                }
        else{
                //nothing to do
            }    
        }
}
    special_action();
    
    //Check the collisions with the cameras
    if(CollisionManager::instance.verify_collision_with_guards(this) ||
    CollisionManager::instance.verify_collision_with_cameras(this)) {
        setEnabled(false);
        //Assigns a default true
        }else {
            setEnabled(true);          
    }
    FinishPoint* finish_point = (FinishPoint*)
    CollisionManager::instance.verify_collision_with_finish_points(this);
    
    //Check if the finish point is different from null
    if(finish_point != NULL) {
        if(finish_point->get_alien_names().find("B") != std::string::npos) {
            in_position = true;
        //Assigns a default in_position true
        }else {
            in_position(false);
        }
    }else{
        //nothing to do
    }

    animator->update();
}

/**
* Special action method
* <p>verifies the interaction of both paper and pc</p>
*@param unsigned bool-hacking
*@param unsigned bool-editing
*@return void
*/

void Bilu::special_action() {

    bool hacking = true;
    bool editing = true;

    std::pair<int, int> interval;

    GameObject* paper = CollisionManager::instance.verify_collision_with_papers(this);
    GameObject* doorSwitch = CollisionManager::instance.verify_collision_with_switches(this);

    if(InputManager::instance.is_key_pressed(InputManager::KEY_PRESS_SPACE) && is_selected) {
    // Paper interaction
        if(paper != NULL) {
            // If editing
            if(! editing) {
                editing = true;
                block_movement = true;
                ((Paper*)(paper))->play_effect();
            //Assigns a default editing and block_movement false
            }else {
                editing = false;
                block_movement = false;
            }
        }else {
            //nothing to do
        }
    // PC interaction
        //Check if the door switch is different from null 
        if(doorSwitch != NULL) {
            if(!hacking) {
                hacking = true;
                block_movement = true;
                ((DoorSwitch*)(doorSwitch))->play_effect();
            //Assigns a default hacking and block_movement false
            }else {
                hacking = false;
                block_movement = false;
            }
        }else{
            //nothing to do
        }

//Chech if instance was selected
}else if(InputManager::instance.is_key_pressed(InputManager::KEY_PRESS_ESC)&& is_selected) {
    // If hacking
    if(hacking) {
        hacking = false;
        block_movement = false;
        ((DoorSwitch*)(doorSwitch))->stop_effect();
        ((DoorSwitch*)(doorSwitch))->stop_animation();
        ((DoorSwitch*)(doorSwitch))->reset_hacking_progress();
        //Assigns a default hacking and block_movement false, and paper receives actions
        }else if (editing) {
            editing = false;
            block_movement = false;
            ((Paper*)(paper))->stop_effect();
            ((Paper*)(paper))->stop_animation();
            ((Paper*)(paper))->reset_editing_progress();
        }
}
    // If hacking
    if(hacking) {
        ((DoorSwitch*)(doorSwitch))->animate();
        set_special_action_animator();
            // doorSwitch receives actions
            if(((DoorSwitch*)(doorSwitch))->get_hacking_bar_percent() <= 0.0) {
                hacking = false;
                ((DoorSwitch*)(doorSwitch))->stop_animation();
                ((DoorSwitch*)(doorSwitch))->stop_effect();
                ((DoorSwitch*)(doorSwitch))->reset_hacking_progress();
                Alien::animator->set_interval("idle");
                block_movement = false;
            //Assigns a default hacking and block_movement false
            }else {
                hacking = true;
                block_movement = true;
            }
// If editing receives actions
}else if(editing) {
    ((Paper*)(paper))->animate();
    set_special_action_animator();
        if(((Paper*)(paper))->get_editing_bar_percent() <= 0.0) {
            editing = false;
            ((Paper*)(paper))->stop_animation();
            //((Paper*)(paper))->stop_effect();
            ((Paper*)(paper))->reset_editing_progress();
            Alien::animator->set_interval("idle");
            block_movement = false;
        //Assigns a default hacking and block_movement false    
        }else {
            editing = true;
            block_movement = true;
        }
}
    last_action = hacking;
}

/**
* Draw method
* <p>draws the animation of the character according to its position</p>
*@param unsigned double-bilu_position_x
*@param unsigned double-bilu_position_y
*@return void
*/

void Bilu::draw() {

    double bilu_position_x = 0.0;
    double bilu_position_y = 0.0;

    INFO("Bilu DRAW");
    animator->draw(get_position_x()-11, get_position_y()-20);
    animator->draw_collider(get_position_x(), get_position_y(), get_width(), get_height());
}

/**
* Special action animator
* <p>special character animation</p>
*@return void
*/

void Bilu::set_special_action_animator() {
    // Check if idle_animation_number is equals 5
    if(idle_animation_number == 5) {
        animator->set_interval("special_right");
    // If you do not receive an action
    }else {
        animator->set_interval("special_left");
    }
        animator->set_total_time(0.6);
}