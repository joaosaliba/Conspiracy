#include "alien_etemer.hpp"
#include "chair.hpp"
#include "guard.hpp"

#define FILENAME "assets/sprites/etemer_sheet.png"
#define WIDTH 10
#define HEIGHT 22

Etemer::Etemer(double position_x, double position_y) : Alien(FILENAME, position_x, position_y, WIDTH, HEIGHT) {
        animator->addAction("special_right",14,17);
        animator->addAction("special_left",10,13);

        is_selected = true;
        talking = false;
        in_position = false;
}

void Etemer::update(double time_elapsed) {
        in_position = false;
        if (block_movement) {
                animator->setTotalTime(1.0);
        }else {
                animator->setTotalTime(0.3);
        }

        auto inc_y = 0.15*time_elapsed;
        auto inc_x = 0.15*time_elapsed;

        if(!block_movement && is_selected) {
                walkInX(inc_x);
                walkInY(inc_y, inc_x);
        }

        if(inc_x == 0.0 && inc_y == 0.0 && !block_movement) {
                if(idle_animation_number) {
                        animator->setInterval("idle_right");
                }else {
                        animator->setInterval("idle_left");
                }
        }

        FinishPoint* finish_point = (FinishPoint*)CollisionManager::instance.verifyCollisionWithFinishPoints(this);
        if(finish_point != NULL) {
            if(finish_point->getAlienNames().find("E") != std::string::npos) {
                in_position = true;
            }
        }

        moveChair();

        if(CollisionManager::instance.verifyCollisionWithCameras(this)) {
            setEnabled(false);
        }
        animator->update();
}
void Etemer::specialAction(GameObject * guard, double distance) {
        if(InputManager::instance.isKeyPressed(InputManager::KEY_PRESS_SPACE) && guard != NULL && is_selected) {
                animator->setTotalTime(1.0);
                //TODO Change distance.
                if(!talking && distance < 60) {
                        talking = true;
                        block_movement = true;
                        if(((Guard *) (guard))->getPositionX() > getPositionX()) {
                                ((Guard *)(guard))->talkingToETemer("left");
                        }else {
                                ((Guard *)(guard))->talkingToETemer("right");
                        }
                }

        }

        if(talking) {
                if(((Guard *) (guard))->getPositionX() >= getPositionX()) {
                        animator->setInterval("special_right");
                        idle_animation_number = 5;
                }else {
                        animator->setInterval("special_left");
                        idle_animation_number = 0;
                }
                if(((Guard *) (guard))->getTalkingBarPercent() <= 0.0) {
                        talking = false;
                        block_movement = false;
                        if(idle_animation_number) {
                                animator->setInterval("idle_right");
                        }else{
                                animator->setInterval("idle_left");
                        }
                }
        }
}

void Etemer::draw() {
        INFO("Etemer DRAW");
        animator->draw(getPositionX()-15, getPositionY()-20);
        animator->draw_collider(getPositionX(), getPositionY(), getWidth(), getHeight());
}

void Etemer::moveChair() {
        std::pair<std::string, GameObject *> chair = CollisionManager::instance.verifyCollisionWithChairs(this);
        if(chair.second != NULL) {
                if(animator->getInterval().first == chair.first) {
                        ((Chair *) (chair.second))->setMoving(true);
                        ((Chair *) (chair.second))->setDirection(chair.first);
                }else {
                        ((Chair *) (chair.second))->setMoving(false);
                }
        }
}


void Etemer::walkInX(double & inc_x) {

        if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_RIGHT)) {
                inc_x = inc_x;
                idle_animation_number = 5;
                animator->setInterval("right");
        }
        else if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_LEFT)) {
                //movement_sound_effect->play(-1);
                inc_x = inc_x * (0-1);
                idle_animation_number = 0;
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

void Etemer::walkInY(double & inc_y, double inc_x) {

        if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_UP)) {
                inc_y = inc_y * (0-1);
                idle_animation_number = 5;
                if(inc_x == 0) {
                        animator->setInterval("up");
                }
        }
        else if(engine::InputManager::instance.isKeyPressed(engine::InputManager::KeyPress::KEY_PRESS_DOWN)) {
                inc_y = inc_y;
                idle_animation_number = 0;
                if(inc_x == 0) {
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

void Etemer::verifyDistance(GameObject* guard){
        double distance = sqrt((pow(getPositionX() - guard->getPositionX(), 2.0)) +  (pow(getPositionY() - guard->getPositionY(), 2.0)));

        if(distance < 60){
            specialAction(guard, distance);
        }
}
