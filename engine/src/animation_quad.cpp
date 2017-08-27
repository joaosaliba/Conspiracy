#include "animation_quad.hpp"

using namespace engine;

AnimationQuad::AnimationQuad(double pX, double pY, SDL_Rect* p_render_quad, SDL_Rect* p_clip_rect, SDL_Texture* Ptexture){
    x = pX;
    y = pY;
    renderQuad = p_render_quad;
    clip_rect = p_clip_rect;
    texture = Ptexture;
}

AnimationQuad::~AnimationQuad(){

}

SDL_Rect* AnimationQuad::getRenderQuad(){
    return render_quad;
}
SDL_Rect* AnimationQuad::getClipRect(){
    return clip_rect;
}
SDL_Texture* AnimationQuad::getTexture(){
    return texture;
}
double AnimationQuad::getX(){
    return x;
}
double AnimationQuad::getY(){
    return y;
}
