//#define NDEBUG *uncomment to disable assertions
#include "paper.hpp"
#include <assert.h>
struct color {
  int red;
  int green;
  int blue;

  double alpha; 
}
BACKCOLOR.red,  BACKCOLOR.green, BACKCOLOR.black,BACKCOLOR.alpha
#define  const color BACKCOLOR.red=22
#define const color  BACKCOLOR.green=206;
#define const color BACKCOLOR.bue=26;
#define const color BACKCOLOR.alpha=1;
#define const color FRONTCOLOR.red=116;
#define const color FRONTCOLOR.green=225;
#define const color FRONTCOLOR.blue=117;
#define const color FRONTCOLOR.alpha=0.5;
struct  size{
   int rows;
   int columns;
}
struct size_figure{
  int with;
  int heigh;
}

struct margin{
   int left;
   int heigh;
}

MARGIN.left,MARGIN.heigh
#define const  margin MARGIN.left=3
#define const  margin MARGIN.heigh=8; 
#define  const size ANIMATION.rows=1;
#define const size ANIMATION.columns=4;
# define  const int TIME=0.5;
#define const size_figure PROGRESS.width=22.5;
#define const size_figure PROGRESS.heigh=5;
#define const int INCREMENT=0.005;
# const int TIMESTOPLAY =0
Paper::Paper(std::string object_name, double paper_position_x, double paper_position_y,
                                     int paper_width, int paper_height) : GameObject(object_name,
                                                                         paper_position_x,
                                                                         paper_position_y,
                                                                         paper_width, paper_height) {

    animator = new Animation(object_name, ANIMATION.rows,ANIMATION.columns,TIME);

    std::vector<unsigned int> back_color = {BACKCOLOR.red,  BACKCOLOR.green, BACKCOLOR.blue,BACKCOLOR.alpha};
    std::vector<unsigned int> front_color = {FRONTCOLOR.red,FRONTCOLOR.green,FRONTCOLOR.blue,FRONTCOLOR.alpha};
    paper_editing_bar = new ProgressBar(paper_position_x-MARGIN.left, paper_position_y-MARGIN.heigh,PROGRESS.width,PROGRESS.heigh, INCREMENT, back_color, front_color);

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
        if(paper_editing_bar->getPercent() <= 0.0){
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
    paper_editing_sound->play(TIMESTOPLAY);
    assert(paper_editing_sound != NULL);
}

void Paper::stopEffect(){
    paper_editing_sound->stop();
    assert(paper_editing_sound != NULL);
}
