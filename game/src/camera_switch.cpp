#include "camera_switch.hpp"

using namespace engine;

#define FILE_NAME "assets/sprites/cenary/switch_cameras(14X16).png"
#define WIDTH 14
#define HEIGHT 16
#define ADJUST_X 10

CameraSwitch::CameraSwitch(double position_x, double position_y,
                           std::string direction) : GameObject(filename,
                                                               position_x - adjust_x,
                                                               position_y - adjust_x,
                                                               width+adjust_x*2,
                                                               heigh+adjust_x*2) {
    animator = new Animation(FILE_NAME, 1, 2, 0.1);
    switch_efffect = new Audio("assets/sounds/TURNOFFCAMERA.wav", "EFFECT", 128);

    animator->addAction("on", 0,0);
    animator->addAction("off",1,1);
    animator->setInterval("on");
    direction = direction;
    working = true;
}

void CameraSwitch::draw() {
    animator->draw_instant(getPositionX()+adjust_x, getPositionY()+adjust_x);
    animator->draw_collider(getPositionX(), getPositionY(), getWidth(), getHeight());
}

void CameraSwitch::update(double time_elapsed) {
    time_elapsed = time_elapsed;
    animator->update();
}

bool CameraSwitch::isWorking() {
    return working;
}

void CameraSwitch::turnOff() {
    if(animator->getInterval().first!="off") {
        working = false;
        animator->setInterval("off");
        switch_efffect->play(0);
    }
}
