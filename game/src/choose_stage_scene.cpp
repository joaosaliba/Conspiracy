/**
 * @file choose_stage_scene.cpp
 * @brief class to object of choose_stage_scene, where you can find some values, files, others objects
 * and methods to the same.
 * @copyright  GNU GENERAL PUBLIC LICENSE.
 */

#include "choose_stage_scene.hpp"
#include "choice.hpp"

#include <typeinfo>
#include <iostream>

using namespace engine;

#define MAX_CHOICE 5
#define MIN_CHOICE 0


ChooseStageScene::ChooseStageScene(int id) : Scene(id){
    select_button = 1;

    select = new Color(255, 255, 255, 0);
    not_select = new Color(0, 0, 0, 0);

    background = new Sprite("assets/sprites/selecao_fases.png");
    sound_effect = new Audio("assets/sounds/SELECT6.wav", "EFFECT", 100);
}

/**
  *    @brief ChooseStageScene object destructor.
 */

ChooseStageScene::~ChooseStageScene(){

}

void ChooseStageScene::draw(){
    background->draw(80, 20);

    for(auto gameObject : game_objects_list) {
        (*gameObject.second).draw();
    }
}

void ChooseStageScene::update(double time_elapsed){
    select_action_1();
    select_action_2();
    select_action_3();

    for(auto gameObject : game_objects_list) {
        if(typeid(*gameObject.second) == typeid(Choice)) {
            if(gameObject.first == select_button) {
                ((Choice *)(gameObject.second))->set_text_color(select);
                ((Choice *)(gameObject.second))->set_chosen(true);
            }else {
                ((Choice *)(gameObject.second))->set_text_color(notSelect);
                ((Choice *)(gameObject.second))->set_chosen(false);
            }

            if(gameObject.first <= SaveManager::instance.get_stage_number_unlock()) {
                 ((Choice *)(gameObject.second))->set_unlock(true);
            }
         }

         if(!gameObject.first) {
             if(gameObject.first == select_button) {
                 ((Button *)(gameObject.second))->set_text_color(select);
             }else {
                 ((Button *)(gameObject.second))->set_text_color(notSelect);
             }
          }

    (*gameObject.second).update(time_elapsed);
    }
}

void ChooseStageScene::load(){
    game_objects_list.push_back(std::pair<int, GameObject*>(0,new Button("assets/fonts/font.ttf", 20, 20, 100, 100, "Voltar", 30)));
    game_objects_list.push_back(std::pair<int, GameObject*>(1,new Choice("assets/sprites/choices/stage_1.png", 50, 100, 200, 150, "Fase 1", 40)));
    game_objects_list.push_back(std::pair<int, GameObject*>(2,new Choice("assets/sprites/choices/stage_2.png", 720, 100, 200, 150, "Fase 2", 40)));
    game_objects_list.push_back(std::pair<int, GameObject*>(3,new Choice("assets/sprites/choices/stage_3.png", 50, 400, 200, 150, "Fase 3", 40)));
    game_objects_list.push_back(std::pair<int, GameObject*>(4,new Choice("assets/sprites/choices/stage_4.png", 720, 400, 200, 150, "Fase 4", 40)));
    game_objects_list.push_back(std::pair<int, GameObject*>(5,new Choice("assets/sprites/choices/stage_5.png", 400, 250, 200, 150, "Fase 5", 40)));
    AnimationManager::instance.set_background_color(new Color(255,225,142, 125));
}

void ChooseStageScene::select_action_1() {
    if(InputManager::instance.is_key_triggered(InputManager::KeyPress::KEY_PRESS_LEFT)) {
        sound_effect->pause();
        sound_effect->play(0);
        select_button--;
        if(select_button < MIN_CHOICE) {
            select_button = MAX_CHOICE;
        }
    }else {
      //nothing to do
    }
}

void ChooseStageScene::select_action_2() {
    if(InputManager::instance.is_key_triggered(InputManager::KeyPress::KEY_PRESS_RIGHT)) {
        sound_effect->pause();
        sound_effect->play(0);
        select_button++;
        if(select_button > MAX_CHOICE) {
            select_button = MIN_CHOICE;
        }
    }else {
      //nothing to do
    }

}

void ChooseStageScene::select_action_3(){
    
    if(InputManager::instance.is_key_triggered(InputManager::KeyPress::KEY_PRESS_ENTER)) {
        switch(select_button) {
        case 0:
                getSceneManager()->load_scene(0);
                break;
        case 1:
                if(select_button <= SaveManager::instance.get_stage_number_unlock()) {
                    getSceneManager()->load_scene(22);
                }
                break;
        case 2:
                if(select_button <= SaveManager::instance.get_stage_number_unlock()) {
                    getSceneManager()->load_scene(2);
                }
                break;
        case 3:
                if(select_button <= SaveManager::instance.get_stage_number_unlock()) {
                    getSceneManager()->load_scene(3);
                }
                break;
        case 4:
                if(select_button <= SaveManager::instance.get_stage_number_unlock()) {
                    getSceneManager()->load_scene(4);
                }
                break;
        case 5:
                if(select_button <= SaveManager::instance.get_stage_number_unlock()) {
                    getSceneManager()->load_scene(5);
                }
                break;
        default:
                //nothing to do
                break;
        }

    }

}

void ChooseStageScene::unload() {
}
