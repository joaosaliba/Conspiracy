/**
 *   @file chair.cpp
 *    @brief Manage the chair in the game.
 *    @copyright  GNU GENERAL PUBLIC LICENSE.
 */
#include "collision_manager.hpp"
#include "chair.hpp"
#include "log.h"
/**
 *    @brief Chair object constructor.
 *    @param[in] positionX it sets the x coordinate of the object.
 *    @param[in] positionY it sets the y coordinate of the object.
 *    @param[in] width it sets the width dimension of the object.
 *    @param[in] height it sets the height dimension of the object.
 *    @param[in] objectName set the name of the object
 *    
 */
Chair::Chair(std::string objectName, double positionX, double positionY,
             int width, int height) : GameObject(objectName,
                                                 positionX,
                                                 positionY,
                                                 width, height){
        chairEffect = new Audio("assets/sounds/DRAG.wav", "EFFECT", 128);
        animator = new Animation(objectName, 1, 4, 0.5);
        animator->addAction("move",0,3);
        animator->addAction("idle",0,0);
        animator->setInterval("idle");
        isMoving = false;
}

/**
 *    @brief Chair object destructor.
 */

Chair::~Chair(){

}
/**
*    @brief update the chair  decoring the time.
*    @param[in] timeElapsed its about the time
*/

void Chair::update(double timeElapsed){
        auto incX = 0.15*timeElapsed;
        auto incY = 0.15*timeElapsed;

        if(isMoving) {
                moveInX(incX);
                moveInY(incY);
        }else{
          animator->setInterval("idle");
        }

        animator->update();
        setMoving(false);
}

/** 
 *   @brief draws the animation of the chair according to its position
 *   @return void
 */
void Chair::draw(){
        animator->draw(getPositionX(), getPositionY()-15);
        animator->draw_collider(getPositionX(), getPositionY(), getWidth(), getHeight());
}

/** 
 *   @brief set a  new position for the chair in the x plan
 *   @return void
 */

void Chair::moveInX(double incX){

        if(direction == "right") {
                incX = incX;
                animator->setInterval("move");
        }
        else if(direction == "left") {
                incX = incX * (0-1);
                animator->setInterval("move");
        }
        else {
                incX = 0;
        }
        setPositionX(getPositionX()+incX);
        if(CollisionManager::instance.verifyCollisionWithOtherChairs(this) || CollisionManager::instance.verifyCollisionWithWalls(this) || CollisionManager::instance.verifyCollisionWithGuardsBody(this)) {
                setPositionX(getPositionX()+(incX*(0-1)));
        }

}

/** 
 *   @brief set a  new position for the chair in the y plan
 *   @return void
 */
void Chair::moveInY(double incY){

        if(direction == "down") {
                incY = incY;
                animator->setInterval("move");
        }
        else if(direction == "up") {
                incY = incY * (0-1);
                animator->setInterval("move");
        }
        else {
                incY = 0;
        }
        setPositionY(getPositionY()+incY);
        if(CollisionManager::instance.verifyCollisionWithOtherChairs(this) || CollisionManager::instance.verifyCollisionWithWalls(this) || CollisionManager::instance.verifyCollisionWithGuardsBody(this)) {
                setPositionY(getPositionY()+(incY*(0-1)));
        }

}
/** 
 *   @brief if player are move the chair call this function
 *   @return void
 */
void Chair::setMoving(bool move){
        isMoving = move;
}
/** 
 *   @brief when move the chair set the correct direction that it was moved
 *   @return void
 */
void Chair::setDirection(std::string currentDirection){
        direction = currentDirection;
}
