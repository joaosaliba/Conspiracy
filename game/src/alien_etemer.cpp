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

Etemer::Etemer(double position_x, double position_y) : Alien(FILENAME, position_x, position_y, WIDTH, HEIGHT) {
        animator->add_action("special_right",14,17);
        animator->add_action("special_left",10,13);

        is_selected = true;
        talking = false;
        in_position = false;
}

void Etemer::update(double time_elapsed) {
        in_position = false;
        if (block_movement) {
                animator->set_total_time(1.0);
        }else {
                animator->set_total_time(0.3);
        }

        auto inc_y = 0.15*time_elapsed;
        auto inc_x = 0.15*time_elapsed;

        if(!block_movement && is_selected) {
                walk_in_x(inc_x);
                walk_in_y(inc_y, inc_x);
        }

        if(inc_x == 0.0 && inc_y == 0.0 && !block_movement) {
                if(idle_animation_number) {
                        animator->set_interval("idle_right");
                }else {
                        animator->set_interval("idle_left");
                }
        }

        FinishPoint* finish_point = (FinishPoint*)CollisionManager::instance.verify_collision_with_finish_points(this);
        if(finish_point != NULL) {
            if(finish_point->get_alien_names().find("E") != std::string::npos) {
                in_position = true;
            }
        }

        move_chair();

        if(CollisionManager::instance.verify_collision_with_cameras(this)) {
            set_enabled(false);
        }
        animator->update();
}
void Etemer::special_action(GameObject * guard, double distance) {
        if(InputManager::instance.is_key_pressed(InputManager::KEY_PRESS_SPACE) && guard != NULL && is_selected) {
                animator->set_total_time(1.0);
                //TODO Change distance.
                if(!talking && distance < 60) {
                        talking = true;
                        block_movement = true;
                        if(((Guard *) (guard))->get_position_x() > get_position_x()) {
                                ((Guard *)(guard))->talkingToETemer("left");
                        }else {
                                ((Guard *)(guard))->talkingToETemer("right");
                        }
                }

        }

        if(talking) {
                if(((Guard *) (guard))->get_position_x() >= get_position_x()) {
                        animator->set_interval("special_right");
                        idle_animation_number = 5;
                }else {
                        animator->set_interval("special_left");
                        idle_animation_number = 0;
                }
                if(((Guard *) (guard))->getTalkingBarPercent() <= 0.0) {
                        talking = false;
                        block_movement = false;
                        if(idle_animation_number) {
                                animator->set_interval("idle_right");
                        }else{
                                animator->set_interval("idle_left");
                        }
                }
        }
}

void Etemer::draw() {
        INFO("Etemer DRAW");
        animator->draw(get_position_x()-15, get_position_y()-20);
        animator->draw_collider(get_position_x(), get_position_y(), get_width(), get_height());
}

void Etemer::move_chair() {
        std::pair<std::string, GameObject *> chair = CollisionManager::instance.verify_collisionWithChairs(this);
        if(chair.second != NULL) {
                if(animator->getInterval().first == chair.first) {
                        ((Chair *) (chair.second))->setMoving(true);
                        ((Chair *) (chair.second))->setDirection(chair.first);
                }else {
                        ((Chair *) (chair.second))->setMoving(false);
                }
        }
}


void Etemer::walk_in_x(double & inc_x) {

        if(InputManager::instance.is_key_pressed(InputManager::KeyPress::KEY_PRESS_RIGHT)) {
                inc_x = inc_x;
                idle_animation_number = 5;
                animator->set_interval("right");
        }
        else if(InputManager::instance.is_key_pressed(InputManager::KeyPress::KEY_PRESS_LEFT)) {
                //movement_sound_effect->play(-1);
                inc_x = inc_x * (0-1);
                idle_animation_number = 0;
                animator->set_interval("left");
        }
        else {
                inc_x = 0;
        }
        setposition_x(get_position_x()+inc_x);

        if(CollisionManager::instance.verify_collisionWithWallsAndChairs(this)) {
                setposition_x(get_position_x()+(inc_x*(0-1)));
        }
}

void Etemer::walk_in_y(double & inc_y, double inc_x) {

        if(InputManager::instance.is_key_pressed(InputManager::KeyPress::KEY_PRESS_UP)) {
                inc_y = inc_y * (0-1);
                idle_animation_number = 5;
                if(inc_x == 0) {
                        animator->set_interval("up");
                }
        }
        else if(engine::InputManager::instance.is_key_pressed(engine::InputManager::KeyPress::KEY_PRESS_DOWN)) {
                inc_y = inc_y;
                idle_animation_number = 0;
                if(inc_x == 0) {
                        animator->set_interval("down");
                }
        }
        else {
                inc_y = 0;
        }
        setposition_y(get_position_y()+inc_y);

        if(CollisionManager::instance.verify_collisionWithWallsAndChairs(this)) {
                setposition_y(get_position_y()+(inc_y*(0-1)));
        }
}

void Etemer::verify_distance(GameObject* guard){
        double distance = sqrt((pow(get_position_x() - guard->get_position_x(), 2.0)) +  (pow(get_position_y() - guard->get_position_y(), 2.0)));

        if(distance < 60){
            special_action(guard, distance);
        }
}
