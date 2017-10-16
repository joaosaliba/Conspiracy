//#define NDEBUG *uncomment to disable assertions
#include "paper.hpp"
#include <assert.h>
#define INITIAL_PERCENTAGE 0.0

Paper::Paper(std::string object_name, double paper_position_x, double paper_position_y,
                                     int paper_width, int paper_height) : GameObject(object_name,
                                                                         paper_position_x,
                                                                         paper_position_y,
                                                                         paper_width, paper_height) {

    animator = new Animation(object_name, 1, 4, 0.5);

    std::vector<unsigned int> back_color = {22, 206, 26, 1};
    std::vector<unsigned int> front_color = {116, 225, 117, 1};
    paper_editing_bar = new ProgressBar(paper_position_x-3, paper_position_y-8, 22.5, 5, 0.005, back_color, front_color);

    paper_editing_sound = new Audio("assets/sounds/PAPEROISE.wav", "EFFECT", 100);

    animator->addAction("idle",0,0);
    animator->addAction("beingEdited",1,3);
    paper_edited = false;
    paper_is_being_edited = false;
    assert(paper_edited != NULL);
    assert(paper_is_being_edited != NULL);
}

Paper::~Paper(){}

void Paper::update(double time_elapsed){
    time_elapsed = time_elapsed;
    //If paper is being edited it sets the paper editing bar
    if(paper_is_being_edited) {
        paper_editing_bar->update(time_elapsed);
        animator->setInterval("beingEdited");
        //If paper is being edited it gets the percentage of the edition
        if(paper_editing_bar->getPercent() <= INITIAL_PERCENTAGE){
            paper_is_being_edited = false;
            paper_edited = true;
            assert(paper_edited != NULL);
            assert(paper_is_being_edited != NULL);
        //Paper is not being edited
        }else {
            animator->setInterval("idle");
            animator->update();
        }

    }else {
      //nothing to do
    }
}

void Paper::animate(){
    paper_is_being_edited = true;
    assert(paper_is_being_edited != NULL);
}

void Paper::stopAnimation(){
    paper_is_being_edited = false;
    assert(paper_is_being_edited != NULL);
}

bool Paper::isEdited(){
    return paper_edited;
    assert(paper_edited != NULL);
}

void Paper::draw(){
    INFO("Paper DRAW");
    animator->draw(getPositionX(), getPositionY());
    animator->draw_collider(getPositionX(), getPositionY(), getWidth(), getHeight());
    //It draws editing bar if the paper is being edited
    if(paper_is_being_edited){
        AnimationManager::instance.addProgressBar(paper_editing_bar);
    }else {
      //ProgressBar only apears if paper is being edited
    }
}

Animation * Paper::getAnimation(){
  return animator;
  assert(animator != NULL);
}

double Paper::getEditingBarPercent(){
    return paper_editing_bar->getPercent();
    assert(paper_editing_bar != NULL);
}

void Paper::resetEditingProgress(){
    paper_editing_bar->resetPercent();
    assert(paper_editing_bar != NULL);
}

void Paper::playEffect(){
    paper_editing_sound->play(0);
    assert(paper_editing_sound != NULL);
}

void Paper::stopEffect(){
    paper_editing_sound->stop();
    assert(paper_editing_sound != NULL);
}
