#include "alien_varginha.hpp"

#define FILENAME "assets/sprites/varginha_sheet.png"
#define WIDTH 10
#define HEIGHT 15

Varginha::Varginha(double position_x, double position_y) : Alien(FILENAME, position_x, position_y, WIDTH, HEIGHT) {

   animator->addAction("special_right",12,13);
   animator->addAction("special_left",10,11);
   animator->addAction("invisible_right", 13, 13);
   animator->addAction("invisible_left", 11, 11);
   animator->addAction("action_right", 17, 19);
   animator->addAction("action_left", 14, 16);
   is_invisible = false;
   is_selected = false;
   in_position = false;
   turnOff = false;

   timerTurn = new Timer();
   timerTurn->start();
}

void Varginha::update(double time_elapsed) {
    in_position = false;
    animator->setTotalTime(0.3);
    auto inc_y = 0.15*time_elapsed;
    auto inc_x = 0.15*time_elapsed;

    if(!block_movement && is_selected) {
        walkInX(inc_x);
        walkInY(inc_y, inc_x);
    }


    if((inc_x == 0 && inc_y == 0) || (!turnOff && !is_selected)) {
        if(idleAnimationNumber) {
          animator->setInterval("idle_right");
        }else { 
          animator->setInterval("idle_left");
        }
    }
    specialAction();
    verifyTurn();

    if(CollisionManager::instance.verifyCollisionWithGuards(this)) {
        setEnabled(false);
    }

    FinishPoint* finishPoint = (FinishPoint*)CollisionManager::instance.verifyCollisionWithFinishPoints(this);
    if(finishPoint != NULL) {
        if(finishPoint->getAlienNames().find("V") != std::string::npos) {
            in_position = true;
        }
    }

    animator->update();
}

void Varginha::specialAction() {
    std::pair<int, int> interval;

    if(is_invisible) {
        if(idleAnimationNumber == 5) {
            animator->setInterval("invisible_right");
        }else {
            animator->setInterval("invisible_left");
        }
    }else if(is_selected) {
            CameraSwitch* cameraSwitch = NULL;
            CameraLever* cameraLever = NULL;
            cameraSwitch = (CameraSwitch*)CollisionManager::instance.verifyCollisionWithCameraSwitches(this);
            cameraLever = (CameraLever*)CollisionManager::instance.verifyCollisionWithCameraLevers(this);

            if((cameraSwitch != NULL) || (cameraLever != NULL)) {
                   if(InputManager::instance.isKeyTriggered(InputManager::KEY_PRESS_SPACE)) {
                       int x = 0;
                       if(cameraSwitch!= NULL) {
                           cameraSwitch->turnOff();
                           x = cameraSwitch->getPositionX();
                       }else if(cameraLever != NULL) {
                           cameraLever->nextState();
                           x = cameraLever->getPositionX();
                       }

                       if(x > getPositionX()) {
                           animator->setInterval("action_right");
                           idleAnimationNumber = 5;
                       }else {
                           animator->setInterval("action_left");
                           idleAnimationNumber = 0;
                       }
                       block_movement = true;
                       turnOff = true;
                       timerTurn->step();
                   }
           }else if(InputManager::instance.isKeyPressed(InputManager::KEY_PRESS_SPACE)){
               block_movement = true;
               is_invisible = true;
               setVisible(false);
               if(idleAnimationNumber == 5) {
                   animator->setInterval("special_right");
               }else {
                   animator->setInterval("special_left");
               }
           }
   }
   if(InputManager::instance.isKeyReleased(InputManager::KEY_PRESS_SPACE) && is_selected && !turnOff) {
        setDefault();
   }
}

void Varginha::setDefault() {
    is_invisible = false;
    setVisible(true);
    block_movement = false;
}

void Varginha::draw() {
    INFO("Varginha DRAW");
    animator->draw(getPositionX()-15, getPositionY()-25);
    animator->draw_collider(getPositionX(), getPositionY(), getWidth(), getHeight());
}

void Varginha::verifyTurn() {
    if((timerTurn->elapsed_time()/1000.0) > 0.3 && turnOff) {
      block_movement = false;
      turnOff = false;
    }
}
