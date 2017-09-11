#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "engine.hpp"
#include "input_manager.hpp"
#include "game_object.hpp"
#include "text.hpp"

using namespace engine;

class Button: public GameObject{
public:
    Button(std::string objectName, double positionX, double positionY, int width, int height, std::string title, int sizeTitle);
    ~Button();
    void update(double timeElapsed); // update button during time
    void setTextColor(Color * newTextColor); // set a color for the button
    void draw(); // make a draw off the button  
    Text * getText();
protected:
    Text * text;
};

#endif
