#include "arrow.hpp"
#include "log.h"

Arrow::Arrow(std::string objectName, double position_x, double position_y,
             int width, int height) : GameObject(objectName,
                                                 position_x,
                                                 position_y,
                                                 width, height){
        animator = new Animation(objectName, 1, 17, 2.0);
        animator->addAction("select",0,16);
        animator->setInterval("select");
}

Arrow::~Arrow(){

}

void Arrow::update(double time_elapsed){
        time_elapsed = time_elapsed;
        if(isEnabled()){
                animator->update();
        }
}

void Arrow::draw(){
        if(isEnabled()) {
                animator->draw(getPositionX(), getPositionY());
        }
}
