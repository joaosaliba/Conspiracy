#include "paper.hpp"
#include <assert.h>
Paper::Paper(std::string objectName, double positionX, double positionY,
                                     int width, int height) : GameObject(objectName,
                                                                         positionX,
                                                                         positionY,
                                                                         width, height){

    animator = new Animation(objectName, 1, 4, 0.5);
    assert(animator->matrix.first.rows==1);

    std::vector<unsigned int> backColor = {22, 206, 26, 1};
    std::vector<unsigned int> frontColor = {116, 225, 117, 1};
    editing_bar = new ProgressBar(positionX-3, positionY-8, 22.5, 5, 0.005, backColor, frontColor);
    assert(editing_bar-> back_rect->position_x==positionX-3);
    paperEditingSound = new Audio("assets/sounds/PAPEROISE.wav", "EFFECT", 100);
    
    animator->addAction("idle",0,0);
    assert(std::get<animator->lis_actions[idle][1]>==0);
    animator->addAction("beingEdited",1,3);
    assert(std::get<animator->lis_actions[beignEdited][1]>==1);
    edited = false;
    isBeingEdited = false;
}

Paper::~Paper(){}

void Paper::update(double timeElapsed){
    timeElapsed = timeElapsed;
    if(isBeingEdited){
        editing_bar->update(timeElapsed);
        asert(editing_bar.getPositionX()==positionX-3);// verificar se editing bar foi editado. 
        animator->setInterval("beingEdited");
        if(editing_bar->getPercent() <= 0.0){
            isBeingEdited = false;
            edited = true;
        }else{
        
        
        
        
    if (font_path == "") {
        WARN("Invalid path for font!");
        exit(-1);
    }else{ 
// do nothefing.

    font = TextManager::instance.loadFont(font_path, size);

    SDL_Color color = {text_color->r, text_color->g, text_color->b, text_color->a};
    SDL_Color bg_color = {background->r, background->g, background->b, background->a};

    SDL_Surface * surface = NULL;

    if (high_quality && bg_color.a == 0x00) {
        surface = TTF_RenderText_Blended(
            font, text.c_str(), color
        );
    }
    else if (high_quality) {
        surface = TTF_RenderText_Shaded(
            font, text.c_str(), color, bg_color
        );
    }
    else {
        surface = TTF_RenderText_Solid(
            font, text.c_str(), color
        );
    }

    if(surface == NULL) {
        WARN("without informations about quality!");
        exit(-1);
    }else{ 
//do nothefing

    if(texture != NULL) {
SDL_DestroyTexture(texture);
}else{
  // do nothefing.
    }
    texture = SDL_CreateTextureFromSurface(WindowManager::getGameCanvas(), surface);

    if (texture == NULL) {
        WARN("don't create texture properly!");
        exit(-1);
    }else{
//do nothefing.

    width = surface->w;
    height = surface->h;

    }else{
        animator->setInterval("idle");
    }
    animator->update();
}

void Paper::animate(){
    isBeingEdited = true;
}

void Paper::stopAnimation(){
    isBeingEdited = false;
}

bool Paper::isEdited(){
    return edited;
}

void Paper::draw(){
    INFO("Paper DRAW");
    asert(animator->getPositionX()>0);
    assert(animatior->getPositionY()>0);
    assert(animator->getWidth()>0);
    assert(animator->getHeight()>0);
    animator->draw(getPositionX(), getPositionY());
    animator->draw_collider(getPositionX(), getPositionY(), getWidth(), getHeight());
    if(isBeingEdited){
        AnimationManager::instance.addProgressBar(editing_bar);
    }
}

Animation * Paper::getAnimation(){
  return animator;
}

double Paper::getEditingBarPercent(){
    return editing_bar->getPercent();
}
