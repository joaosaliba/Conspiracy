/**
 * @file finish_scene.cpp
 * @brief class to object of finish_scene, where you can find some values, files,
 * others objects used in this class and methods to the same.
 * @copyright  GNU GENERAL PUBLIC LICENSE.
 */

#include "finish_scene.hpp"
#include "button.hpp"

#include <typeinfo>
#include <iostream>

using namespace engine;



FinishScene::FinishScene(int id) : Scene(id) {
    INFO("finish_scene constructor init");

    select_button = 1;

    DEBUG("the buttom selected: "+select_button);

    select = new Color(255, 255, 255, 0);
    not_select = new Color(0, 0, 0, 0);
    sound_effect = new Audio("assets/sounds/SELECT6.wav", "EFFECT", 100);
    background_sound = new Audio("assets/sounds/FINAL.wav", "MUSIC", 50);
    background = new Animation("assets/sprites/finish.png", 1, 1, 0.8);
    background->addAction("finish", 0,0);
    background->setInterval("finish");

    INFO("finish_scene constructor ok");
}

/**
  *    @brief FinishScene object destructor.
 */

FinishScene::~FinishScene() {
}

/**
* @brief Method draw
* <p>This method call the function draw_instant, that draw the background level using two colors</p>
* @return void
*/

void FinishScene::draw() {
    background->draw_instant(80, 20);

    for(auto gameObject : game_objects_list) {
        (*gameObject.second).draw();
    }
}

/**
* @brief Method update
* <p>This method use the time_elapsed to know when have to update the interface level,
*  and use teh array to know what have to show to user.</p>
* @param double-time_elapsed
* @return void
*/

void FinishScene::update(double time_elapsed) {
    DEBUG("time_elapsed receive"+time_elapsed);

    selectAction();

    background->update();

    for(auto gameObject : game_objects_list) {
        if(typeid(*gameObject.second) == typeid(Button)) {
            if(gameObject.first == select_button) {
                ((Button *)(gameObject.second))->setTextColor(select);
            }else {
                ((Button *)(gameObject.second))->setTextColor(not_select);
                 }
        }else {
            INFO("the wont update the background with the new colors");
        }

    (*gameObject.second).update(time_elapsed);
    }
}

/**
* Method load
* <p>This method load the pattern style applied in the level.</p>
* @return void
*/

void FinishScene::load() {
    game_objects_list.push_back(std::pair<int, GameObject*>(1,new Button("assets/fonts/font.ttf", 420, 500, 500, 500, "Menu", 50)));
    AnimationManager::instance.setBackgroundColor(new Color(158,228,159, 125));
    background_sound->play(-1);

}

/**
* Método select_action
* <p>This method create cases to load the next scene of the game.</p>
* @return void
*/

void FinishScene::selectAction() {

    if(InputManager::instance.isKeyTriggered(InputManager::KeyPress::KEY_PRESS_ENTER)) {
        switch(select_button) {
        case 1:
            getSceneManager()->loadScene(0);
            INFO("selected the action one and load the respective scene");
            break;
        default:
            break;
        }

    }
}

void FinishScene::unload() {
}
