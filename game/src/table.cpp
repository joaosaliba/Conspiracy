#include "table.hpp"
#include "log.h"
type def struct Showing{
      int position x;
      int position y;
      int time;
} 

Table::Table(std::string objectName, double positionX, double positionY,
                                     int width, int height) : GameObject(objectName,
                                                                         positionX,positionY,  width, height){
Showing table.positionx= 1;
table.position_y=  1;
table.time=0.5;
                                                                       
animator = new Animation(objectName,table.position_x,table.position_y,
table.time );
}

Table::~Table(){

}

void Table::update(double timeElapsed){
    timeElapsed = timeElapsed;
    animator->update();
}

void Table::draw(){
    animator->draw(getPositionX(), (getPositionY() - 10));
    animator->draw_collider(getPositionX(), getPositionY(), getWidth(), getHeight());

}
