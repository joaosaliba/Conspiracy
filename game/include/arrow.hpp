#ifndef ARROW_HPP
#define ARROW_HPP

#include "engine.hpp"
#include "sprite.hpp"
#include "game_object.hpp"

using namespace engine;

class Arrow: public GameObject{
public:
    Arrow(std::string arrow_name, double arrow_position_x, double arrow_position_y, int arrow_width, int arrow_height);
    ~Arrow();
    void update(double timeElapsed); // update arrow during time
    void draw();
    void init();
    Animation * getAnimation(); // make animation in the arrow
protected:
    Animation* animator = nullptr;
};

#endif
