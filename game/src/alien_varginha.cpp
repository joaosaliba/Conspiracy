#include "alien_varginha.hpp"

#define FILENAME "assets/sprites/varginha_sheet.png"
#define WIDTH 10
#define HEIGHT 15

/** objects included in the alien_varginha.hpp 
* where the methods will be responsible for the manipulation and organization 
* of these objects
*/

Varginha::Varginha(double position_x, double position_y) : 
Alien(FILENAME, position_x, position_y, WIDTH, HEIGHT) {

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
*   movement and special actions of the character, in addition to checking the finishi point
*   @return void
*/

void Varginha::update(double time_elapsed) {
    in_position = false;
    animator->set_total_time(0.3);
    auto inc_y = 0.15*time_elapsed;
    auto inc_x = 0.15*time_elapsed;

    if(!block_movement && is_selected) {
        walk_in_x(inc_x);
        walk_in_y(inc_y, inc_x);
    }

    if((inc_x == 0 && inc_y == 0) || (!turn_off && !is_selected)) {
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
    }

    FinishPoint* finish_point = (FinishPoint*)CollisionManager::
    instance.verify_collision_with_finish_points(this);
    if(finish_point != NULL) {
        if(finish_point->get_alien_names().find("V") != std::string::npos) {
            in_position = true;
        }
    }

    animator->update();
}

/** 
*   movement and special actions of the character, in addition to verify collisions and 
*   attributes of movement of the character
*   @return void
*/

void Varginha::special_action() {
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
                    x = camera_switch->get_position_x();
                }else if(camera_lever != NULL) {
                    camera_lever->next_state();
                    x = camera_lever->get_position_x();
                }

                if(x > get_position_x()) {
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
    }
   }
   if(InputManager::instance.is_key_released(InputManager::KEY_PRESS_SPACE) && 
   is_selected && !turn_off) {
        set_default();
   }
}

/** 
*   standard of play 
*   @return void
*/

void Varginha::set_default() {
    is_invisible = false;
    set_visible(true);
    block_movement = false;
}

/** 
*   draws the animation of the character according to its position
*   @return void
*/
 
void Varginha::draw() {
    INFO("Varginha DRAW");
    animator->draw(get_position_x()-15, get_position_y()-25);
    animator->draw_collider(get_position_x(), get_position_y(), get_width(), get_height());
}

/** 
*   checking remaining game time
*   @return void
*/

void Varginha::verify_turn() {
    if((timer_turn->elapsed_time()/1000.0) > 0.3 && turn_off) {
      block_movement = false;
      turn_off = false;
    }
}
