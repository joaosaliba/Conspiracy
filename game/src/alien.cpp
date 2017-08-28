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

    animator->addAction("right",6,9);
    animator->addAction("left",1,4);
    animator->addAction("up",6,9);
    animator->addAction("down",1,4);
    animator->addAction("idle_right",5,5);
    animator->addAction("idle_left",0,0);
    animator->addAction("idle_up",5,5);
    animator->addAction("idle_down",0,0);

    idleAnimationNumber = 5;
    block_movement = false;
    in_position = false;
    movement_sound_effect = new Audio("assets/sounds/FOOTSTEP.wav", "EFFECT", 128);
}

Alien::~Alien() {}

void Alien::walkInX(double & inc_x) {

    if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_RIGHT)) {
        inc_x = inc_x;
        idleAnimationNumber = 5;
        animator->setInterval("right");
    }
    else if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_LEFT)) {
        //movement_sound_effect->play(-1);
        inc_x = inc_x * (0-1);
        idleAnimationNumber = 0;
        animator->setInterval("left");
    }
    else {
        inc_x = 0;
    }
    setPositionX(getPositionX()+inc_x);
    if(CollisionManager::instance.verifyCollisionWithWallsAndChairs(this)) {
        setPositionX(getPositionX()+(inc_x*(0-1)));
    }
}

void Alien::walkInY(double & inc_y, double inc_x) {

    if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_UP)) {
        inc_y = inc_y * (0-1);
        idleAnimationNumber = 5;
        if(inc_x == 0){
            animator->setInterval("up");
        }
    }
    else if(engine::InputManager::instance.isKeyPressed(engine::InputManager::KeyPress::KEY_PRESS_DOWN)) {
        inc_y = inc_y;
        idleAnimationNumber = 0;
        if(inc_x == 0){
            animator->setInterval("down");
        }
    }
    else {
        inc_y = 0;
    }
    setPositionY(getPositionY()+inc_y);
    if(CollisionManager::instance.verifyCollisionWithWallsAndChairs(this)) {
        setPositionY(getPositionY()+(inc_y*(0-1)));
    }
}

void Alien::draw() {
    INFO("ALIEN DRAW");
    animator->draw(getPositionX(), getPositionY());
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
