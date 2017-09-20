/**
 *   @file button.cpp
 *    @brief Manage the button in the game.
 *    @copyright  GNU GENERAL PUBLIC LICENSE.
 */
#include "button.hpp"
#include <assert.h>
/**
 *    @brief Button object constructor.
 *    @param[in] objectName name Key of the targeted object.
 *    @param[in] positionX it sets the x coordinate of the object.
 *    @param[in] positionY it sets the y coordinate of the object.
 *    @param[in] width it sets the width dimension of the object.
 *    @param[in] height it sets the height dimension of the object.
 *    @param[in] title it sets the title for the  button
 *    @param[in] sizeTitle it sets the size of the title button
 *
 */

Button::Button(std::string objectName, double positionX, double positionY,
                                     int width, int height, std::string title, int sizeTitle) : GameObject(objectName,
                                                                         positionX,
                                                                         positionY,
                                                                         width, height) {

    text = new Text(title, objectName, sizeTitle, true, new Color(0,0,0,0), new Color(0,0,0,0));
    assert ( positionX != NULL);
    assert ( positionY != NULL);
    assert ( width != NULL);
    assert ( height != NULL);
}
/**
 *    @brief Button object destructor.
 */
Button::~Button() {

}

/**
*    @brief update the button  decoring the time.
*    @param[in] timeElapsed its about the time
*/
void Button::update(double timeElapsed) {
    assert ( timeElapsed != NULL);
    timeElapsed = timeElapsed;
    INFO(timeElapsed);

}
/**
 *   @brief draws the animation of the button according to its position
 *   @return void
 */
void Button::draw() {
    INFO("TEXT DRAW");
    text->draw(getPositionX(), getPositionY());
}
/**
 *   @brief set a text Color for the button in the game
 *   @return void
 */

void Button::setTextColor(Color * newTextColor) {
    text->setTextColor(newTextColor);
}

/**
*   @brief get a text for the button in the game
*   @return text
*/

Text * Button::getText() {
    return text;
}
