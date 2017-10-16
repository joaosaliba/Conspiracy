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

void Rectangle::nullSurfaceDetector(SDL_Surface *surface){

  surface = SDL_CreateRGBSurface(0, getWidth(),getHeight(), 8, 0, 0, 0,0);
  //If the surface is null it fires an error
  if (surface == NULL) {
      ERROR("Create surface failed.");
      exit(-1);
  //The surface is not null and it aspects are calculated
  }else {
  assert(surface != NULL);
  setWidth((int)(surface->w));
  setHeight((int)(surface->h));

  texture = SDL_CreateTextureFromSurface(WindowManager::getGameCanvas(), surface);
  assert(texture != NULL);
  SDL_FreeSurface(surface);
  }
}

void Rectangle::init() {
    SDL_Surface *surface = nullptr;
    surface = SDL_CreateRGBSurface(0, getWidth(),getHeight(), 8, 0, 0, 0,0);

    nullSurfaceDetector(surface);
}

void Rectangle::update(double time_elapsed){
    time_elapsed = time_elapsed;
    //Verifies if the rectangle is enabled
    if(isEnabled()) {
        verifyAlpha();
    //Rectangle is not enabled
    }else {
        ERROR("Rectangle is not enabled");
    }
}

void Rectangle::draw() {
    //If there is a rectangle object enabled it draws the rectangle
    if(isEnabled()) {
      SDL_Rect clipRect = {0, 0, getWidth(), getHeight()};
      SDL_Rect renderQuad = {(int)getPositionX(), (int)getPositionY(), clipRect.w, clipRect.h};
      SDL_RenderCopy(WindowManager::getGameCanvas(), texture, &clipRect, &renderQuad);
    //Rectangle is not enabled
    }else {
      ERROR("Rectangle is not enabled");
    }
}

void Rectangle::verifyAlpha() {
    //If the rectangle alpha is active it sets the texture
    if(alpha_active){
        SDL_SetTextureColorMod(texture, rectangle_color->r, rectangle_color->g, rectangle_color->b);
        SDL_SetTextureAlphaMod(texture, rectangle_color->a);
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    //Alpha is not active
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
