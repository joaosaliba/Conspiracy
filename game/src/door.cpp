#include "door.hpp"

Door::Door(std::string object_name, double position_x, double position_y,
           int width, int height, std::string door_side) : GameObject(object_name,
                                                                     position_x,
                                                                     position_y,
                                                                     width,
                                                                     height){

    if(door_side.compare("DOWN") == 0) {
        animator = new animation(object_name, 1, 4, 0.5);
        animator->add_action("closed", 0,0);
        animator->add_action("open",1,3);
    }else if(door_side.compare("RIGHT") == 0) {
        animator = new animation(object_name, 1, 8, 0.5);
        animator->add_action("closed", 0,0);
        animator->add_action("open",1,3);
    }else if(door_side.compare("LEFT") == 0) {
        animator = new animation(object_name, 1, 8, 0.5);
        animator->add_action("closed", 4,4);
        animator->add_action("open",5,7);
    }

    side = door_side;
    door_effect = new Audio("assets/sounds/DOOR.wav", "EFFECT", 90);

    animator->set_draw_size(width,height);
    open = false;
}

Door::~Door(){}

void Door::update(double time_elapsed) {
    time_elapsed = time_elapsed;
    if(animator->get_current_position_frame()!=3 && animator->get_current_position_frame() != 7){
        animator->update();
    }
    if(is_open()) {
        animator->set_interval("open");
    }else{
        animator->set_interval("closed");
    }
}

void Door::draw() {
    INFO("Door DRAW");
    animator->draw(get_position_x(), get_position_y());
    animator->draw_collider(get_position_x(), get_position_y(), get_width(), get_height());
}

animation * Door::get_animation() {
  return animator;
}

bool Door::is_open() {
        return open;
}

void Door::set_open(bool status) {
        open = status;
}

void Door::play_effect() {
    door_effect->play(0);
}

std::string Door::get_door_side() {
    return side;
}
