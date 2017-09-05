#include "alien_bilu.hpp"
#include "collision_manager.hpp"
#include "paper.hpp"
#include "door_switch.hpp"

#define FILENAME "assets/sprites/bilu_sheet.png"
#define WIDTH 19
#define HEIGHT 22

Bilu::Bilu(double position_x, double position_y) : Alien(FILENAME, position_x, position_y, WIDTH, HEIGHT){
        animator->addAction("special_right",14,17);
        animator->addAction("special_left",10,13);

        hacking = false;
        editing = false;
        lastAction = false;
        isSelected = false;
        inPosition = false;
}

void Bilu::update(double timeElapsed){
        inPosition = false;
        animator->setTotalTime(0.3);
        auto inc_y = 0.15*time_elapsed;
        auto inc_x = 0.15*time_elapsed;

        if(!blockMovement && isSelected) {
                walkInX(inc_x);
                walkInY(inc_y, inc_x);
        }

        if(inc_x == 0 && inc_y == 0) {
                if(idleAnimationNumber) {
                        animator->setInterval("idle_right");
                }else{
                        animator->setInterval("idle_left");
                }
        }
        specialAction();

        if(CollisionManager::instance.verifyCollisionWithGuards(this) || CollisionManager::instance.verifyCollisionWithCameras(this)) {
                setEnabled(false);
        }
        FinishPoint* finishPoint = (FinishPoint*)CollisionManager::instance.verifyCollisionWithFinishPoints(this);
        if(finishPoint != NULL){
            if(finishPoint->getAlienNames().find("B") != std::string::npos){
                inPosition = true;
            }
        }

        animator->update();
}

void Bilu::specialAction(){
        std::pair<int, int> interval;

        GameObject* paper = CollisionManager::instance.verifyCollisionWithPapers(this);
        GameObject* doorSwitch = CollisionManager::instance.verifyCollisionWithSwitches(this);

        if(InputManager::instance.isKeyPressed(InputManager::KEY_PRESS_SPACE) && isSelected) {
                // Paper interaction
                if(paper != NULL) {
                        if(! editing) {
                                editing = true;
                                blockMovement = true;
                                ((Paper*)(paper))->playEffect();
                        }
                }

                // PC interaction
                if(doorSwitch != NULL) {
                        if(!hacking) {
                                hacking = true;
                                blockMovement = true;
                                ((DoorSwitch*)(doorSwitch))->playEffect();
                        }
                }

        }else if(InputManager::instance.isKeyPressed(InputManager::KEY_PRESS_ESC) && isSelected) {
                if(hacking) {
                        hacking = false;
                        blockMovement = false;
                        ((DoorSwitch*)(doorSwitch))->stopEffect();
                        ((DoorSwitch*)(doorSwitch))->stopAnimation();
                        ((DoorSwitch*)(doorSwitch))->resetHackingProgress();
                }else if(editing) {
                        editing = false;
                        blockMovement = false;
                        ((Paper*)(paper))->stopEffect();
                        ((Paper*)(paper))->stopAnimation();
                        ((Paper*)(paper))->resetEditingProgress();
                }
        }

        if(hacking) {
                ((DoorSwitch*)(doorSwitch))->animate();
                setSpecialActionAnimator();
                if(((DoorSwitch*)(doorSwitch))->getHackingBarPercent() <= 0.0) {
                        hacking = false;
                        ((DoorSwitch*)(doorSwitch))->stopAnimation();
                        ((DoorSwitch*)(doorSwitch))->stopEffect();
                        ((DoorSwitch*)(doorSwitch))->resetHackingProgress();
                        Alien::animator->setInterval("idle");
                        blockMovement = false;
                }
        }else if(editing) {
                ((Paper*)(paper))->animate();
                setSpecialActionAnimator();
                if(((Paper*)(paper))->getEditingBarPercent() <= 0.0) {
                        editing = false;
                        ((Paper*)(paper))->stopAnimation();
                        //((Paper*)(paper))->stopEffect();
                        ((Paper*)(paper))->resetEditingProgress();
                        Alien::animator->setInterval("idle");
                        blockMovement = false;
                }
        }
        lastAction = hacking;
}

void Bilu::draw(){
        INFO("Bilu DRAW");
        animator->draw(getPositionX()-11, getPositionY()-20);
        animator->draw_collider(getPositionX(), getPositionY(), getWidth(), getHeight());
}

void Bilu::setSpecialActionAnimator(){// seta o tempo para uma iteração. 
        if(idleAnimationNumber == 5) {
                animator->setInterval("special_right");
        }else{
                animator->setInterval("special_left");
        }
        animator->setTotalTime(0.6);
}
