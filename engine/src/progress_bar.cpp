/**
 * @file progress_bar.cpp
 * @brief class to object of progress_bar, where you can find some values, files,
 * others objects used in this class and methods to the same.
 * @copyright  GNU GENERAL PUBLIC LICENSE.
 */

 //#define NDEBUG *uncomment to disable assertions

#include "progress_bar.hpp"
#include <assert.h>

#define MAX_STRANGE_POSITION 1000
#define MIN_STRANGE_POSITION 0

using namespace engine;

ProgressBar::ProgressBar(double position_x, double position_y, int width,
                                                             int height,
                                                             double increment):
                                                                      GameObject(
                                                                          position_x,
                                                                          position_y,
                                                                          width,
                                                                          height){

    INFO("progress_bar constructor init");

    if(position_x > MAX_STRANGE_POSITION || position_x < MIN_STRANGE_POSITION) {
        ERROR("Strange progress_bar position");
        exit(-1);
    }else {
        //nothing to do
        INFO("progress_bar position_x is ok");
    }

    if(position_y > MAX_STRANGE_POSITION || position_y < MIN_STRANGE_POSITION) {
        ERROR("Strange progress_bar position");
        exit(-1);
    }else {
        //nothing to do
        INFO("progress_bar position y is ok");
    }

    if(width > 100 || width < MIN_STRANGE_POSITION) {
        ERROR("Strange progress_bar width");
        exit(-1);
    }else {
        //nothing to do
        INFO("progress_bar width is ok");
    }

    if(height > 100 || height < MIN_STRANGE_POSITION) {
        ERROR("Strange progress_bar height");
        exit(-1);
    }else {
        //nothing to do
        INFO("progress_bar height is ok");
    }

    percent = 1.0;

    DEBUG("percent receive: "+percent);

    progress_increment = increment;

    backRect = new SDL_Rect();
    backRect->x = position_x;
    backRect->y = position_y;
    backRect->w =  width;
    backRect->h =  height;

    frontRect = new SDL_Rect();
    frontRect->x = position_x;
    frontRect->y = position_y;
    frontRect->w =  width;
    frontRect->h =  height;

    //backColor = {0, 255, 0, 255};
    back_color = {31, 65, 158, 1};
    front_color = {161, 181, 236, 50};
    SDL_GetRenderDrawColor(WindowManager::getGameCanvas(),
                                 &old_color.r, &old_color.g,
                                 &old_color.g, &old_color.a);

    INFO("progress_bar constructor finished");
}

ProgressBar::ProgressBar(double position_x, double position_y, int width,
                                                             int height,
                                                             double increment,
                                                             std::vector<unsigned int> newBackColor,
                                                             std::vector<unsigned int> newFrontColor):
                                                                      GameObject(
                                                                          position_x,
                                                                          position_y,
                                                                          width,
                                                                          height){


    assert (position_x != NULL);
    assert (position_y != NULL);
    assert (width < 100);
    assert (height > 100);

    if(position_x > MAX_STRANGE_POSITION || position_x < MIN_STRANGE_POSITION) {
        ERROR("Strange progress_bar position");
        exit(-1);
    }else {
        //nothing to do
        INFO("progress_bar position_x is ok");
    }
    if(position_y > MAX_STRANGE_POSITION || position_y < MIN_STRANGE_POSITION) {
        ERROR("Strange progress_bar position");
        exit(-1);
    }else {
        //nothing to do
        INFO("progress_bar position_y is ok");
    }
    if(width > 100 || width < MIN_STRANGE_POSITION) {
        ERROR("Strange progress_bar width");
        exit(-1);
    }else {
        //nothing to do
        INFO("progress_bar width is ok");
    }
    if(height > 100 || height < MIN_STRANGE_POSITION) {
        ERROR("Strange progress_bar height");
        exit(-1);
    }else {
        //nothing to do
        INFO("progress_bar height is ok");
    }

    percent = 1.0;
    progress_increment = increment;

    backRect = new SDL_Rect();
    backRect->x = position_x;
    backRect->y = position_y;
    backRect->w =  width;
    backRect->h =  height;

    frontRect = new SDL_Rect();
    frontRect->x = position_x;
    frontRect->y = position_y;
    frontRect->w =  width;
    frontRect->h =  height;

    //backColor = {0, 255, 0, 255};
    back_color = {(uint8_t)new_back_color[0], (uint8_t)new_back_color[1], (uint8_t)new_back_color[2], (uint8_t)new_back_color[3]};
    front_color = {(uint8_t)new_front_color[0], (uint8_t)new_front_color[1], (uint8_t)new_front_color[2], (uint8_t)new_front_color[3]};
    SDL_GetRenderDrawColor(WindowManager::getGameCanvas(),
                                 &old_color.r, &old_color.g,
                                 &old_color.g, &old_color.a);
}

/**
  *    @brief ProgressBar object destructor.
 */

ProgressBar::~ProgressBar(){}


void ProgressBar::update(double time_elapsed) {

    DEBUG("time_elapsed receive: "+time_elapsed);

    if(time_elapsed == NULL) {
      ERROR("type_elapsed can not be null");
      exit(-1);
    }else {
      //nothing to do
      INFO("exist the time_elapsed data");
    }

    time_elapsed = time_elapsed;

    if(percent > 1.0){
        percent = 1.0;
    }else if(percent < 0.0){
        percent = 0.0;
    }

    back_rect->x = getPositionX();

    if(getPositionX() == NULL){
      ERROR("the value of position x cant be null");
      exit(-1);
    }

    back_rect->y = getPositionY();

    if(getPositionY() == NULL){
      ERROR("the value of position y cant be null");
      exit(-1);
    }

    pw = (int)((double)getWidth() * percent);

    if(getWidth() == NULL){
      ERROR("the value of position x cant be null");
      exit(-1);
    }

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

double ProgressBar::getPercent() {
    return percent;
}

void ProgressBar::resetPercent() {
    percent = 1.0;
}
