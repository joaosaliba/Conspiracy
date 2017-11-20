/**
 * @file player.cpp
 * @brief class to object of player, where you can find some values, files,
 * others objects used in this class and methods to the same.
 * @copyright  GNU GENERAL PUBLIC LICENSE.
 */

#include "log.h"
#include "player.hpp"
#include <assert.h>

using namespace engine;

Player::Player(std::pair<int, int> bilu_position, std::pair<int, int> etemer_position,
               std::pair<int,int> varginha_position, int paper_quantity, int stage_number) {

    assert(paper_quantity > 0 && paper_quantity < 100000);
    assert(stage_number > -10000 && stage_number < 100000);

    exclamation_animation = new Animation("assets/sprites/exclamation2.png",1, 1, 0.5);

    bilu = new Bilu(bilu_position.first, bilu_position.second);
    varginha = new Varginha(varginha_position.first, varginha_position.second);
    etemer = new Etemer(etemer_position.first, etemer_position.second);
    header = new Header(0,0, paper_quantity, stage_number);

    selected_alien = 1;

    etemer->update(0);
    bilu->update(0);
    varginha->update(0);
    header->update(0);

    bilu->setAlienDeselect();
    varginha->setAlienDeselect();
    etemer->setAlienSelected();

    bilu_sound_effect = new Audio("assets/sounds/TROCABILU.wav", "EFFECT", 100);
    varginha_sound_effect = new Audio("assets/sounds/TROCAVARGINHA.wav", "EFFECT", 25);
    etemer_sound_effect = new Audio("assets/sounds/TROCATEMER.wav", "EFFECT", 75);
}

Player::~Player() {
}

void Player::update(double time_elapsed) {
//verifyyyyyy

    assert(time_elapsed > 0 && time_elapsed < 20000000);

    int before_alien = selected_alien;

    if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_ONE)) {
        selected_alien = 1;
    } else if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_TWO)) {
        selected_alien = 2;
    } else if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_THREE)) {
        selected_alien = 3;
        ((Varginha *)(varginha))->setDefault();
    }

    if(before_alien != selected_alien) {
        header->setAlienSelect(selected_alien);
        etemer->setAlienDeselect();
        bilu->setAlienDeselect();
        varginha->setAlienDeselect();

        waitAnimation(before_alien);
        switch(selected_alien) {
        case 1: etemer->setAlienSelected(); etemer_sound_effect->play(0); break;
        case 2: bilu->setAlienSelected(); bilu_sound_effect->play(0); break;
        case 3: varginha->setAlienSelected(); varginha_sound_effect->play(0);break;
        }
    }

    exclamation_animation->update();

    etemer->update(time_elapsed);
    bilu->update(time_elapsed);
    varginha->update(time_elapsed);
    header->update(time_elapsed);
}

void Player::draw() {
    INFO("PLAYER DRAW");
    bilu->draw();
    varginha->draw();
    etemer->draw();
    header->draw();
}

void Player::updatePaperQuantity(int new_value){
    header->updatePaperQuantity(new_value);
}

void Player::waitAnimation(int before_alien){
    if(before_alien==1) {
        idleAnimation(etemer);
        etemer->update(0);
    }else if(before_alien==2) {
        idleAnimation(bilu);
        bilu->update(0);
    } else if(before_alien==3) {
        idleAnimation(varginha);
        varginha->update(0);
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
        exclamation_animation->draw(varginha->getPositionX()-5, varginha->getPositionY()-40);
        return true;
    }else if(!bilu->isEnabled()) {
        exclamation_animation->draw(bilu->getPositionX(), bilu->getPositionY()-40);
            return true;
    }else if(!etemer->isEnabled()) {
        exclamation_animation->draw(etemer->getPositionX(), etemer->getPositionY()-40);
            return true;
    }
    return false;
}

Alien * Player::getBilu() {
    return bilu;
}

Alien * Player::getVarginha() {
    return varginha;
}

Alien * Player::getEtemer() {
    return etemer;
}
