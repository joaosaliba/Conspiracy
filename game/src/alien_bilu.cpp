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
    assert (bilu_position_x !=NULL);
    assert (bilu_position_y !=NULL);
    assert (WIDTH !=NULL);
    assert (WIDTH > 19);
    assert (HEIGHT !=NULL);
    assert (HEIGHT > 22);
    if(bilu_position_x > 1000 || bilu_position_x < 0) {
        ERROR("Strange Bilu position x");
        exit(-1);
    }else {
       //nothing to do
    }
    if(bilu_position_y > 1000 || bilu_position_y < 0) {
       ERROR("Strange Bilu position y");
       exit(-1);
     }else {
       //nothing to do
     }
    if(WIDTH > 19 || WIDTH < 0) {
       ERROR("Strange width");
       exit(-1);
     }else {
       //nothing to do
     }
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
    assert ( time_elapsed != NULL);

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

    if(!block_movement && is_selected) {
        walk_in_x(move_bilu_in_x);
        walk_in_y(move_bilu_in_y, move_bilu_in_x);
    }else {
        //nothing to do
    }

    if(move_bilu_in_x == 0 && move_bilu_in_y == 0) {
        if(idle_animation_number) {
            animator->set_interval("idle_right");
        }else {
            animator->set_interval("idle_left");

        if(move_bilu_in_x == 0 && move_bilu_in_y == 0) {
                if(idle_animation_number) {
                        animator->set_interval("idle_right");
                }else {
                        animator->set_interval("idle_left");
                }
        else{
                //nothing to do
            }    
        }
}
    special_action();

    if(CollisionManager::instance.verify_collision_with_guards(this) ||
    CollisionManager::instance.verify_collision_with_cameras(this)) {
        setEnabled(false);
        }else {
            setEnabled(true);          
    }
    FinishPoint* finish_point = (FinishPoint*)
    CollisionManager::instance.verify_collision_with_finish_points(this);
    if(finish_point != NULL) {
        if(finish_point->get_alien_names().find("B") != std::string::npos) {
            in_position = true;
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
    std::pair<int, int> interval;

    GameObject* paper = CollisionManager::instance.verify_collision_with_papers(this);
    GameObject* doorSwitch = CollisionManager::instance.verify_collision_with_switches(this);

    if(InputManager::instance.is_key_pressed(InputManager::KEY_PRESS_SPACE) && is_selected) {
    // Paper interaction
        if(paper != NULL) {
            if(! editing) {
                editing = true;
                block_movement = true;
                ((Paper*)(paper))->play_effect();
            }else {
                editing = false;
                block_movement = false;
            }
        }else {
            //nothing to do
        }
    // PC interaction
        if(doorSwitch != NULL) {
            if(!hacking) {
                hacking = true;
                block_movement = true;
                ((DoorSwitch*)(doorSwitch))->play_effect();
            }else {
                hacking = false;
                block_movement = false;
            }
        }else{
            //nothing to do
        }
}else if(InputManager::instance.is_key_pressed(InputManager::KEY_PRESS_ESC)&& is_selected) {
    if(hacking) {
        hacking = false;
        block_movement = false;
        ((DoorSwitch*)(doorSwitch))->stop_effect();
        ((DoorSwitch*)(doorSwitch))->stop_animation();
        ((DoorSwitch*)(doorSwitch))->reset_hacking_progress();
        }else if (editing) {
            editing = false;
            block_movement = false;
            ((Paper*)(paper))->stop_effect();
            ((Paper*)(paper))->stop_animation();
            ((Paper*)(paper))->reset_editing_progress();
        }
}

    if(hacking) {
        ((DoorSwitch*)(doorSwitch))->animate();
        set_special_action_animator();
            if(((DoorSwitch*)(doorSwitch))->get_hacking_bar_percent() <= 0.0) {
                hacking = false;
                ((DoorSwitch*)(doorSwitch))->stop_animation();
                ((DoorSwitch*)(doorSwitch))->stop_effect();
                ((DoorSwitch*)(doorSwitch))->reset_hacking_progress();
                Alien::animator->set_interval("idle");
                block_movement = false;
            }else {
                hacking = true;
                block_movement = true;
            }
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
    if(idle_animation_number == 5) {
        animator->set_interval("special_right");
    }else {
        animator->set_interval("special_left");
    }
        animator->set_total_time(0.6);
}