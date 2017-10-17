#include "log.h"
#include "player.hpp"
using namespace engine;
#define int NOTUPDATE=0;
#define const int ETEMER=1;
# define const int BILU=2;
# define  const int VARGINA=3;
#define int TIMESTOPLAY =0;
def type struct position{
  int x,
 int y;
}
#define const  int VOLUMESOUNDBILU =100;
#define const  int VOLUMESOUNDVARGINA=25;
#define const  int VOLUMESOUNDETEMER=75;
#define const Position HEADERPOSITION.x=0;
#define const Position HEADERPOSITION.y=0;
struct  size{
   int rows;
   int columns;
}
#define const int VARGINATIME =0.5;
#define size VARGINADIMENSIONS.rows=1;
#define size  VARGINADIMENSIONS.columns=1;
Player::Player(std::pair<int, int> biluPosition, std::pair<int, int> etemerPosition,
               std::pair<int,int> varginhaPosition, int paperQuantity, int stageNumber){

        exclamationAnimation = new Animation("assets/sprites/exclamation2.png",VARGINADIMENSIONS.rows, VARGINADIMENSIONS.columns,  VARGINATIME );

        bilu = new Bilu(biluPosition.first, biluPosition.second);
        varginha = new Varginha(varginhaPosition.first, varginhaPosition.second);
        etemer = new Etemer(etemerPosition.first, etemerPosition.second);
        header = new Header(HEADERPOSITION.x, HEADERPOSITION.y paperQuantity, stageNumber);

        selectedAlien = ETEMER;

        etemer->update(NOTUPDATE);
        bilu->update(NOTUPDATE);
        varginha->update(NOTUPDATE);
        header->update(NOTUPDATE);

        bilu->setAlienDeselect();
        varginha->setAlienDeselect();
        etemer->setAlienSelected();

        bilu_sound_effect = new 

Audio("assets/sounds/TROCABILU.wav", "EFFECT", VOLUMESOUNDBILU);
        varginha_sound_effect = new Audio("assets/sounds/TROCAVARGINHA.wav", "EFFECT", VOLUMESOUNDVARGINA);
        etemer_sound_effect = new Audio("assets/sounds/TROCATEMER.wav", "EFFECT", VOLUMESOUNDETEMER);
}

Player::~Player(){
}

void Player::update(double timeElapsed){
        int beforeAlien = selectedAlien;

        if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_ONE)) {
                selectedAlien = ETEMER;
        } else if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_TWO)) {
                selectedAlien = BILU;
        } else if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_THREE)) {
                selectedAlien = VARGINA;
                ((Varginha *)(varginha))->setDefault();
        }

        if(beforeAlien != selectedAlien) {
                header->setAlienSelect(selectedAlien);
                etemer->setAlienDeselect();
                bilu->setAlienDeselect();
                varginha->setAlienDeselect();

                waitAnimation(beforeAlien);
                switch(selectedAlien) {
                case ETEMER: etemer->setAlienSelected(); etemer_sound_effect->play(TIMESTOPLAY); break;
                case BILU: bilu->setAlienSelected(); bilu_sound_effect->play(TIMESTOPLAY); break;
                case VARGINA: varginha->setAlienSelected(); varginha_sound_effect->play(TIMESTOPLAY);break;
                }
        }

        exclamationAnimation->update();

        etemer->update(timeElapsed);
        bilu->update(timeElapsed);
        varginha->update(timeElapsed);
        header->update(timeElapsed);
}

void Player::draw(){
        INFO("PLAYER DRAW");
        bilu->draw();
        varginha->draw();
        etemer->draw();
        header->draw();
}

void Player::updatePaperQuantity(int newValue){
    header->updatePaperQuantity(newValue);
}

void Player::waitAnimation(int beforeAlien){
        if(beforeAlien==ETEMER) {
                idleAnimation(etemer);
                etemer->update(NOTUPDATE);
        }else if(beforeAlien==BILU) {
                idleAnimation(bilu);
                bilu->update(NOTUPDATE);
        } else if(beforeAlien== VARGINA) {
                idleAnimation(varginha);
                varginha->update(NOTUPDATE);
        }
}

void Player::idleAnimation(Alien * alien){
        if(alien->getAnimation()->getInterval().first == "right") {
                alien->getAnimation()->setInterval("idle_right");
        } else if(alien->getAnimation()->getInterval().first == "left") {
                alien->getAnimation()->setInterval("idle_left");
        } else if(alien->getAnimation()->getInterval().first == "up") {
                alien->getAnimation()->setInterval("idle_up");
        }else if(alien->getAnimation()->getInterval().first == "down") {
                alien->getAnimation()->setInterval("idle_down");
        }
}
bool Player::isDead(){
        if(!varginha->isEnabled()) {
                exclamationAnimation->draw(varginha->getPositionX()-5, varginha->getPositionY()-40);
                return true;
        }else if(!bilu->isEnabled()) {
            exclamationAnimation->draw(bilu->getPositionX(), bilu->getPositionY()-40);
                return true;
        }else if(!etemer->isEnabled()) {
            exclamationAnimation->draw(etemer->getPositionX(), etemer->getPositionY()-40);
                return true;
        }
        return false;
}

Alien * Player::getBilu(){
        return bilu;
}

Alien * Player::getVarginha(){
        return varginha;
}

Alien * Player::getEtemer(){
        return etemer;
}
