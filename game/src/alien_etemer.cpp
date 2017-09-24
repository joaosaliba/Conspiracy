#include "alien_etemer.hpp"
#include "chair.hpp"
#include "guard.hpp"
#include <assert.h>

#define FILENAME "assets/sprites/etemer_sheet.png"
#define WIDTH 10
#define HEIGHT 22

/** objects included in the alien_etemer.hpp, guard.hpp classes found on lines 1 to
* line 3, where the methods will be responsible for the manipulation and organization 
* of these objects
*/

Etemer::Etemer(double etemer_position_x, double etemer_position_y) : 
Alien(FILENAME, etemer_position_x, etemer_position_y, WIDTH, HEIGHT) {
    assert (etemer_position_x !=NULL);
    assert (etemer_position_y !=NULL);
    assert (WIDTH !=NULL);
    assert (HEIGHT !=NULL);
    
    animator->add_action("special_right",14,17);
    animator->add_action("special_left",10,13);

    is_selected = true;
    talking = false;
    in_position = false;
}

/** 
*   movement and special actions of the character, in addition to checking the finishi point
*   @return void
*/

void Etemer::update(double time_elapsed) {
    assert (time_elapsed !=NULL);

    in_position = false;
    if (block_movement) {
        animator->set_total_time(1.0);
}else {
    animator->set_total_time(0.3);
}

    auto etemer_in_y = 0.15*time_elapsed;
    auto etemer_in_x = 0.15*time_elapsed;

    if(!block_movement && is_selected) {
        walk_in_x(etemer_in_x);
        walk_in_y(etemer_in_y, etemer_in_x);
}

    if(etemer_in_x == 0.0 && etemer_in_y == 0.0 && !block_movement) {
        if(idle_animation_number) {
            animator->set_interval("idle_right");
}else {
    animator->set_interval("idle_left");
}
}        

   FinishPoint* finish_point = (FinishPoint*)CollisionManager::
   instance.verify_collision_with_finish_points(this);
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

/** 
*   movement and special actions of the character, in addition to verify collisions and 
*   attributes of movement of the character
*   @return void
*/

void Etemer::special_action(GameObject * guard, double etemer_distance) {
    assert (etemer_distance !=NULL);

    if(InputManager::instance.is_key_pressed(InputManager::KEY_PRESS_SPACE) &&
    guard != NULL && is_selected) {
        animator->set_total_time(1.0);
        //TODO Change etemer_distance.
        if(!talking && etemer_distance < 60) {
            talking = true;
            block_movement = true;
        if(((Guard *) (guard))->get_position_x() > get_position_x()) {
                ((Guard *)(guard))->talking_to_etemer("left");
}else {
    ((Guard *)(guard))->talking_to_etemer("right");
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
    if(((Guard *) (guard))->get_talking_bar_percent() <= 0.0) {
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

/** 
*   draws the animation of the character according to its position
*   @return void
*/

void Etemer::draw() {
    INFO("Etemer DRAW");
    animator->draw(get_position_x()-15, get_position_y()-20);
    animator->draw_collider(get_position_x(), get_position_y(), get_width(), get_heigth());
}

/** 
*   character move
*   @return void
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
    }
}

/** 
*   Creates animations of movement and collision in X in the game
*   @return void
*/

void Etemer::walk_in_x(double & etemer_in_x) {
    assert (etemer_in_x !=NULL);

    if(InputManager::instance.is_key_pressed(InputManager::KeyPress::KEY_PRESS_RIGHT)) {
        etemer_in_x = etemer_in_x;
        idle_animation_number = 5;
        animator->set_interval("right");
}
    else if(InputManager::instance.is_key_pressed(InputManager::KeyPress::KEY_PRESS_LEFT)) {
        //movement_sound_effect->play(-1);
        etemer_in_x = etemer_in_x * (0-1);
        idle_animation_number = 0;
        animator->set_interval("left");
}
    else {
        etemer_in_x = 0;
}
    set_position_x(get_position_x()+etemer_in_x);

    if(CollisionManager::instance.verify_collision_with_walls_and_chairs(this)) {
        set_position_x(get_position_x()+(etemer_in_x*(0-1)));
    }
}

/** 
*   Creates animations of movement and collision in Y in the game
*   @return void
*/

void Etemer::walk_in_y(double & etemer_in_y, double etemer_in_x) {
    assert (etemer_in_y !=NULL);
    assert (etemer_in_x !=NULL);

    if(InputManager::instance.is_key_pressed(InputManager::KeyPress::KEY_PRESS_UP)) {
        etemer_in_y = etemer_in_y * (0-1);
        idle_animation_number = 5;
            if(etemer_in_x == 0) {
                animator->set_interval("up");
    }
}
    else if(engine::InputManager::instance.is_key_pressed(engine::InputManager::KeyPress::
    KEY_PRESS_DOWN)) {
        etemer_in_y = etemer_in_y;
        idle_animation_number = 0;
            if(etemer_in_x == 0) {
                animator->set_interval("down");
    }
}
    else {
        etemer_in_y = 0;
}
    set_position_y(get_position_y()+etemer_in_y);

    if(CollisionManager::instance.verify_collision_with_walls_and_chairs(this)) {
        set_position_y(get_position_y()+(etemer_in_y*(0-1)));
    }
}

/** 
*   check the guards' etemer_distance
*   @return void
*/

void Etemer::verify_etemer_distance(GameObject* guard) {
    double etemer_distance = sqrt((pow(get_position_x() - guard->get_position_x(), 2.0)) +  
    (pow(get_position_y() - guard->get_position_y(), 2.0)));

    if(etemer_distance < 60){
        special_action(guard, etemer_distance);
    }
}
