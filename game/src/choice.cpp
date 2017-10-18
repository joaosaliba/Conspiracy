/**
 *   @file choice.cpp
 *    @brief Manage the chair in the game.
 *    @copyright  GNU GENERAL PUBLIC LICENSE.
 */
#include "choice.hpp"
#include <assert.h>
//#define NDEBUG *uncomment to disable assertions
/**
 *    @brief Choice object constructor.
 *    @param[in] positionX it sets the x coordinate of the object.
 *    @param[in] positionY it sets the y coordinate of the object.
 *    @param[in] width it sets the width dimension of the object.
 *    @param[in] height it sets the height dimension of the object.
 *    @param[in] objectName set the name of the object
 *
 */

Choice::Choice(std::string objectName, double positionX, double positionY,
                                     int width, int height, std::string title, int sizeTitle) : GameObject(objectName,
                                                                         positionX,
                                                                         positionY,
                                                                         width, height){
    assert (positionX !=NULL);
    assert (positionY !=NULL);
    assert (width !=NULL);
    assert (height !=NULL);
    button = new Button("assets/fonts/font.ttf", positionX + (width/2)*0.4, positionY + height, 200, 150, title, sizeTitle);
    sprite = new Sprite(objectName);
    sprite->setDrawSize(200,150);
    padlock = new Sprite("assets/sprites/padlock.png");
    chosen = false;
    unlock = false;
    Color *color = new Color(0, 0, 0, 150);
    rectangle = new Rectangle("Rectangle", positionX, positionY, width, height, true, color);
}

/**
 *    @brief Choice object destructor.
 */
Choice::~Choice() {

}
/**
*    @brief update the choice  during the time.
*    @param[in] timeElapsed its about the time
*/
void Choice::update(double timeElapsed){
    assert ( timeElapsed != NULL);
    if(chosen && unlock){
        rectangle->setEnabled(false);
    }else{
        rectangle->setEnabled(true);
    }
    rectangle->update(timeElapsed);

}
/**
 *   @brief draws the animation of the chair according to its position
 *   @return void
 */
void Choice::draw(){
    INFO("TEXT DRAW");
    sprite->draw(getPositionX(), getPositionY());
    if(!unlock){
        padlock->draw(getPositionX()+ (getWidth()/2)*0.8, getPositionY()+ (getHeight()/2)*0.8);
    }
    button->draw();
    rectangle->draw();
}

/**
 *   @brief Set a color for the text button
 */
void Choice::setTextColor(Color * newTextColor){
    button->setTextColor(newTextColor);
}
/**
 *   @brief Set a back ground color for the button
 */
void Choice::setBackgroundColor(Color * newBackgroundColor){
    button->setTextColor(newBackgroundColor);
}
/**
 *   @brief Set a text for the choice button
 *   @return button->getText();
 */
Text * Choice::getText(){
  if ( button->getText() == NULL){
    ERROR("Failed to start window manager");
      exit(-1);
  }
  else{
    return button->getText();
  }
}
/**
 *   @brief Set a chosen for the choice
 */
void Choice::setChosen(bool isChosen){
  assert( isChosen != NULL);
  chosen = isChosen;
}
/**
 *   @brief Set if the choice are unlock
 */
void Choice::setUnlock(bool isUnlock){
    assert( isUnlock != NULL);
    unlock = isUnlock;
}
/**
 *   @brief get the actual situation for the choice
 *   @return unlock
 */
bool Choice::getUnlock(){
  if ( unlock == NULL){
    ERROR("Failed to start window manager");
      exit(-1);
  }
  else{
    return unlock;
  }

}
