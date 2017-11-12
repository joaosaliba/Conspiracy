/**
 *   @file door_system.cpp
 *    @brief Manage the chair in the game.
 *    @copyright  GNU GENERAL PUBLIC LICENSE.
 */
#include "collision_manager.hpp"
#include "log.h"
#include <assert.h>

using namespace engine;

CollisionManager CollisionManager::instance;
/**
 *    @brief collision manager  add guard vision
 */
void CollisionManager::addGuardFieldOfVision(FieldOfVision* filed_vision){
        guardsVision.push_back(filed_vision);
}
/**
 *    @brief collision manager  add camera field
 */
void CollisionManager::addCameraFieldOfVision(FieldOfVision* field_vision){
        camerasVision.push_back(field_vision);
}
/**
 *    @brief collision manager  add wall
 */
void CollisionManager::addWall(GameObject* game_object){
        wallList.push_back(game_object);
}

void CollisionManager::addCameraSwitch(GameObject* game_object){
    cameraSwitchList.push_back(game_object);
}
/**
 *    @brief collision manager  add camera lever
 */
void CollisionManager::addCameraLever(GameObject* game_object){
    if(game_object != NULL){
        cameraLeverList.push_back(game_object);
    }
}
/**
 *    @brief collision manager  add guard
 */
void CollisionManager::addGuard(GameObject* game_object){
        guardList.push_back(game_object);
}
/**
 *    @brief collision manager  add paper ( object to be change in the game)
 */
void CollisionManager::addPaper(GameObject* game_object){
        paperList.push_back(game_object);
}
/**
 *    @brief collision manager  add door ( object to be opened when hakc computer)
 */
void CollisionManager::addDoor(GameObject* game_object){
        doorList.push_back(game_object);
}
/**
 *    @brief collision manager  add switch
 */
void CollisionManager::addSwitch(GameObject* game_object){
        switchList.push_back(game_object);
}
/**
 *    @brief collision manager  add chair
 */
void CollisionManager::addChair(GameObject* game_object){
        chairList.push_back(game_object);
}
/**
 *    @brief collision manager  add a finish point for the phase
 */
void CollisionManager::addFinishPoint(GameObject* game_object){
        finishPointList.push_back(game_object);
}
/**
 *    @brief collision manager  and verify if the personage have a collision with the walls
 *    @return bool
 */
bool CollisionManager::verifyCollisionWithWalls(GameObject* game_object_collision){
        for(GameObject * wall : wallList) {
                if(verifyCollision(wall, game_object_collision)) {
                        return true;
                }
                else{
                        //nothing to do
                }
        }
        for(GameObject* door : doorList) {
                if(door->isEnabled() && verifyCollision(door,game_object_collision)) {
                        return true;
                }
                else{
                        //nothing to do
                }
        }
        return false;
}
/**
 *    @brief collision manager  and verify if the personage have a collision with the walls and chairs
 *    @return bool
 */
bool CollisionManager::verifyCollisionWithWallsAndChairs(GameObject* game_object_collision){
        for(GameObject * wall : wallList) {
                if(verifyCollision(wall, game_object_collision)) {
                        return true;
                }
                else{
                        //nothing to do
                }
        }
        for(GameObject * chair : chairList) {
                if(verifyCollision(chair, game_object_collision)) {
                        return true;
                }
                else{
                        //nothing to do
                }
        }
        for(GameObject* door : doorList) {
                if(door->isEnabled() && verifyCollision(door,game_object_collision)) {
                        return true;
                }
                else{
                        //nothing to do
                }
        }
        return false;
}
/**
 *    @brief collision manager  verify the collisions with chairs
 *    @return ?
 */
std::pair<std::string, GameObject *> CollisionManager::verifyCollisionWithChairs(GameObject* game_object_collision){
        std::string collision = "";
        for(GameObject * chair : chairList) {
                if((collision = verifyCollisionChair(chair, game_object_collision))!="none") {
                        return std::pair<std::string, GameObject*>(collision, chair);
                }
                else{
                        //nothing to do
                }
        }
        return std::pair<std::string, GameObject*>(collision, NULL);
}
/**
 *    @brief collision manager  verify the collisions with  other chairs
 *    @return boll
 */
bool CollisionManager::verifyCollisionWithOtherChairs(GameObject* game_object){
  for(GameObject * chair : chairList) {
      if(chair != game_object){
            if(verifyCollision(chair, game_object)) {
                    return true;
            }
            else{
                //nothing to do
            }
      }
  }
  return false;
}

/**
 *    @brief collision manager  verify the collisions wth guards body
 *    @return bool
 */
bool CollisionManager::verify_collision_with_guardsBody(GameObject* game_object){
        for(GameObject * enemy : guardList) {
                if(verifyCollision(enemy, game_object)) {
                        return true;
                }
                else{
                        //nothing to do
                }
        }
        return false;
}
/**
 *    @brief collision manager  verify the collisions wth guards
 *    @return bool
 */

bool CollisionManager::verify_collision_with_guards(GameObject* game_object_collision){
    bool status = false;

        status = verify_collision_with_guardsBody(game_object_collision);
        if(status){
            return status;
        }else{
            status = verifyCollisionWithFieldsOfVision(game_object_collision, guardsVision);
            return status;
        }
        assert (status != NULL);
}
/**
 *    @brief collision manager  verify the collisions wth cameras( if personage were caught)
 *    @return bool
 */
bool CollisionManager::verify_collision_with_cameras(GameObject* game_object_collision){
    bool status = false;
    status = verifyCollisionWithFieldsOfVision(game_object_collision, camerasVision);
    assert (status != NULL);
    return status;
}
/**
 *    @brief collision manager  verify if the personage where in the plane vision of the guards or cameras
 *    @return bool
 */
bool CollisionManager::verifyCollisionWithFieldsOfVision(GameObject* game_object_collision, std::vector<FieldOfVision*> fields){
    bool isVisible = true;
    for(FieldOfVision* field : fields) {
        if(field->isActive()){
            for(Line* line : field->getLines()) {
                    if(verifyRectangleCollisionWithLine(game_object_collision,line->getPoint1(),line->getPoint2())) {
                            std::pair<double,double> playerCenter = game_object_collision->getCenter();
                            int distanceBetweenPlayer = calculateDistance(playerCenter,line->getPoint1()); // declareting varible distance betwen players
                            // Margin between player and line
                            // Or else just touching a line would make you lose
                            if(distanceBetweenPlayer < field->getRange()*0.85) {
                                    for(auto wall : wallList) {
                                            if(verifyRectangleCollisionWithLine(wall,line->getPoint1(),line->getPoint2())) {
                                                    std::pair<double,double> wallCenter = wall->getCenter();
                                                    int distanceBetweenWall = calculateDistance(wallCenter,line->getPoint1());// declareting varible distance betwen wall
                                                    //Wall in front of player
                                                    if(distanceBetweenWall < distanceBetweenPlayer) {
                                                            isVisible = false;
                                                    }
                                            }
                                    }
                                    if((isVisible && game_object_collision->isVisible())) {
                                            field->playEffect();
                                            return true;
                                    }
                                    else{
                                        //nothing to do
                                    }
                            }
                            else{
                                //nothing to do
                            }
                    } else{
                        //nothing to do
                      }
            }
        }
        else{
                //nothing to do
        }
    }
    return false;
    assert( isVisible != NULL);
}
/**
 *    @brief collision manager  and verify the interection with the switches
 *    @return null
 */
GameObject* CollisionManager::verify_collision_with_switches(GameObject* game_object_collision){
        for(GameObject * doorSwitch : switchList) {
                if(verifyCollision(doorSwitch, game_object_collision)) {
                        return doorSwitch;
                }
                else{
                        //nothing to do
                }
        }
        return NULL;
}
/**
 *    @brief collision manager  and verify the interection with the camera switches
 *    @return null
 */
GameObject* CollisionManager::verify_collision_with_cameraswitches(GameObject* game_object){
    for(GameObject * cameraSwitch : cameraSwitchList) {
            if(verifyCollision(cameraSwitch, game_object)) {
                    return cameraSwitch;
            }
            else{
                //nothing to do
           }
    }
    return NULL;

}
/**
 *    @brief collision manager  and verify the interection with the cameras levers
 *    @return null
 */
GameObject* CollisionManager::verifyCollisionWithCameraLevers(GameObject* game_object){
    for(GameObject * lever : cameraLeverList) {
            if(verifyCollision(lever, game_object)) {
                    return lever;
            }
            else{
                //nothing to do
        }
    }
    return NULL;
}
/**
 *    @brief collision manager  and verify the interection with the papers
 *    @return null
 */
GameObject* CollisionManager::verify_collision_with_papers(GameObject* game_object_collision){
        for(GameObject * paper : paperList) {
                if(verifyCollision(paper, game_object_collision)) {
                        return paper;
                }
                else{
                        //nothing to do
                }
        }
        return NULL;
}
/**
 *    @brief collision manager  and verify the finishs points
 *    @return null
 */
GameObject* CollisionManager::verify_collision_with_finish_points(GameObject* game_object_collision){
    for(GameObject * finishPoint : finishPointList) {
            if(verifyCollision(finishPoint, game_object_collision)) {
                    return finishPoint;
            }else{
                //nothing to do
            }
    }
    return NULL;
}
/**
 *    @brief collision manager  calculate the distance between the things
 *    @return double sqrt
 */

double CollisionManager::calculateDistance(std::pair<double,double> center, std::pair<double,double> lineCenter){
        return sqrt(((center.first-lineCenter.first)*
                     (center.first-lineCenter.first))+
                    ((center.second-lineCenter.second)*
                     (center.second-lineCenter.second)));
}
/**
 *    @brief reset: walllist,guard,list,paperlist,doorlist,swithclist,chairlist,
 *                  guardsvision,camerasvision,cameralerverlist,and cameraswitchlever
 */
void CollisionManager::resetLists(){
        wallList.clear();
        guardList.clear();
        paperList.clear();
        doorList.clear();
        switchList.clear();
        chairList.clear();
        guardsVision.clear();
        camerasVision.clear();
        cameraLeverList.clear();
        cameraSwitchList.clear();
}
/**
 *    @brief collision manager  and verify if the personage have a collision
 *    @return bool
 */
bool CollisionManager::verifyCollision( GameObject* game_object_collision, GameObject* game_object_collision2){
        //The sides of the rectangles
        int leftA, rightA, topA, bottomA; //declarating variables
        int leftB, rightB, topB, bottomB; //declarating variables

        assert (leftA != NULL);
        assert (rightA != NULL);
        assert (topA != NULL);
        assert (buttonA != NULL);
        assert (leftB != NULL);
        assert (rightB != NULL);
        assert (topB != NULL);
        assert (buttonB != NULL);
        //Calculate the sides of rect A
        leftA = game_object_collision->getPositionX();
        rightA = leftA + game_object_collision->getWidth();
        topA = game_object_collision->getPositionY();
        bottomA = topA + game_object_collision->getHeight();

        //Calculate the sides of rect B
        leftB = game_object_collision2->getPositionX();
        rightB = leftB + game_object_collision2->getWidth();
        topB = game_object_collision2->getPositionY();
        bottomB = topB + game_object_collision2->getHeight();

        if(game_object_collision2->getWidth() == 0 || game_object_collision2->getHeight() == 0) {
                return false;
        }
        else{
                //nothing to do
        }
        if(game_object_collision->getWidth() == 0 || game_object_collision->getHeight() == 0) {
                return false;
        }
        else{
                //nothing to do
        }

        //If any of the sides from A are outside of B
        if( bottomA <= topB ) { 
                return false; 
        }
        else{
                //nothing to do
        }
        if( topA >= bottomB ) {
                 return false; 
        }
        else{
                //nothing to do
        }
        if( rightA <= leftB ) {
                 return false; 
        }
        else{
                //nothing to do
        }
        if( leftA >= rightB ) { 
                return false;
        }
        else{
                //nothing to do
        }
        //If none of the sides from A are outside B
        return true;
}
/**
 *    @brief collision manager  and verify if the rectangle game have a collision with the reference line
 *    @return bool
 */
bool CollisionManager::verifyRectangleCollisionWithLine(GameObject* game_object, std::pair<int, int> a, std::pair<int, int> b){
        std::pair<std::pair<int, int>, std::pair<int, int> > top;
        std::pair<std::pair<int, int>, std::pair<int, int> > right;
        std::pair<std::pair<int, int>, std::pair<int, int> > left;
        std::pair<std::pair<int, int>, std::pair<int, int> > bottom;

        top.first.first = game_object->getPositionX();
        top.first.second = game_object->getPositionY();
        top.second.first = game_object->getPositionX()+game_object->getWidth();
        top.second.second= game_object->getPositionY();

        right.first.first = game_object->getPositionX()+game_object->getWidth();
        right.first.second = game_object->getPositionY();
        right.second.first = game_object->getPositionX()+game_object->getWidth();
        right.second.second= game_object->getPositionY()+game_object->getHeight();

        left.first.first = game_object->getPositionX();
        left.first.second = game_object->getPositionY();
        left.second.first = game_object->getPositionX();
        left.second.second= game_object->getPositionY()+game_object->getHeight();

        bottom.first.first = game_object->getPositionX();
        bottom.first.second = game_object->getPositionY()+game_object->getHeight();
        bottom.second.first = game_object->getPositionX()+game_object->getWidth();
        bottom.second.second= game_object->getPositionY()+game_object->getHeight();

        if(verifyLineCollisionWithLine(top.first,top.second,a,b)) {
                return true; 
        } else{
                //nothing to do
        }
        if(verifyLineCollisionWithLine(right.first,right.second,a,b)) {
                return true; 
        }
        else{
                //nothing to do
        }
        if(verifyLineCollisionWithLine(left.first,left.second,a,b)) {
                return true;
        }
        else{
                //nothing to do
        }
        if(verifyLineCollisionWithLine(bottom.first,bottom.second,a,b)) {
                return true;
        }
        else{
                //nothing to do
        }
        return false;
}
/**
 *    @brief collision manager  and verify  the collisions lines
 *    @return int
 */
bool CollisionManager::verifyLineCollisionWithLine(std::pair<int, int> line_a, std::pair<int, int> line_b, std::pair<int, int> line_c, std::pair<int, int> line_d){
        return (CCW(line_a,line_b,line_c)*CCW(line_a,line_b,line_d)<0 && CCW(line_c,line_d,line_b)*CCW(line_c,line_d,line_a)<0);
}
/**
 *    @brief collision manager  and verify the time when happens the collision
 *    @return int
 */
double CollisionManager::CCW(std::pair<int, int> line_a, std::pair<int, int> line_b, std::pair<int, int> line_c){
        return (line_b.first-line_a.first)*(line_c.second-line_a.second) - (line_b.second-line_a.second)*(line_c.first-line_a.first);
}

/**
 *    @brief collision manager  and verify if the personage have a collision with the chairs
 *    @return string
 */
std::string CollisionManager::verifyCollisionChair(GameObject* game_object_collision, GameObject* game_object_collision2){
        //The sides of the rectangles
        int leftA, rightA, topA, bottomA;  // declareting varibles
        int leftB, rightB, topB, bottomB; // declareting varibles

        //Calculate the sides of rect A
        leftA = game_object_collision->getPositionX();
        rightA = leftA + game_object_collision->getWidth();
        topA = game_object_collision->getPositionY();
        bottomA = topA + game_object_collision->getHeight();

        //Calculate the sides of rect B
        leftB = game_object_collision2->getPositionX();
        rightB = leftB + game_object_collision2->getWidth();
        topB = game_object_collision2->getPositionY();
        bottomB = topB + game_object_collision2->getHeight();

        if(game_object_collision2->getWidth() == 0 || game_object_collision2->getHeight() == 0) {
                return "none";
        }
        else{
                //nothing to do
        }
        if(game_object_collision->getWidth() == 0 || game_object_collision->getHeight() == 0) {
                return "none";
        }
        else{
                //nothing to do
        }

        if(rightB > (leftA - 3) && rightA > (rightB)) {
                if((bottomB < (bottomA) && bottomB > (topA)) || (topB < bottomA && topB > topA)) {
                        return "right";
                }
                else{
                        //nothing to do
                }
                if((bottomA < bottomB && bottomA > topB) || (topA < bottomB && topA > topB)) {
                        return "right";
                }
                else{
                        //nothing to do
                }
        }
        else{
                //nothing to do
        }

        if(leftB < (rightA + 3) && leftA < (leftB)) {
                if((bottomB < bottomA && bottomB > topA) ||(topB < bottomA && topB > topA)) {
                        return "left";
                }
                else{
                        //nothing to do
                }
                if((bottomA < bottomB && bottomA > topB) || (topA < bottomB && topA > topB)) {
                        return "left";
                }
                else{
                        //nothing to do
                }
        }
        else{
                //nothing to do
        }

        if(topB <= (bottomA + 3) && (topB) > topA) {
                if((leftB >= leftA && leftB <= rightA) || (rightB <= rightA && rightB >= leftA)) {
                        return "up";
                } else{
                        //nothing to do
                }
                if((leftA >= leftB && leftA <= rightB) || (rightA <= rightB && rightA >= leftB)) {
                        return "up";
                } else{
                        //nothing to do
                }
        }
        else{
                //nothing to do
        }

        if(bottomB >= (topA - 3) && bottomA > (bottomB)) {
                if((leftB >= leftA && leftB <= rightA) || (rightB <= rightA && rightB >= leftA)) {
                        return "down";
                } 
                else{
                        //nothing to do
                }
                if((leftA >= leftB && leftA <= rightB) || (rightA <= rightB && rightA >= leftB)) {
                        return "down";
                }
                else{
                        //nothing to do
                }
        }
        else{
                //nothing to do
        }

        return "none";
}
