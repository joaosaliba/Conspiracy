/**class to object of player, where you can find some objects, files, variables and meths
 *used to the samen.
 */

#include "log.h"
#include "player.hpp"
using namespace engine;

Player::Player(std::pair<int, int> bilu_position, std::pair<int, int> etemer_position,
               std::pair<int,int> varginha_position, int paper_quantity, int stage_number) {

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

    bilu->set_alien_deselect();
    varginha->set_alien_deselect();
    etemer->set_alien_selected();

    bilu_sound_effect = new Audio("assets/sounds/TROCABILU.wav", "EFFECT", 100);
    varginha_sound_effect = new Audio("assets/sounds/TROCAVARGINHA.wav", "EFFECT", 25);
    etemer_sound_effect = new Audio("assets/sounds/TROCATEMER.wav", "EFFECT", 75);
}

Player::~Player() {
}

void Player::update(double time_elapsed) {
    int before_alien = selected_alien;

    if(InputManager::instance.is_key_pressed(InputManager::KeyPress::KEY_PRESS_ONE)) {
        selected_alien = 1;
    } else if(InputManager::instance.is_key_pressed(InputManager::KeyPress::KEY_PRESS_TWO)) {
        selected_alien = 2;
    } else if(InputManager::instance.is_key_pressed(InputManager::KeyPress::KEY_PRESS_THREE)) {
        selected_alien = 3;
        ((Varginha *)(varginha))->set_default();
    }

    if(before_alien != selected_alien) {
        header->set_alien_select(selected_alien);
        etemer->set_alien_deselect();
        bilu->set_alien_deselect();
        varginha->set_alien_deselect();

        wait_animation(before_alien);
        switch(selected_alien) {
        case 1: etemer->set_alien_selected(); etemer_sound_effect->play(0); break;
        case 2: bilu->set_alien_selected(); bilu_sound_effect->play(0); break;
        case 3: varginha->set_alien_selected(); varginha_sound_effect->play(0);break;
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

void Player::update_paper_quantity(int new_value){
    header->update_paper_quantity(new_value);
}

void Player::wait_animation(int before_alien){
    if(before_alien==1) {
        idle_animation(etemer);
        etemer->update(0);
    }else if(before_alien==2) {
        idle_animation(bilu);
        bilu->update(0);
    } else if(before_alien==3) {
        idle_animation(varginha);
        varginha->update(0);
    }
}

void Player::idle_animation(Alien * alien){
    if(alien->get_animation()->get_interval().first == "right") {
        alien->get_animation()->set_interval("idle_right");
    } else if(alien->get_animation()->get_interval().first == "left") {
        alien->get_animation()->set_interval("idle_left");
    } else if(alien->get_animation()->get_interval().first == "up") {
        alien->get_animation()->set_interval("idle_up");
    }else if(alien->get_animation()->get_interval().first == "down") {
        alien->get_animation()->set_interval("idle_down");
    }
}
bool Player::is_dead(){
    if(!varginha->is_enabled()) {
        exclamation_animation->draw(varginha->get_position_x()-5, varginha->get_position_y()-40);
        return true;
    }else if(!bilu->is_enabled()) {
        exclamation_animation->draw(bilu->get_position_x(), bilu->get_position_y()-40);
            return true;
    }else if(!etemer->is_enabled()) {
        exclamation_animation->draw(etemer->get_position_x(), etemer->get_position_y()-40);
            return true;
    }
    return false;
}

Alien * Player::get_bilu() {
    return bilu;
}

Alien * Player::get_varginha() {
    return varginha;
}

Alien * Player::get_etemer() {
    return etemer;
}
