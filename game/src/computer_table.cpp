#include "computer_table.hpp"
#include "log.h"

ComputerTable::ComputerTable(std::string objectName, double position_x, double position_y,
                                     int width, int height) : GameObject(objectName,
                                                                         position_x,
                                                                         position_y,
                                                                         width, height){
table = new Table("assets/sprites/mesa.png", position_x, position_y, width, height);
doorSwitch = new DoorSwitch("assets/sprites/PC_sprites(34X20).png", position_x + 15, position_y - 7, 34, 60);
}

ComputerTable::~ComputerTable(){

}

void ComputerTable::update(double time_elapsed){
   table->update(time_elapsed);
    doorSwitch->update(time_elapsed);
}

void ComputerTable::draw(){
   table->draw();
   doorSwitch->draw();
}

DoorSwitch* ComputerTable::getDoorSwitch(){
    return doorSwitch;
}

Table* ComputerTable::getTable(){
    return table;
}
