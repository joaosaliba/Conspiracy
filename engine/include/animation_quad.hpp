#ifndef ANIMATION_QUAD_HPP
#define ANIMATION_QUAD_HPP

#include "sdl2includes.hpp"
namespace engine{

class AnimationQuad{
public:
    AnimationQuad(double p_x, double p_y, SDL_Rect* p_renderQuad, SDL_Rect* p_clipRect, 
    SDL_Texture* p_texture);
    ~AnimationQuad();
    SDL_Rect* get_render_quad();
    SDL_Rect* get_clip_rect();
    SDL_Texture* get_texture();
    double get_x();
    double get_y();
    double x;
    double y;
private:
    SDL_Rect* renderQuad;
    SDL_Rect* clipRect;
    SDL_Texture* texture;
};
}
#endif
