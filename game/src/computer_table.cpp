/**
 *   @file computer_table.cpp
 *    @brief Manage the chair in the game.
 *    @copyright  GNU GENERAL PUBLIC LICENSE.
 */
#include "computer_table.hpp"
#include "log.h"
#include <assert.h>
//#define NDEBUG *uncomment to disable assertions

/**
 *    @brief Computer_table object constructor.
 *    @param[in] positionX it sets the x coordinate of the object.
 *    @param[in] positionY it sets the y coordinate of the object.
 *    @param[in] width it sets the width dimension of the object.
 *    @param[in] height it sets the height dimension of the object.
 *    @param[in] objectName set the name of the object
 *
 */
ComputerTable::ComputerTable(std::string objectName, double positionX, double positionY,
                                     int width, int height) : GameObject(objectName,
                                                                         positionX,
                                                                         positionY,
                                                                         width, height){
  assert (positionX !=NULL);
  assert (positionY !=NULL);
  assert (width !=NULL);
  assert (height !=NULL);
  table = new Table("assets/sprites/mesa.png", positionX, positionY, width, height);
  doorSwitch = new DoorSwitch("assets/sprites/PC_sprites(34X20).png", positionX + 15, positionY - 7, 34, 60);
  INFO("Computer Table Constructor ");
}
/**
 *    @brief ComputetTable object destructor.
 */
ComputerTable::~ComputerTable(){
  INFO("Computer Table Destructor ");

}

/**
 *   @brief draws the animation of the chair according to its position
 *   @return void
 */
void ComputerTable::draw(){
   table->draw();
   doorSwitch->draw();
   INFO("Draw Computer Table  ");
}

/**
*    @brief update the ComputerTable  during the time.
*    @param[in] timeElapsed its about the time
*/
void ComputerTable::update(double timeElapsed){
   assert(timeElapsed != NULL);
   table->update(timeElapsed);
    doorSwitch->update(timeElapsed);
    INFO("Update Computer Table  ");
}

/**
 *   @brief get the actual way that the switch are
 *   @return doorSwitch
 */
DoorSwitch* ComputerTable::getDoorSwitch(){
  if ( doorSwitch == NULL){
    ERROR("Failed to start window manager");
      exit(-1);
  }
  else{
    return doorSwitch;
  }
  INFO("Get door switch in Computer Table  ");

}
/**
 *   @brief get the situation that the computer table are
 *   @return table;
 */
Table* ComputerTable::getTable(){
  if ( table == NULL){
    ERROR("Failed to start window manager");
      exit(-1);
  }
  else{
    return table;
  }
  INFO("get Table in Computer Table  ");
}
