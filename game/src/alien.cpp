#include "alien.hpp"

Alien::Alien(std::string objectName, double position_x, double position_y,
                                     int width, int height) : GameObject(objectName,
                                                                         position_x,
                                                                         position_y,
                                                                         width, height) {
    if(objectName.compare("assets/sprites/bilu_sheet.png") == 0) {
        alienName = "Bilu";
    }else if(objectName.compare("assets/sprites/varginha_sheet.png") == 0) {
        alienName = "Varginha";

    }else if(objectName.compare("assets/sprites/etemer_sheet.png") == 0) {
        alienName = "Etemer";
    }
    animator = new Animation(objectName, 2, 10, 0.5);

    animator->add_action("right",6,9);
    animator->add_action("left",1,4);
    animator->add_action("up",6,9);
    animator->add_action("down",1,4);
    animator->add_action("idle_right",5,5);
    animator->add_action("idle_left",0,0);
    animator->add_action("idle_up",5,5);
    animator->add_action("idle_down",0,0);

    idle_animation_number = 5;
    block_movement = false;
    in_position = false;
    movement_sound_effect = new Audio("assets/sounds/FOOTSTEP.wav", "EFFECT", 128);
}

Alien::~Alien() {}

void Alien::walk_in_x(double & inc_x) {

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

void Alien::walk_in_y(double & inc_y, double inc_x) {

    if(InputManager::instance.is_key_pressed(InputManager::KeyPress::KEY_PRESS_UP)) {
        inc_y = inc_y * (0-1);
        idle_animation_number = 5;
        if(inc_x == 0){
            animator->set_interval("up");
        }
    }
    else if(engine::InputManager::instance.is_key_pressed(engine::InputManager::KeyPress::KEY_PRESS_DOWN)) {
        inc_y = inc_y;
        idle_animation_number = 0;
        if(inc_x == 0){
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

void Alien::draw() {
    INFO("ALIEN DRAW");
    animator->draw(get_position_x(), get_position_y());
}

Animation * Alien::getAnimation() {
  return animator;
}

void Alien::setAlienSelected() {
    is_selected = true;
}

void Alien::setAlienDeselect() {
    is_selected = false;
}

bool Alien::isInPosition() {
    return in_position;
}
