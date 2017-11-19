#ifndef CHOICE_HPP
#define CHOICE_HPP

#include "engine.hpp"
#include "input_manager.hpp"
#include "game_object.hpp"
#include "button.hpp"
#include "sprite.hpp"
#include "color.hpp"
#include "rectangle.hpp"

using namespace engine;

class Choice: public GameObject{
public:
    Choice(std::string objectName, double position_x, double position_y, int width, int height, std::string title, int sizeTitle);
    ~Choice();
    void update(double time_elapsed);
    void setTextColor(Color * newTextColor);
    void setBackgroundColor(Color * newBackgroundColor);
    void setChosen(bool isChosen);
    void draw();
    void init();
    Text * getText();
    bool getUnlock();
    void setUnlock(bool isUnlock);
private:
    Sprite * sprite;
    Sprite * padlock;
    Button * button;
    Rectangle * rectangle;
    bool unlock;
    bool chosen;
};

#endif
