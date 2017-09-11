/*
Objective: this class implements animations.
Author of the last update: Lucas kishima.
Date:27/08/2017
*/

#include "animation.hpp"

using namespace engine;

Animation::Animation(std::string new_directory, int rows, int columns, double all_time){
    directory = new_directory;
    matrix.first = rows;
    matrix.second = columns;
    total_time = all_time;
    current_position_frame = 0;
    init();
}

Animation::~Animation() {

}

void Animation::init() {
    INFO("Init sprite.");
    SDL_Surface * image = NULL;
    image = IMG_Load(directory.c_str());

    if(image == NULL){
        ERROR("INIT SPRITE ERROR.");
        exit(-1);
    }

    texture = SDL_CreateTextureFromSurface(WindowManager::getGameCanvas(), image);

    if(texture == NULL) {
        ERROR("CREATE TEXTURE SPRITE ERROR.");
        exit(-1);
    }

    lenght.first = image->w;
    lenght.second = image->h;

    draw_width = width_frame = lenght.first/matrix.second;
    draw_height = height_frame = lenght.second/matrix.first;

    quantity = static_cast<int>(lenght.first/matrix.second * lenght.second/matrix.first);

    SDL_FreeSurface(image);

}

void Animation::update(){
    double time_per_frame = static_cast<double> (total_time / (interval.second.second -
                                                               interval.second.first + 1));

    time_elapsed = (SDL_GetTicks() - step_time) / 1000.0f;
    DEBUG("Time Per Frame: " << time_per_frame << "Time elapsed: " << time_elapsed);

    if(time_elapsed >= time_per_frame){
        next();
        step_time = SDL_GetTicks();
    }

    int Y = (current_position_frame / (lenght.first / widthFrame));
    int X = (current_position_frame % (lenght.first  / widthFrame));

    clip_rect = {X*width_frame, Y*height_frame, width_frame, height_frame};
    DEBUG("Axis in X:" << X*width_frame << " Axis in Y:" << Y*height_frame << " Position:"
          << current_position_frame);
}
void Animation::setDrawSize(int width, int height){
    draw_width = width;
    draw_height = height;
}
void Animation::draw(int x, int y){
    INFO("ANIMATOR DRAW");
    // Rendering in screen
    render_quad = {x, y, draw_width, draw_height};
    DEBUG("X: " + std::to_string(axis.first));
    DEBUG("Y: " + std::to_string(axis.second));

    AnimationQuad* newQuad = new AnimationQuad(x,y,&render_quad,&clip_rect,texture);
    AnimationManager::instance.add_animation_quad(newQuad);
}

void Animation::drawCollider(int x, int y, int width, int height) {
    SDL_Rect* quad = new SDL_Rect();
    *quad = {x,y,width,height};
    AnimationManager::instance.add_collider(quad);
}
void Animation::drawInstant(int x, int y){
    INFO("ANIMATOR DRAW");
    // Rendering in screen
    render_quad = {x, y, clip_rect.w, clip_rect.h };
    DEBUG("X: " + std::to_string(axis.first));
    DEBUG("Y: " + std::to_string(axis.second));
    SDL_RenderCopy(WindowManager::getGameCanvas(), texture, &clip_rect, &render_quad);

}

void Animation::next(){
    current_position_frame ++;

    if(current_position_frame > interval.second.second){
       current_position_frame = interval.second.first;
    }
}

void Animation::setCurrentPositionFrame(int position_frame){
    current_position_frame = position_frame;
}
int Animation::getCurrentPositionFrame(){
    return current_position_frame;
}

void Animation::setInterval(std::string action){
    current_action = action;

    if(action != interval.first) {
        start_time = SDL_GetTicks();
        step_time = start_time;
        interval.second =  list_actions[action];
        interval.first = action;
        current_position_frame = interval.second.first;
        INFO("ACTION: " << action << current_position_frame);
    }
}
void Animation::setTotalTime(double new_total_time){
    total_time = new_total_time;
}

void Animation::shutdown(){
    INFO("Destroy sprite.");
    SDL_DestroyTexture(texture);
    texture = NULL;
}

std::pair<std::string, std::pair<int, int>> Animation::get_interval(){
    return interval;
}

void Animation::addAction(std::string name_action, int initial, int last){
  list_actions[name_action] = std::pair<int, int>(initial, last);
}

std::string Animation::getCurrentAction(){
    return current_action;
}
