#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "engine.hpp"
#include "input_manager.hpp"
#include "game_object.hpp"
#include "text.hpp"

using namespace engine;

class Button: public GameObject{
public:
    Button(std::string button_name, double button_position_x, double button_position_y, int button_width, int button_height, std::string title, int sizeTitle);
    ~Button();

    void setTextColor(Color * newTextColor); // set a color for the button
    void draw(); // make a draw off the button
    Text * getText();

private:
    void update(double time_elapsed); // update button during time

protected:
    Text * text = nullptr;
};

#endif
