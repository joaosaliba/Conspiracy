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
*/

Bilu::Bilu(double bilu_position_x, double bilu_position_y) : 
Alien(FILENAME, bilu_position_x, bilu_position_y, WIDTH, HEIGHT) {
    assert (bilu_position_x !=NULL);
    assert (bilu_position_y !=NULL);
    assert (WIDTH !=NULL);
    assert (HEIGHT !=NULL);

    animator->add_action("special_right",14,17);
    animator->add_action("special_left",10,13);
    
    hacking = false;
    editing = false;
    last_action = false;
    is_selected = false;
    in_position = false;
}

/** 
*   movement and special actions of the character, in addition to checking the finishi point
*   @return void
*/

void Bilu::update(double time_elapsed) {
    assert ( time_elapsed != NULL);
    
    in_position = false;
    animator->set_total_time(0.3);
    auto move_bilu_in_y = 0.15*time_elapsed;
    auto move_bilu_in_x = 0.15*time_elapsed;

    if(!block_movement && is_selected) {
        walk_in_x(move_bilu_in_x);
        walk_in_y(move_bilu_in_y, move_bilu_in_x);
}

<<<<<<< HEAD
    if(move_bilu_in_x == 0 && move_bilu_in_y == 0) {
        if(idle_animation_number) {
            animator->set_interval("idle_right");
        }else {
            animator->set_interval("idle_left");
=======
        if(inc_x == 0 && inc_y == 0) {
                if(idle_animation_number) {
                        animator->setInterval("idle_right");
                }else {
                        animator->setInterval("idle_left");
                }
>>>>>>> origin/Development
        }
}
    special_action();

    if(CollisionManager::instance.verify_collision_with_guards(this) || 
    CollisionManager::instance.verify_collision_with_cameras(this)) {
        set_enabled(false);
}
    FinishPoint* finish_point = (FinishPoint*)
    CollisionManager::instance.verify_collision_with_finish_points(this);
    if(finish_point != NULL) {
        if(finish_point->get_alien_names().find("B") != std::string::npos) {
            in_position = true;
        }
}

    animator->update();
}

/** 
*   verifies the interaction of both paper and pc
*   @return void
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
            }
        }
    // PC interaction
        if(doorSwitch != NULL) {
            if(!hacking) {
                hacking = true;
                block_movement = true;
                ((DoorSwitch*)(doorSwitch))->play_effect();
            }
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
            }
}else if(editing) {
    ((Paper*)(paper))->animate();
    setspecial_action_animator();
        if(((Paper*)(paper))->get_editing_bar_percent() <= 0.0) {
            editing = false;
            ((Paper*)(paper))->stop_animation();
            //((Paper*)(paper))->stop_effect();
            ((Paper*)(paper))->reset_editing_progress();
            Alien::animator->set_interval("idle");
            block_movement = false;
        }
}
    last_action = hacking;
}

/** 
*   draws the animation of the character according to its position
*   @return void
*/

void Bilu::draw() {
    INFO("Bilu DRAW");
    animator->draw(get_position_x()-11, get_position_y()-20);
    animator->draw_collider(get_position_x(), get_position_y(), get_width(), get_height());
}

<<<<<<< HEAD
/** 
*   special character animation
*   @return void
*/

void Bilu::set_special_action_animator() {
    if(idle_animation_number == 5) {
        animator->set_interval("special_right");
    }else {
        animator->set_interval("special_left");
    }
        animator->set_total_time(0.6);
=======
void Bilu::setSpecialActionAnimator() {
        if(idle_animation_number == 5) {
                animator->setInterval("special_right");
        }else {
                animator->setInterval("special_left");
        }
        animator->setTotalTime(0.6);
>>>>>>> origin/Development
}
