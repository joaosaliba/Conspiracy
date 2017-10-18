/**
 *   @file door_system.cpp
 *    @brief Manage the chair in the game.
 *    @copyright  GNU GENERAL PUBLIC LICENSE.
 */
#include "log.h"
#include "door_system.hpp"
#include <assert.h>
//#define NDEBUG *uncomment to disable assertions

/**
 *    @brief door_system object constructor.
 *    @param[in] positionX it sets the x coordinate of the object.
 *    @param[in] positionY it sets the y coordinate of the object.
 *    @param[in] width it sets the width dimension of the object.
 *    @param[in] height it sets the height dimension of the object.
 *    @param[in] objectName set the name of the object
 *
 */

DoorSystem::DoorSystem(std::pair<int,int> doorPosition,
                       std::pair<int,int> switchPosition, std::string doorSide){

    if(doorSide.compare("RIGHT") == 0 || doorSide.compare("LEFT") == 0){
        door = new Door("assets/sprites/cenary/porta_anima_lateral(40X59).png", doorPosition.first, doorPosition.second, 40, 60, doorSide);
    }else{
        door = new Door("assets/sprites/cenary/porta_anima.png", doorPosition.first, doorPosition.second, 79, 58, doorSide);
    }

    computerTable = new ComputerTable("assets/sprites/PC_sprites(34X20).png", switchPosition.first,switchPosition.second, 60, 24);
}
/**
 *    @brief DoorSystem object destructor.
 */
DoorSystem::~DoorSystem() {

}
/**
*    @brief update the DoorSystem  during the time.
*    @param[in] timeElapsed its about the time
*/
void DoorSystem::update(double timeElapsed){
    assert(timeElapsed !=NULL);
    door->update(timeElapsed);
    computerTable->update(timeElapsed);
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
/**
 *   @brief draws the animation of the chair according to its position
 *   @return void
 */
void DoorSystem::draw(){
    door->draw();
    computerTable->draw();
}
/**
 *   @brief get the way that the door be
 *   @return door
 */
GameObject* DoorSystem::getDoor(){
  if ( door == NULL){
    ERROR("Failed to start window manager");
      exit(-1);
  }
  else{
    return door;
  }
}
/**
 *   @brief get the actual way that the switch are
 *   @return computerTable->getDoorSwitch();
 */
GameObject* DoorSystem::getSwitch(){
  if ( computerTable->getDoorSwitch() == NULL){
    ERROR("Failed to start window manager");
      exit(-1);
  }
  else{
    return computerTable->getDoorSwitch();
  }
}
/**
 *   @brief get the actual way that the table are
 *   @return computerTable->getTable();
 */
GameObject* DoorSystem::getTable(){
  if ( computerTable->getTable() == NULL){
    ERROR("Failed to start window manager");
      exit(-1);
  }
  else{
      return computerTable->getTable();
  }

}
