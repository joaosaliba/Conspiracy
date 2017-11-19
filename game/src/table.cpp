#include "table.hpp"
#include "log.h"

Table::Table(std::string objectName, double position_x, double position_y,
                                     int width, int height) : GameObject(objectName,
                                                                         position_x,
                                                                         position_y,
                                                                         width, height){
animator = new Animation(objectName, 1, 1, 0.5);
}

Table::~Table(){

}

void Table::update(double timeElapsed){
    timeElapsed = timeElapsed;
    animator->update();
}

void Table::draw(){
    animator->draw(get_position_x(), (get_position_y() - 10));
    animator->draw_collider(get_position_x(), get_position_y(), get_width(), get_height());

}
