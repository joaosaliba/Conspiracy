#include "ground.hpp"
#include "log.h"

Ground::Ground(std::string object_name, double position_x, double position_y,
                                     int width, int height) : GameObject(object_name,
                                                                         position_x,
                                                                         position_y,
                                                                         width, height){
animator = new Animation(object_name, 1, 1, 0.5);
}

Ground::~Ground(){}
void Ground::update(double time_elapsed){
    time_elapsed = time_elapsed;
    animator->update();
}

void Ground::draw(){
    animator->draw_instant(getPositionX(), getPositionY());
}
