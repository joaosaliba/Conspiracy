#include "progress_bar.hpp"

using namespace engine;

ProgressBar::ProgressBar(double position_x, double position_y, int width, int height, double increment):
    GameObject(position_x, position_y, width, height) {
    percent = 1.0;
    progress_increment = increment;

    back_rect = new SDL_Rect();
    back_rect->x = position_x;
    back_rect->y = position_y;
    back_rect->w =  width;
    back_rect->h =  height;

    front_rect = new SDL_Rect();
    front_rect->x = position_x;
    front_rect->y = position_y;
    front_rect->w =  width;
    front_rect->h =  height;

    //backColor = {0, 255, 0, 255};
    back_color = {31, 65, 158, 1};
    front_color = {161, 181, 236, 50};
    SDL_GetRenderDrawColor(WindowManager::getGameCanvas(),
                                 &old_color.r, &old_color.g,
                                 &old_color.g, &old_color.a);
}

ProgressBar::ProgressBar(double position_x, double position_y, int width, int height, double increment, std::vector<unsigned int> new_back_color, std::vector<unsigned int> new_front_color):
    GameObject(position_x, position_y, width, height) {
    percent = 1.0;
    progress_increment = increment;

    back_rect = new SDL_Rect();
    back_rect->x = position_x;
    back_rect->y = position_y;
    back_rect->w =  width;
    back_rect->h =  height;

    front_rect = new SDL_Rect();
    front_rect->x = position_x;
    front_rect->y = position_y;
    front_rect->w =  width;
    front_rect->h =  height;

    //backColor = {0, 255, 0, 255};
    back_color = {(uint8_t)new_back_color[0], (uint8_t)new_back_color[1], (uint8_t)new_back_color[2], (uint8_t)new_back_color[3]};
    front_color = {(uint8_t)new_front_color[0], (uint8_t)new_front_color[1], (uint8_t)new_front_color[2], (uint8_t)new_front_color[3]};
    SDL_GetRenderDrawColor(WindowManager::getGameCanvas(),
                                 &old_color.r, &old_color.g,
                                 &old_color.g, &old_color.a);
}

ProgressBar::~ProgressBar() {}

void ProgressBar::update(double time_elapsed){
    time_elapsed = time_elapsed;
    if(percent > 1.0){
        percent = 1.0;
    }else if(percent < 0.0){
        percent = 0.0;
    }

    back_rect->x = getPositionX();
    back_rect->y = getPositionY();

    pw = (int)((double)getWidth() * percent);
    px = getPositionX() + (getWidth() - pw);

    front_rect->x = px;
    front_rect->y = getPositionY();
    front_rect->w = pw;
    front_rect->h = getHeight();
    percent -= progress_increment;
}

void ProgressBar::draw() {
    SDL_SetRenderDrawColor(WindowManager::getGameCanvas(), back_color.r,
                                                           back_color.g,
                                                           back_color.b,
                                                           back_color.a);

    SDL_RenderFillRect(WindowManager::getGameCanvas(), back_rect);

    SDL_SetRenderDrawColor(WindowManager::getGameCanvas(),
                               front_color.r, front_color.g,
                               front_color.b, front_color.a);

    SDL_RenderFillRect(WindowManager::getGameCanvas(), front_rect);

    SDL_SetRenderDrawColor(WindowManager::getGameCanvas(), old_color.r,
                                                           old_color.g,
                                                           old_color.b,
                                                           old_color.a);
}

double ProgressBar::getPercent(){
    return percent;
}

void ProgressBar::resetPercent(){
    percent = 1.0;
}
