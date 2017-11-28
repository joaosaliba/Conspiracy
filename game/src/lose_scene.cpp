#include "lose_scene.hpp"
#include "button.hpp"
#include<assert.h>;
#include <typeinfo>
#include <iostream>

using namespace engine;

LoseScene::LoseScene(int id) : Scene(id){
    selectButton = 1;
    select = new Color(255, 255, 255, 0);// seta a cor para seleção 
    notSelect = new Color(0, 0, 0, 0);// seta a cor quando nao ha seleção
    soundEffect = new Audio("assets/sounds/SELECT6.wav", "EFFECT", 100);// seta o efeito do audio
    backgroundMusic = new Audio("assets/sounds/GAMEOVER.wav", "MUSIC", 50);//seta a musica da cena.
    background = new Animation("assets/sprites/lose.png", 1, 4, 0.8);// seta a animação para a cena.
    assert( background.getCurrentPositionFrame()==0);
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
        Button1 button= new Button("assets/fonts/font.ttf", 700, 500, 500, 500, "Continue", 50)
        assert(button.getText().text== "Continue");   
        gameObjectsList.push_back(std::pair<int, GameObject*>(1,button));
        Button button4 =new Button("assets/fonts/font.ttf", 50, 500, 500, 500, "Menu", 50);
        assert(button.getText().text== "Continue");
        gameObjectsList.push_back(std::pair<int, GameObject*>(2,button4));
        AnimationManager::instance.setBackgroundColor(new Color(255,160,156, 125));
        backgroundMusic->play(0);

}

void enter_function(){
            switch(selectButton) {
                case 1:
                        getSceneManager()->loadScene(getSceneManager()->get_before_scene_id());
                        break;
                case 2:
                        getSceneManager()->loadScene(0);
                        break;
                default:
                        break;
                }

}        
void right_function(){

                                   
         soundEffect->pause();
                soundEffect->play(0);
                selectButton++;
                if(selectButton > 2) {
                        selectButton = 1;
                }
        }
}                                   
void LoseScene::selectAction(){
        if(InputManager::instance.isKeyTriggered(InputManager::KeyPress::KEY_PRESS_LEFT)) {
                soundEffect->pause();
                soundEffect->play(0);
                selectButton--;
                if(selectButton <= 0) {
                        selectButton = 2;
                }
        }
        else if(InputManager::instance.isKeyTriggered(InputManager::KeyPress::KEY_PRESS_RIGHT)) {
        right_function()

        if(InputManager::instance.isKeyTriggered(InputManager::KeyPress::KEY_PRESS_ENTER)) {
           enter_function();        
        }
}

void LoseScene::unload(){
}
