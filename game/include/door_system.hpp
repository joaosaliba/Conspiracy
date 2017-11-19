#ifndef DOOR_SYSTEM_HPP
#define DOOR_SYSTEM_HPP

#include "engine.hpp"
#include "door.hpp"
#include "door_switch.hpp"
#include "computer_table.hpp"

using namespace engine;
/**
*objective : this class is responsable to instace  the variables
* for being used in door system cpp
*/
class DoorSystem: public GameObject{
public:
    DoorSystem(std::pair<int,int> doorPosition, std::pair<int,int> switchPosition, std::string doorSide);
    ~DoorSystem();
    void update(double time_elapsed);
    void draw();
    GameObject* get_door();
    GameObject* getSwitch();
    GameObject* getTable();
private:
    Door* door = nullptr;
    ComputerTable * computerTable = nullptr;
};
#endif
