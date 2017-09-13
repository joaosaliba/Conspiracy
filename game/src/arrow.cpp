/**
 *   @file arrow.cpp
 *    @brief Manage the arrow in the game.
 *    @copyright  GNU GENERAL PUBLIC LICENSE.
 */

#include "arrow.hpp"
#include "log.h"

/**
 *    @brief Arrow object constructor.
 *    @param[in] objectName name Key of the targeted object.
 *    @param[in] positionX it sets the x coordinate of the object.
 *    @param[in] positionY it sets the y coordinate of the object.
 *    @param[in] width it sets the width dimension of the object.
 *    @param[in] height it sets the height dimension of the object.
 */

Arrow::Arrow(std::string objectName, double positionX, double positionY,
             int width, int height) : GameObject(objectName,
                                                 positionX,
                                                 positionY,
                                                 width, height){
        animator = new Animation(objectName, 1, 17, 2.0);
        animator->addAction("select",0,16);
        animator->setInterval("select");
}

/**
*    @brief Arrow object constructor.
*/
Arrow::~Arrow(){

}
/**
*    @brief update the arrow  decoring the time.
*    @param[in] timeElapsed its about the time
*/
void Arrow::update(double timeElapsed){
        timeElapsed = timeElapsed;
        if(isEnabled()){
                animator->update();
        }
}

/** 
 *   @brief draws the animation of the arrow according to its position
 *   @return void
 */

void Arrow::draw(){
        if(isEnabled()) {
                animator->draw(getPositionX(), getPositionY());
        }
}
