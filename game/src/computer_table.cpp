/*
Objective: this class implements a computer table.
Author of the last update: lucas kishima dos santos.
Date:27/08/2017.
*/
#include "computer_table.hpp"
#include "log.h"

ComputerTable::ComputerTable(std::string object_name, double position_x, double position_y,
                             int width, int height) : GameObject(object_name, position_x,
                                                                 position_y, width, height) {

table = new Table("assets/sprites/mesa.png", position_x, position_y, width, height);

door_switch = new DoorSwitch("assets/sprites/PC_sprites(34X20).png",
                             position_x + 15, position_y - 7, 34, 60);
}

ComputerTable::~ComputerTable(){

}

void ComputerTable::update(double time_elapsed){
    table->update(time_elapsed);
    door_switch->update(time_elapsed);
}

void ComputerTable::draw(){
   table->draw();
   door_switch->draw();
}

DoorSwitch* ComputerTable::getDoorSwitch(){
    return door_switch;
}

Table* ComputerTable::getTable(){
    return table;
}
