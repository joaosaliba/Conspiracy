
#include "table.hpp"
#include "log.h"
#include <assert.h>
Table::Table(std::string objectName, double positionX, double positionY,
                                     int width, int height) : GameObject(objectName,
                                                                         positionX,
                                                                         positionY,
                                                                         width, height){
animator = new Animation(objectName, 1, 1, 0.5);
assert( background.getCurrentPositionFrame()==0);
}

Table::~Table(){

}

void Table::update(double timeElapsed){
    timeElapsed=0.0; 
    timeElapsed = timeElapsed;
    assert(timeElapsed>0.0);
    animator->update();
}

void Table::draw(){
    animator->draw(getPositionX(), (getPositionY() - 10));
    animator->draw_collider(getPositionX(), getPositionY(), getWidth(), getHeight());

}
