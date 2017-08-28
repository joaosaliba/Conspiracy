#include "rectangle.hpp"

Rectangle::Rectangle(std::string object_name, double position_x, double position_y,
  int width, int height, bool new_alpha_active, Color * newColor): GameObject(object_name,
                                                 position_x,
                                                 position_y,
                                                 width, height){

      color = newColor;
      alpha_active = new_alpha_active;
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
    }

    setWidth((int)(surface->w));
    setHeight((int)(surface->h));

    texture = SDL_CreateTextureFromSurface(WindowManager::getGameCanvas(), surface);
    SDL_FreeSurface(surface);
}

void Rectangle::update(double time_elapsed){
    time_elapsed = time_elapsed;

    if(isEnabled()) {
        verifyAlpha();
    }
}

void Rectangle::draw() {
    if(isEnabled()) {
      SDL_Rect clipRect = {0, 0, getWidth(), getHeight()};
      SDL_Rect renderQuad = {(int)getPositionX(), (int)getPositionY(), clipRect.w, clipRect.h};

      SDL_RenderCopy(WindowManager::getGameCanvas(), texture, &clipRect, &renderQuad);
    }
}

void Rectangle::verifyAlpha() {
    if(alpha_active){
        SDL_SetTextureColorMod(texture, color->r, color->g, color->b);
        SDL_SetTextureAlphaMod(texture, color->a);
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    }
}

void Rectangle::setAlphaActive(bool is_active) {
    alpha_active = is_active;
}

bool Rectangle::getAlphaActive() {
    return alpha_active;
}

void Rectangle::setColor(Color * newColor){
    color = newColor;
}
