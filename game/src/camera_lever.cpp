#include "camera_lever.hpp"

using namespace engine;

#define FILENAME "assets/sprites/cenary/alavanca_sheet(17X20).png"
#define WIDTH 20
#define HEIGHT 20
/** objective : this class is responsble to create
* a lever for the camera object in the game
*/

CameraLever::CameraLever(double positionX, double positionY, std::string direction) : GameObject(FILENAME,positionX,positionY,
                                                                     WIDTH, HEIGHT){
    animator = new Animation(FILENAME, 1, 3, 0.1);
    animator->addAction("up", 2,2);
    animator->addAction("mid",1,1);
    animator->addAction("down", 0,0);
    animator->setInterval("mid");
    direction = direction;
    stateInc = 1;
    state = 1;
}
//Class responsable to draw where  pass lines  and set theirs positions
void CameraLever::draw(){
    animator->draw(getPositionX(), getPositionY());
    animator->draw_collider(getPositionX(), getPositionY(), getWidth(), getHeight());
}
//update camera 
void CameraLever::update(double timeElapsed){
    timeElapsed = timeElapsed;
    animator->update();
}
//check if the cameras are working
int CameraLever::getState(){
    return state;
}
// class responsable to set  off the camera and personages pass
void CameraLever::nextState(){
    if(state >= 2 || state <= 0){
        stateInc *= -1;
    }
    state += stateInc;
    switch(state){
        case 0: animator->setInterval("up"); break;
        case 1: animator->setInterval("mid"); break;
        case 2: animator->setInterval("down"); break;
    }
}
