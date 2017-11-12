#include "log.h"
#include "player.hpp"
using namespace engine;

Player::Player(std::pair<int, int> biluPosition, std::pair<int, int> etemerPosition,
               std::pair<int,int> varginhaPosition, int paperQuantity, int stageNumber){

        exclamationAnimation = new Animation("assets/sprites/exclamation2.png",1, 1, 0.5);

        bilu = new Bilu(biluPosition.first, biluPosition.second);
        varginha = new Varginha(varginhaPosition.first, varginhaPosition.second);
        etemer = new Etemer(etemerPosition.first, etemerPosition.second);
        header = new Header(0,0, paperQuantity, stageNumber);

        selectedAlien = 1;

        etemer->update(0);
        bilu->update(0);
        varginha->update(0);
        header->update(0);

        bilu->set_alien_deselect();
        varginha->set_alien_deselect();
        etemer->set_alien_selected();

        bilu_sound_effect = new Audio("assets/sounds/TROCABILU.wav", "EFFECT", 100);
        varginha_sound_effect = new Audio("assets/sounds/TROCAVARGINHA.wav", "EFFECT", 25);
        etemer_sound_effect = new Audio("assets/sounds/TROCATEMER.wav", "EFFECT", 75);
}

Player::~Player(){
}

void Player::update(double timeElapsed){
        int beforeAlien = selectedAlien;

        if(InputManager::instance.is_key_pressed(InputManager::KeyPress::KEY_PRESS_ONE)) {
                selectedAlien = 1;
        } else if(InputManager::instance.is_key_pressed(InputManager::KeyPress::KEY_PRESS_TWO)) {
                selectedAlien = 2;
        } else if(InputManager::instance.is_key_pressed(InputManager::KeyPress::KEY_PRESS_THREE)) {
                selectedAlien = 3;
                ((Varginha *)(varginha))->set_default();
        }

        if(beforeAlien != selectedAlien) {
                header->setAlienSelect(selectedAlien);
                etemer->set_alien_deselect();
                bilu->set_alien_deselect();
                varginha->set_alien_deselect();

                waitAnimation(beforeAlien);
                switch(selectedAlien) {
                case 1: etemer->set_alien_selected(); etemer_sound_effect->play(0); break;
                case 2: bilu->set_alien_selected(); bilu_sound_effect->play(0); break;
                case 3: varginha->set_alien_selected(); varginha_sound_effect->play(0);break;
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
        if(beforeAlien==1) {
                idleAnimation(etemer);
                etemer->update(0);
        }else if(beforeAlien==2) {
                idleAnimation(bilu);
                bilu->update(0);
        } else if(beforeAlien==3) {
                idleAnimation(varginha);
                varginha->update(0);
        }
}

void Player::idleAnimation(Alien * alien){
        if(alien->get_animation()->getInterval().first == "right") {
                alien->get_animation()->set_interval("idle_right");
        } else if(alien->get_animation()->getInterval().first == "left") {
                alien->get_animation()->set_interval("idle_left");
        } else if(alien->get_animation()->getInterval().first == "up") {
                alien->get_animation()->set_interval("idle_up");
        }else if(alien->get_animation()->getInterval().first == "down") {
                alien->get_animation()->set_interval("idle_down");
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
