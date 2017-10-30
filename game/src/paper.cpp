/**
    @file paper.cpp
    @brief Manage the interations with the papers on stages.
    @copyright MIT License.
*/

//#define NDEBUG *uncomment to disable assertions
#include "paper.hpp"
#include <assert.h>
#define INITIAL_PERCENTAGE 0.0

/**
    @brief Paper class constructor.
    @param[in] object_name stirng that contains the name of the object.
    @param[in] paper_position double parameter with the coordinates of the object.
    @param[in] paper_width paper width dimension
    @param[in] paper_height paper height dimension
*/

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

/**
    @brief Paper class destructor.
*/

Paper::~Paper(){}

/**
    @brief Gets the percentage of the edition.
*/

void Paper::getPercentage(){
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
}

/**
    @brief Updates the paper object state.
*/

void Paper::update(double time_elapsed){
    time_elapsed = time_elapsed;
    //If paper is being edited it sets the paper editing bar
    if(paper_is_being_edited) {
        paper_editing_bar->update(time_elapsed);
        animator->setInterval("beingEdited");
        getPercentage();

    }else {
      //nothing to do
    }
}

/**
    @brief Start paper animation.
*/

void Paper::animate(){
    paper_is_being_edited = true;
    assert(paper_is_being_edited != NULL);
}

/**
    @brief Stops the paper animation.
*/

void Paper::stopAnimation(){
    paper_is_being_edited = false;
    assert(paper_is_being_edited != NULL);
}

/**
    @brief It sets the paper edition.
    @param[out] paper_edited bool that sets that the paper was edited.
*/

bool Paper::isEdited(){
    return paper_edited;
    assert(paper_edited != NULL);
}

/**
    @brief Draws the instance of paper object.
*/

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

/**
    @brief Gets paper animation.
*/

Animation * Paper::getAnimation(){
  return animator;
  assert(animator != NULL);
}

/**
    @brief Gets the percentage of paper that is edited.
*/

double Paper::getEditingBarPercent(){
    return paper_editing_bar->getPercent();
    assert(paper_editing_bar != NULL);
}

/**
    @brief Resets editing progress.
*/

void Paper::resetEditingProgress(){
    paper_editing_bar->resetPercent();
    assert(paper_editing_bar != NULL);
}

/**
    @brief Start paper editing sound.
*/

void Paper::playEffect(){
    paper_editing_sound->play(0);
    assert(paper_editing_sound != NULL);
}

/**
    @brief Stop paper editing sound.
*/

void Paper::stopEffect(){
    paper_editing_sound->stop();
    assert(paper_editing_sound != NULL);
}
