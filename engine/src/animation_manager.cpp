/*
Objective: this class implements animations.
Author of the last update: Lucas kishima.
Date:27/08/2017
*/
#include "animation_manager.hpp"

using namespace engine;

AnimationManager AnimationManager::instance;
void AnimationManager::add_animation_quad(Animation_quad* new_quad){
    animationQuads.push_back(new_quad);
}

void AnimationManager::add_collider(SDL_Rect* new_quad){
    colliderRects.push_back(new_quad);
}
void AnimationManager::addFieldOfVision(FieldOfVision* field){
    fields.push_back(field);
}

void AnimationManager::addGuardVision(FieldOfVision* field){
    guardsVision.push_back(field);
}
void AnimationManager::addProgressBar(ProgressBar* new_progress_bar){
    progressBars.push_back(new ProgressBar);
}

void AnimationManager::clearAnimationQuads(){
    for(auto AnimationQuad: animation_quads){
        free(AnimationQuad);
    }

    for(auto collider: colliderRects){
        free(collider);
    }

    animationQuads.clear();
    fields.clear();
    guardsVision.clear();
    progressBars.clear();
    colliderRects.clear();

}

void AnimationManager::draw_quads() {
    if(InputManager::instance.isKeyTriggered(InputManager::KEY_PRESS_L)) {
        if(is_active) {
            is_active = false;
        }else {
            is_active = true;
        }
    }

    std::sort(animation_quads.begin(),
              animation_quads.end(),[](const AnimationQuad* lhs,
                                       const AnimationQuad* rhs){ return lhs->y < rhs->y; });

    for(AnimationQuad * quad : animation_quads) {
        SDL_RenderCopy(WindowManager::getGameCanvas(), quad->getTexture(),
                       quad->getClipRect(), quad->getRenderQuad());
    }

    if(isActive) {
        draw_colliders();
    }

    drawProgressBars();

    drawLinesOfVision();

    clearAnimationQuads();

    SDL_SetRenderDrawColor(WindowManager::getGameCanvas(), color->r, color->g, color->b, color->a);
}
void AnimationManager::drawLinesOfVision(){

    SDL_SetRenderDrawColor(WindowManager::getGameCanvas(), 230, 0, 0, 1);

    if(!isActive) {
        for(auto field: fields){
            drawTriangleVision(field->getLines());
        }
    }else {
        for(auto field: fields){
            for(auto line: field->getLines()){
                drawLine(line);
            }
        }
        for(auto field: guardsVision){
            for(auto line: field->getLines()){
                drawLine(line);
            }
        }
    }

    int colorLine = 100;
    SDL_SetRenderDrawColor(WindowManager::getGameCanvas(), colorLine, colorLine, colorLine, 1);

}

void AnimationManager::drawTriangleVision(std::vector<Line*> lines){
    Line* bottom_line = NULL;
    Line* upper_line = NULL;
    Line* front_line = NULL;

    int i = 0;

    for(auto line:lines) {
        if(i++ == 0){
            bottom_line = line;
            upper_line = line;
        }
        if(line->getAngle() > upper_line->getAngle()) {
            upper_line = line;
        }
        if(line->getAngle() < bottom_line->getAngle()) {
            bottom_line = line;
        }
    }
    front_line = new Line(bottomLine->getPoint2().first,bottomLine->getPoint2().second,
                         upperLine->getPoint2().first,upperLine->getPoint2().second);

    drawLine(bottom_line);
    drawLine(upper_line);
    drawLine(front_line);
}
void AnimationManager::drawLine(Line* line) {
    SDL_RenderDrawLine(WindowManager::getGameCanvas(), line->getPoint1().first,
                       line->getPoint1().second, line->getPoint2().first,
                       line->getPoint2().second);
}

void AnimationManager::draw_colliders() {
    for(SDL_Rect * quad : colliderRects) {
        SDL_RenderDrawRect(WindowManager::getGameCanvas(), quad);
    }
}

void AnimationManager::drawProgressBars() {
    for(ProgressBar * progress_bar : progress_bars) {
        progress_bar->draw();
    }
}

void AnimationManager::setBackgroundColor(Color* background_color){
    color = background_color;
}
