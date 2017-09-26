#include "lose_scene.hpp"
#include "button.hpp"

#include <typeinfo>
#include <iostream>
#include <assert.h>
using namespace engine;

LoseScene::LoseScene(int id) : Scene(id){
    selectButton = 1;
    select = new Color(255, 255, 255, 0);
    notSelect = new Color(0, 0, 0, 0);
    soundEffect = new Audio("assets/sounds/SELECT6.wav", "EFFECT", 100);
    backgroundMusic = new Audio("assets/sounds/GAMEOVER.wav", "MUSIC", 50);
    background = new Animation("assets/sprites/lose.png", 1, 4, 0.8);
    background->addAction("lose", 0,3);
    background->setInterval("lose");
}

LoseScene::~LoseScene(){
}

void LoseScene::draw(){
        background->draw_instant(80, 20);

        for(auto gameObject : gameObjectsList) {
                (*gameObject.second).draw();
        }
}

void LoseScene::update(double timeElapsed){
        assert(timeElapsed>0);
        selectAction();

        background->update();

        for(auto gameObject : gameObjectsList) {
                if(typeid(*gameObject.second) == typeid(Button)) {
                        if(gameObject.first == selectButton) {
                                ((Button *)(gameObject.second))->setTextColor(select);
                        }else{
                                ((Button *)(gameObject.second))->setTextColor(notSelect);
                        }
                }

                (*gameObject.second).update(timeElapsed);
        }
}

void LoseScene::load(){
        gameObjectsList.push_back(std::pair<int, GameObject*>(1,new Button("assets/fonts/font.ttf", 700, 500, 500, 500, "Continue", 50)));
        gameObjectsList.push_back(std::pair<int, GameObject*>(2,new Button("assets/fonts/font.ttf", 50, 500, 500, 500, "Menu", 50)));
