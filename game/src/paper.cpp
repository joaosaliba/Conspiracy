#include "paper.hpp"

Paper::Paper(std::string objectName, double position_x, double position_y,
                                     int width, int height) : GameObject(objectName,
                                                                         position_x,
                                                                         position_y,
                                                                         width, height){

    animator = new Animation(objectName, 1, 4, 0.5);

    std::vector<unsigned int> back_color = {22, 206, 26, 1};
    std::vector<unsigned int> front_color = {116, 225, 117, 1};
    editing_bar = new ProgressBar(position_x-3, position_y-8, 22.5, 5, 0.005, back_color, front_color);

    paper_editing_sound = new Audio("assets/sounds/PAPEROISE.wav", "EFFECT", 100);

    animator->addAction("idle",0,0);
    animator->addAction("being_edited",1,3);
    edited = false;
    is_being_edited = false;
}

Paper::~Paper(){}

void Paper::update(double time_elapsed){
    time_elapsed = time_elapsed;
    if(is_being_edited){
        editing_bar->update(time_elapsed);
        animator->setInterval("being_edited");
        if(editing_bar->getPercent() <= 0.0){
            is_being_edited = false;
            edited = true;
        }
    }else{
        animator->setInterval("idle");
    }
    animator->update();
}

void Paper::animate(){
    is_being_edited = true;
}

void Paper::stopAnimation(){
    is_being_edited = false;
}

bool Paper::isEdited(){
    return edited;
}

void Paper::draw(){
    INFO("Paper DRAW");
    animator->draw(getPositionX(), getPositionY());
    animator->draw_collider(getPositionX(), getPositionY(), getWidth(), getHeight());
    if(is_being_edited){
        AnimationManager::instance.addProgressBar(editing_bar);
    }
}

Animation * Paper::getAnimation(){
  return animator;
}

double Paper::getEditingBarPercent(){
    return editing_bar->getPercent();
}

void Paper::resetEditingProgress(){
    editing_bar->resetPercent();
}

void Paper::playEffect(){
    paper_editing_sound->play(0);
}

void Paper::stopEffect(){
    paper_editing_sound->stop();
}
