/**
    @file rectangle.cpp
    @brief Manage the surface of the stages.
    @copyright MIT License.
*/

//#define NDEBUG *uncomment to disable assertions
#include <assert.h>
#include "rectangle.hpp"

/**
    @brief Paper class constructor.
    @param[in] object_name stirng that contains the name of the object.
    @param[in] rectangle_position double parameter with the coordinates of the object.
    @param[in] rectangle_width rectangle width dimension
    @param[in] rectangle_height rectangle height dimension
    @param[in] new_alpha_active bool alpha active
*/

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

/**
    @brief Rectangle class destructor.
*/

Rectangle::~Rectangle() {

}

/**
    @brief It detects if the surface is null.
    @param[in] surface surface object.
*/

void Rectangle::nullSurfaceDetector(SDL_Surface *surface){
  INFO("Detecting if surfac is null");
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

/**
    @brief Starts instance of the class.
*/

void Rectangle::init() {
    INFO("Initializing rectangle object");
    SDL_Surface *surface = nullptr;
    surface = SDL_CreateRGBSurface(0, getWidth(),getHeight(), 8, 0, 0, 0,0);

    nullSurfaceDetector(surface);
}

/**
    @brief Verifies object state.
*/

void Rectangle::update(double time_elapsed){
    INFO("Updating object state");
    time_elapsed = time_elapsed;
    //Verifies if the rectangle is enabled
    if(isEnabled()) {
        verifyAlpha();
    //Rectangle is not enabled
    }else {
        ERROR("Rectangle is not enabled");
    }
}

/**
    @brief Renderizes the surface.
*/

void Rectangle::draw() {
    INFO("Drawing rectangle");
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

/**
    @brief Verifies if the alpha is active.
*/

void Rectangle::verifyAlpha() {
    INFO("Verifying if alpha is active");
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

/**
    @brief Set alpha as active.
*/

void Rectangle::setAlphaActive(bool is_active) {
    INFO("Setting alpha as active");
    alpha_active = is_active;
}

/**
    @brief Gets alpha state.
*/

bool Rectangle::getAlphaActive() {
    INFO("Getting alpha active");
    return alpha_active;
}

/**
    @brief Sets rectangle color.
*/

void Rectangle::setColor(Color * rectangle_new_color){
    INFO("Setting rectangle color");
    assert(rectangle_new_color != NULL);
    rectangle_color = rectangle_new_color;
}
