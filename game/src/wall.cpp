#include "wall.hpp"
#include "log.h"

Wall::Wall(std::string objectName, double position_x, double position_y,
                                     int width, int height) : GameObject(objectName,
                                                                         position_x,
                                                                         position_y,
                                                                         width, height){
animator = new Animation(objectName, 1, 1, 0.5);
}

Wall::~Wall(){}
void Wall::update(double timeElapsed){
    timeElapsed = timeElapsed;
    animator->update();
}

void Wall::draw(){
    if(getName().compare("assets/sprites/cenary/parede2.png") == 0){
        animator->draw(get_position_x(), get_position_y()-25);
    }else{
        animator->draw(get_position_x(), get_position_y());
    }
    animator->draw_collider(get_position_x(), get_position_y(), get_width(), get_height());
}
