/**
 *   @file chair.cpp
 *    @brief Manage the chair in the game.
 *    @copyright  GNU GENERAL PUBLIC LICENSE.
 */
#include "collision_manager.hpp"
#include "chair.hpp"
#include "log.h"
#include <assert.h>
#define QUARTERSECOND  0.15
//#define NDEBUG *uncomment to disable assertions
/**
 *    @brief Chair object constructor.
 *    @param[in] chair_position_x it sets the x coordinate of the object.
 *    @param[in] chair_position_y it sets the y coordinate of the object.
 *    @param[in] chair_width it sets the chair_width dimension of the object.
 *    @param[in] chair_height it sets the chair_height dimension of the object.
 *    @param[in] chair_name set the name of the object
 *
 */
Chair::Chair(std::string chair_name, double chair_position_x, double chair_position_y,
             int chair_width, int chair_height) : GameObject(chair_name,
                                                 chair_position_x,
                                                 chair_position_y,
                                                 chair_width, chair_height){
        chairEffect = new Audio("assets/sounds/DRAG.wav", "EFFECT", 128);
        animator = new Animation(chair_name, 1, 4, 0.5);
        animator->addAction("move",0,3);
        animator->addAction("idle",0,0);
        animator->setInterval("idle");
        isMoving = false;
        assert ( chair_position_x != NULL);
        assert ( chair_position_y != NULL);
        assert ( chair_width != NULL);
        assert ( chair_height != NULL);
          INFO("Constructor chair ");
}

/**
 *    @brief Chair object destructor.
 */

Chair::~Chair(){
  INFO("Destructor chair ");
}

/**
 *   @brief draws the animation of the chair according to its position
 *   @return void
 */
void Chair::draw(){
        animator->draw(getPositionX(), getPositionY()-15);
        animator->draw_collider(getPositionX(), getPositionY(), getWidth(), getHeight());
        INFO("draw chair ");
}

/**
*    @brief update the chair  decoring the time.
*    @param[in] timeElapsed its about the time
*/
void Chair::update(double timeElapsed){
        assert ( timeElapsed != NULL);
        auto move_chair_in_x = QUARTERSECOND*timeElapsed;
        auto move_chair_in_y = QUARTERSECOND*timeElapsed;

        if(isMoving) {
                moveInX(move_chair_in_x);
                moveInY(move_chair_in_y);
        }else{
          animator->setInterval("idle");
        }

        animator->update();
        setMoving(false);
          INFO("update chair ");
}



/**
 *   @brief set a  new position for the chair in the x plan
 *   @return void
 */

void Chair::moveInX(double move_chair_in_x){
        assert ( move_chair_in_x != NULL);
        if(direction == "right") {
                move_chair_in_x = move_chair_in_x;
                animator->setInterval("move");
        }
        else if(direction == "left") {
                move_chair_in_x = move_chair_in_x * (0-1);
                animator->setInterval("move");
        }
        else {
                move_chair_in_x = 0;
        }
        setPositionX(getPositionX()+move_chair_in_x);
        if(CollisionManager::instance.verifyCollisionWithOtherChairs(this) || CollisionManager::instance.verifyCollisionWithWalls(this) || CollisionManager::instance.verifyCollisionWithGuardsBody(this)) {
                setPositionX(getPositionX()+(move_chair_in_x*(0-1)));
        }
        INFO("move chair in X");
}

/**
 *   @brief set a  new position for the chair in the y plan
 *   @return void
 */
void Chair::moveInY(double move_chair_in_y){
        assert ( move_chair_in_y != NULL);

        if(direction == "down") {
                move_chair_in_y = move_chair_in_y;
                animator->setInterval("move");
        }
        else if(direction == "up") {
                move_chair_in_y = move_chair_in_y * (0-1);
                animator->setInterval("move");
        }
        else {
                move_chair_in_y = 0;
        }
        setPositionY(getPositionY()+move_chair_in_y);
        if(CollisionManager::instance.verifyCollisionWithOtherChairs(this) || CollisionManager::instance.verifyCollisionWithWalls(this) || CollisionManager::instance.verifyCollisionWithGuardsBody(this)) {
                setPositionY(getPositionY()+(move_chair_in_y*(0-1)));
        }
        INFO("move chair in Y");
}
/**
 *   @brief if player are move the chair call this function
 *   @return void
 */
void Chair::setMoving(bool chair_move){
        assert ( chair_move != NULL);
        isMoving = chair_move;
        INFO("Set chair movement");
}
/**
 *   @brief when move the chair set the correct direction that it was moved
 *   @return void
 */
void Chair::setDirection(std::string currentDirection){
        direction = currentDirection;
        INFO("Set chair direction");
}
