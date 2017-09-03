#include "door.hpp"

Door::Door(std::string objectName, double position_x, double position_y,
           int width, int height, std::string doorSide) : GameObject(object_name,
                                                                     position_x,
                                                                     position_y,
                                                                     width,
                                                                     height){

    if(doorSide.compare("DOWN") == 0){
        animator = new Animation(object_name, 1, 4, 0.5);
        animator->addAction("closed", 0,0);
        animator->addAction("open",1,3);
    }else if(doorSide.compare("RIGHT") == 0){
        animator = new Animation(object_name, 1, 8, 0.5);
        animator->addAction("closed", 0,0);
        animator->addAction("open",1,3);
    }else if(doorSide.compare("LEFT") == 0){
        animator = new Animation(object_name, 1, 8, 0.5);
        animator->addAction("closed", 4,4);
        animator->addAction("open",5,7);
    }

    side = doorSide;
    door_effect = new Audio("assets/sounds/DOOR.wav", "EFFECT", 90);

    animator->setDrawSize(width,height);
    open = false;
}

Door::~Door(){}

void Door::update(double time_elapsed){
    time_elapsed = time_elapsed;
    if(animator->getCurrentPositionFrame()!=3 && animator->getCurrentPositionFrame()!=7){
        animator->update();
    }
    if(isOpen()){
        animator->setInterval("open");
    }else{
        animator->setInterval("closed");
    }
}

void Door::draw(){
    INFO("Door DRAW");
    animator->draw(getPositionX(), getPositionY());
    animator->draw_collider(getPositionX(), getPositionY(), getWidth(), getHeight());
}

Animation * Door::getAnimation(){
  return animator;
}

bool Door::isOpen(){
        return open;
}

void Door::setOpen(bool status){
        open = status;
}

void Door::playEffect(){
    door_effect->play(0);
}

std::string Door::getDoorSide(){
    return side;
}
