/*
Objective: this class implements a camera lever.
Author of the last update: lucas kishima dos santos.
Date:27/08/2017.
*/

#include "camera_lever.hpp"

using namespace engine;

#define FILE_NAME "assets/sprites/cenary/alavanca_sheet(17X20).png"
#define WIDTH 20
#define HEIGHT 20

CameraLever::CameraLever(double position_x, double position_y,
                         std::string direction) : GameObject(FILE_NAME, position_x,
                                                             position_y, WIDTH, HEIGHT) {
    animator = new Animation(FILE_NAME, 1, 3, 0.1);
    animator->addAction("up", 2,2);
    animator->addAction("mid",1,1);
    animator->addAction("down", 0,0);
    animator->setInterval("mid");
    direction = direction;
    state_inc = 1;
    state = 1;
}

void CameraLever::draw() {
    animator->draw(getPositionX(), getPositionY());
    animator->draw_collider(getPositionX(), getPositionY(), getWidth(), getHeight());
}

void CameraLever::update(double time_elapsed) {
    time_elapsed = time_elapsed;
    animator->update();
}

int CameraLever::getState() {
    return state;
}

void CameraLever::nextState() {
    if(state >= 2 || state <= 0) {
        state_inc *= -1;
    }

    state += state_inc;

    switch(state){
        case 0: animator->setInterval("up"); break;
        case 1: animator->setInterval("mid"); break;
        case 2: animator->setInterval("down"); break;
    }
}
