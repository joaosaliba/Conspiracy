/**
    @file paper.cpp
    @brief Manage the interations with the papers on stages.
    @copyright MIT License.
*/

//#define NDEBUG *uncomment to disable assertions
#include "paper.hpp"
#include <assert.h>
#include "log.h"
struct { 
    int red;
    int green;
    int blue;
    int alpha;
} color;
type def struct color color2;
color2 BACK_COLOR;
#define BACK_COLOR.red=22;
#define BACK_COLOR.green=206;
#define BACK_COLOR.blue=26;
#define BACK_COLOR.alpha=1;
struct {
    int initial_position;
    int last_postion;
} action;
typdef action paper_action;
paper_action WATING;
#define const WATING.initial_position=0;
#define const WATING.last_position=0;
paper_action MOVE.
#define const MOVE.initial_position=1;
#define const WATING.last_position=3;
WATING.last_position,MOVE.initial_position
    

color2 FRONT_COLOR;
#define FRONT_COLOR.red=116;
#define FRONT_COLOR.green=225;
#define FRONT_COLOR.blue=117;
#define FRONT_COLOR.alpha=1;
struct{
    int columns;
    int rows,
    int time;
}animation;    
typedef animation animationpaper;
animationpaper ANIMATION_PAPER;
#define const ANIMATION_PAPER.columns=1;
#define const ANIMATION_PAPER.rows=4;
#define const ANIMATION_PAPER.time=0.5;


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

    animator = new Animation(object_name,ANIMATION_PAPER.columns,ANIMATION_PAPER.rows,ANIMATION_PAPER.time );
    assert(animator != NULL);
    animator->addAction("idle",WATING.initial_position,WATING.last_position);
    animator->addAction("beingEdited",WATING.last_position,MOVE.initial_position);

    std::vector<unsigned int> back_color = {BACK_COLOR.red,BACK_COLOR.green,BACK_COLOR.blue,BACK_COLOR.alpha};
    std::vector<unsigned int> front_color = {FRONT_COLOR.red,FRONT_COLOR.green,FRONT_COLOR.blue,FRONT_COLOR.alpha};
    assert(back_color != NULL);
    assert(front_color != NULL);

    paper_editing_bar = new ProgressBar(paper_position_x-3, paper_position_y-8, 22.5, 5, 0.005, back_color, front_color);
    paper_editing_sound = new Audio("assets/sounds/PAPEROISE.wav", "EFFECT", 100);
    assert(paper_editing_bar != NULL);
    assert(paper_editing_sound != NULL);

    paper_edited = false;
    paper_is_being_edited = false;
    assert(paper_edited == false);
    assert(paper_is_being_edited == false);
}

/**
    @brief Paper class destructor.
*/

Paper::~Paper(){}

/**
    @brief Gets the percentage of the edition.
*/

void Paper::getPercentage(){
  INFO("Getting percentage");
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
    INFO("Updating paper state");

    assert(time_elapsed != NULL);
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
    INFO("Initializing paper animation");

    paper_is_being_edited = true;
    assert(paper_is_being_edited == true);
}

/**
    @brief Stops the paper animation.
*/

void Paper::stopAnimation(){
    INFO("Stoping paper animation");
    paper_is_being_edited = false;
    assert(paper_is_being_edited == false);
}

/**
    @brief It sets the paper edition.
    @param[out] paper_edited bool that sets that the paper was edited.
*/

bool Paper::isEdited(){
    INFO("Verifying if paper is edited");
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
  INFO("Getting paper animation");
  return animator;
  assert(animator != NULL);
}

/**
    @brief Gets the percentage of paper that is edited.
*/

double Paper::getEditingBarPercent(){
    INFO("Getting editing bar percentage");
    return paper_editing_bar->getPercent();
    assert(paper_editing_bar != NULL);
}

/**
    @brief Resets editing progress.
*/

void Paper::resetEditingProgress(){
    INFO("Reseting paper editing percentage");
    paper_editing_bar->resetPercent();
    assert(paper_editing_bar != NULL);
}

/**
    @brief Start paper editing sound.
*/

void Paper::playEffect(){
    INFO("Starting editing sound");
    paper_editing_sound->play(0);
    assert(paper_editing_sound != NULL);
}

/**
    @brief Stop paper editing sound.
*/

void Paper::stopEffect(){
    INFO("Stoping editing sound");
    paper_editing_sound->stop();
    assert(paper_editing_sound != NULL);
}
