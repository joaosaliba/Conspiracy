#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "engine.hpp"
#include "input_manager.hpp"
#include "game_object.hpp"
#include "text.hpp"

using namespace engine;

class Button: public GameObject{
    public:
      Button(std::string object_name, double position_x, double position_y,
                   int width, int height, std::string title, int size_title);

    ~Button();

    void update(double timeElapsed);

    void setTextColor(Color * newTextColor);

    void draw();

    Text * getText();

    protected:
      Text * text;
};

#endif
