/**
 *   @file button.cpp
 *    @brief Manage the button in the game.
 *    @copyright  GNU GENERAL PUBLIC LICENSE.
 */
#include "button.hpp"
#include <assert.h>
//#define NDEBUG *uncomment to disable assertions
/**
 *    @brief Button object constructor.
 *    @param[in] button_name name Key of the targeted object.
 *    @param[in] button_position_x it sets the x coordinate of the object.
 *    @param[in] button_position_y it sets the y coordinate of the object.
 *    @param[in] button_width it sets the button_width dimension of the object.
 *    @param[in] button_height it sets the button_height dimension of the object.
 *    @param[in] title it sets the title for the  button
 *    @param[in] sizeTitle it sets the size of the title button
 *
 */

Button::Button(std::string button_name, double button_position_x, double button_position_y,
                                     int button_width, int button_height, std::string title, int sizeTitle) : GameObject(button_name,
                                                                         button_position_x,
                                                                         button_position_y,
                                                                         button_width, button_height) {

    text = new Text(title, button_name, sizeTitle, true, new Color(0,0,0,0), new Color(0,0,0,0));
    assert ( button_position_x != NULL);
    assert ( button_position_y != NULL);
    assert ( button_width != NULL);
    assert ( button_height != NULL);
       INFO("Constructor Button");
}
/**
 *    @brief Button object destructor.
 */
Button::~Button() {
       INFO("Destructor Button");
}

/**
*    @brief update the button  decoring the time.
*    @param[in] timeElapsed its about the time
*/
void Button::update(double timeElapsed) {
    assert ( timeElapsed != NULL);
    if (timeElapsed == NULL){
      ERROR("Failed to start window manager");
        exit(-1);
    }
    else{
      timeElapsed = timeElapsed;
    }
    INFO(timeElapsed);
       INFO("Update Button");
}
/**
 *   @brief draws the animation of the button according to its position
 *   @return void
 */
void Button::draw() {
    INFO("TEXT DRAW");
    text->draw(getPositionX(), getPositionY());
           INFO("draw Button");
}
/**
 *   @brief set a text Color for the button in the game
 *   @return void
 */

void Button::setTextColor(Color * newTextColor) {
    text->setTextColor(newTextColor);
           INFO("Set Text Collor Button");
}

/**
*   @brief get a text for the button in the game
*   @return text
*/

Text * Button::getText() {
  if (text == NULL){
    ERROR("Failed to start window manager");
      exit(-1);
  }
  else{
    return text;
  }
         INFO("Get Text Button");
}
