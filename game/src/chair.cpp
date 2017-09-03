#include "collision_manager.hpp"
#include "chair.hpp"
#include "log.h"

Chair::Chair(std::string objectName, double position_x, double position_y,
             int width, int height) : GameObject(objectName,
                                                 position_x,
                                                 position_y,
                                                 width, height){
        chairEffect = new Audio("assets/sounds/DRAG.wav", "EFFECT", 128);
        animator = new Animation(objectName, 1, 4, 0.5);
        animator->addAction("move",0,3);
        animator->addAction("idle",0,0);
        animator->setInterval("idle");
        isMoving = false;
}

Chair::~Chair(){

}

void Chair::update(double time_elapsed){
        auto inc_x = 0.15*time_elapsed;
        auto inc_y = 0.15*time_elapsed;

        if(isMoving) {
                moveInX(inc_x);
                moveInY(inc_y);
        }else{
          animator->setInterval("idle");
        }

        animator->update();
        setMoving(false);
}

void Chair::draw(){
        animator->draw(getPositionX(), getPositionY()-15);
        animator->draw_collider(getPositionX(), getPositionY(), getWidth(), getHeight());
}

void Chair::moveInX(double incX){

        if(direction == "right") {
                incX = inc_x;
                animator->setInterval("move");
        }
        else if(direction == "left") {
                inc_x = inc_x * (0-1);
                animator->setInterval("move");
        }
        else {
                incX = 0;
        }
        setPositionX(getPositionX()+inc_x);
        if(CollisionManager::instance.verifyCollisionWithOtherChairs(this) || CollisionManager::instance.verifyCollisionWithWalls(this) || CollisionManager::instance.verifyCollisionWithGuardsBody(this)) {
                setPositionX(getPositionX()+(inc_x*(0-1)));
        }

}

void Chair::moveInY(double inc_y){

        if(direction == "down") {
                incY = inc_y;
                animator->setInterval("move");
        }
        else if(direction == "up") {
                inc_y = inc_y * (0-1);
                animator->setInterval("move");
        }
        else {
                inc_y = 0;
        }
        setPositionY(getPositionY()+inc_y);
        if(CollisionManager::instance.verifyCollisionWithOtherChairs(this) || CollisionManager::instance.verifyCollisionWithWalls(this) || CollisionManager::instance.verifyCollisionWithGuardsBody(this)) {
                setPositionY(getPositionY()+(inc_y*(0-1)));
        }

}

void Chair::setMoving(bool move){
        isMoving = move;
}

void Chair::setDirection(std::string currentDirection){
        direction = currentDirection;
}
