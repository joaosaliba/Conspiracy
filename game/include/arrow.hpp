#ifndef ARROW_HPP
#define ARROW_HPP

#include "engine.hpp"
#include "sprite.hpp"
#include "game_object.hpp"

using namespace engine;

class Arrow: public GameObject{
    public:
      Arrow(std::string object_name, double position_x, double position_y,
                 int width, int height);

    ~Arrow();

    void update(double timeElapsed);

    void draw();

    void init();

    Animation * getAnimation();

    protected:
      Animation* animator;
};

#endif
