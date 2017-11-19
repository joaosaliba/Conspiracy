#include "door.hpp"

Door::Door(std::string objectName, double position_x, double position_y,
           int width, int height, std::string doorSide) : GameObject(objectName,
                                                                     position_x,
                                                                     position_y,
                                                                     width,
                                                                     height){

    if(doorSide.compare("DOWN") == 0){
        animator = new Animation(objectName, 1, 4, 0.5);
        animator->add_action("closed", 0,0);
        animator->add_action("open",1,3);
    }else if(doorSide.compare("RIGHT") == 0){
        animator = new Animation(objectName, 1, 8, 0.5);
        animator->add_action("closed", 0,0);
        animator->add_action("open",1,3);
    }else if(doorSide.compare("LEFT") == 0){
        animator = new Animation(objectName, 1, 8, 0.5);
        animator->add_action("closed", 4,4);
        animator->add_action("open",5,7);
    }

    side = doorSide;
    door_effect = new Audio("assets/sounds/DOOR.wav", "EFFECT", 90);

    animator->setDrawSize(width,height);
    open = false;
}

Door::~Door(){}

void Door::update(double timeElapsed){
    timeElapsed = timeElapsed;
    if(animator->getCurrentPositionFrame()!=3 && animator->getCurrentPositionFrame()!=7){
        animator->update();
    }
    if(isOpen()){
        animator->set_interval("open");
    }else{
        animator->set_interval("closed");
    }
}

void Door::draw(){
    INFO("Door DRAW");
    animator->draw(get_position_x(), get_position_y());
    animator->draw_collider(get_position_x(), get_position_y(), get_width(), get_height());
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

void Door::play_effect(){
    door_effect->play(0);
}

std::string Door::get_doorSide(){
    return side;
}
