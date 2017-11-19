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

    Animation * getAnimation(); // make animation in the arrow
private:
  void update(double time_elapsed); // update arrow during time
  void draw();
  void init();
protected:
    Animation* animator = nullptr;
};

#endif
