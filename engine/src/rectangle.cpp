//#define NDEBUG *uncomment to disable assertions
#include <assert.h>
#include "rectangle.hpp"

Rectangle::Rectangle(std::string object_name, double rectangle_position_x, double rectangle_position_y,
  int rectangle_width, int rectangle_height, bool new_alpha_active, Color * rectangle_new_color): GameObject(object_name,
                                                 rectangle_position_x,
                                                 rectangle_position_y,
                                                 rectangle_width, rectangle_height){

      rectangle_color = rectangle_new_color;
      alpha_active = new_alpha_active;
      assert(rectangle_color != NULL);
      init();
}

Rectangle::~Rectangle() {

}

void Rectangle::init() {
    SDL_Surface *surface;
    surface = SDL_CreateRGBSurface(0, getWidth(),getHeight(), 8, 0, 0, 0,0);

    if (surface == NULL) {
        ERROR("Create surface failed.");
        exit(-1);
    }else {
    assert(surface != NULL);
    setWidth((int)(surface->w));
    setHeight((int)(surface->h));

    texture = SDL_CreateTextureFromSurface(WindowManager::getGameCanvas(), surface);
    assert(texture != NULL);
    SDL_FreeSurface(surface);
  }
}

void Rectangle::update(double time_elapsed){
    time_elapsed = time_elapsed;
    if(isEnabled()) {
        verifyAlpha();
    }else {
        ERROR("Rectangle is not enabled");
    }
}

void Rectangle::draw() {
    if(isEnabled()) {
      SDL_Rect clipRect = {0, 0, getWidth(), getHeight()};
      SDL_Rect renderQuad = {(int)getPositionX(), (int)getPositionY(), clipRect.w, clipRect.h};
      SDL_RenderCopy(WindowManager::getGameCanvas(), texture, &clipRect, &renderQuad);
    }else {
      ERROR("Rectangle is not enabled");
    }
}

void Rectangle::verifyAlpha() {
    if(alpha_active){
        SDL_SetTextureColorMod(texture, rectangle_color->r, rectangle_color->g, rectangle_color->b);
        SDL_SetTextureAlphaMod(texture, rectangle_color->a);
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    }else {
        ERROR("Rectangle alpha is not active");
    }
}

void Rectangle::setAlphaActive(bool is_active) {
    alpha_active = is_active;
}

bool Rectangle::getAlphaActive() {
    return alpha_active;
}

void Rectangle::setColor(Color * rectangle_new_color){
    assert(rectangle_new_color != NULL);
    rectangle_color = rectangle_new_color;
}
