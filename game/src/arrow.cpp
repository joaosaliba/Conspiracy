/**
 *   @file arrow.cpp
 *    @brief Manage the arrow in the game.
 *    @copyright  GNU GENERAL PUBLIC LICENSE.
 */

#include "arrow.hpp"
#include "log.h"
#include <assert.h>
//#define NDEBUG *uncomment to disable assertions

/**
 *    @brief Arrow object constructor.
 *    @param[in] arrow_name name Key of the targeted object.
 *    @param[in] arrow_position_x it sets the x coordinate of the object.
 *    @param[in] arrow_position_y it sets the y coordinate of the object.
 *    @param[in] arrow_width it sets the arrow_width dimension of the object.
 *    @param[in] arrow_height it sets the arrow_height dimension of the object.
 */

Arrow::Arrow(std::string arrow_name, double arrow_position_x, double arrow_position_y,
             int arrow_width, int arrow_height) : GameObject(arrow_name,
                                                 arrow_position_x,
                                                 arrow_position_y,
                                                 arrow_width, arrow_height){
        animator = new Animation(arrow_name, 1, 17, 2.0);
        animator->addAction("select",0,16);
        animator->setInterval("select");
        assert ( arrow_position_x != NULL);
        assert ( arrow_position_y != NULL);
        assert ( arrow_width != NULL);
        assert ( arrow_height != NULL);
}

/**
*    @brief Arrow object destryctor.
*/
Arrow::~Arrow(){

}
/**
*    @brief update the arrow  decoring the time.
*    @param[in] timeElapsed its about the time
*/
void Arrow::update(double timeElapsed){
        assert ( timeElapsed != NULL);
        if (timeElapsed == NULL){
          ERROR("Failed to start window manager");
            exit(-1);
        }
        else{
          timeElapsed = timeElapsed;
        }
        if(isEnabled()){
                animator->update();
        }else{
          //nothing to do
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
        else{
          //nothing to do
        }
}
