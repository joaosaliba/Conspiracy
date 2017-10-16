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
    Rectangle(std::string object_name, double rectangle_position_x, double rectangle_position_y, int rectangle_width, int rectangle_height, bool new_alpha_active, Color * rectangle_new_color);
    ~Rectangle();
    void update(double time_elapsed);
    void draw();
    void init();
    void setAlphaActive(bool is_active);
    bool getAlphaActive();
    void setColor(Color * rectangle_new_color);
    void nullSurfaceDetector(SDL_Surface *surface);
private:
    bool alpha_active;
    SDL_Texture* texture;
    Color* rectangle_color;

    void verifyAlpha();
};

#endif
