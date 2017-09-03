#include "log.h"
#include "door_system.hpp"

using namespace engine;

DoorSystem::DoorSystem(std::pair<int,int> door_position,
                       std::pair<int,int> switch_position, std::string door_side){

    if(door_side.compare("RIGHT") == 0 || door_side.compare("LEFT") == 0){
        door = new Door("assets/sprites/cenary/porta_anima_lateral(40X59).png", door_position.first, door_position.second, 40, 60, door_side);
    }else{
        door = new Door("assets/sprites/cenary/porta_anima.png", door_position.first, door_position.second, 79, 58, door_side);
    }

    computer_table = new ComputerTable("assets/sprites/PC_sprites(34X20).png", switch_position.first,switch_position.second, 60, 24);
}
DoorSystem::~DoorSystem(){}

void DoorSystem::update(double time_elapsed){
    door->update(time_elapsed);
    computerTable->update(time_elapsed);
    if(!computerTable->getDoorSwitch()->isEnabled() && !door->isOpen()){
        door->setOpen(true);
        door->playEffect();
        if(door->getDoorSide().compare("DOWN") == 0){
            door->setEnabled(false);
        }else{
            door->setHeight(25);
        }
    }
}

void DoorSystem::draw(){
    door->draw();
    computerTable->draw();
}

GameObject* DoorSystem::getDoor(){
    return door;
}

GameObject* DoorSystem::getSwitch(){
    return computerTable->getDoorSwitch();
}

GameObject* DoorSystem::getTable(){
    return computer_table->getTable();
}
