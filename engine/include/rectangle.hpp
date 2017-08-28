#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "engine.hpp"
#include "game_object.hpp"
#include "sdl2includes.hpp"
#include "log.h"
#include "color.hpp"

using namespace engine;

class Rectangle: public GameObject{
public:
    Rectangle(std::string object_name, double position_x, double position_y, int width, int height, bool new_alpha_active, Color * newColor);
    ~Rectangle();
    void update(double time_elapsed);
    void draw();
    void init();
    void setAlphaActive(bool is_active);
    bool getAlphaActive();
    void setColor(Color * newColor);
private:
    bool alpha_active;
    SDL_Texture* texture;
    Color* color;

    void verifyAlpha();
};

#endif
