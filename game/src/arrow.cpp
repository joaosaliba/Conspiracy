/*
Objective: this class implements an arrow.
Author of the last update: lucas kishima dos santos.
Date:27/08/2017.
*/

#include "arrow.hpp"
#include "log.h"

Arrow::Arrow(std::string object_name, double position_x, double position_y,
             int width, int height) : GameObject(object_name, position_x,
                                                 position_y, width, height){
    animator = new Animation(object_name, 1, 17, 2.0);
    animator->addAction("select",0,16);
    animator->setInterval("select");
}

Arrow::~Arrow(){

}

void Arrow::update(double timeElapsed) {
    timeElapsed = timeElapsed;

    if(isEnabled()) {
        animator->update();
        }
}

void Arrow::draw() {
    if(isEnabled()) {
        animator->draw(getPositionX(), getPositionY());
    }
}
