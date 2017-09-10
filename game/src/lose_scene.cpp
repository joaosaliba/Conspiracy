include "lose_scene.hpp"
#include "button.hpp"

#include <typeinfo>
#include <iostream>
/* set lose scene.
 *@return background 
*/ 

using namespace engine;

LoseScene::LoseScene(int id) : Scene(id){
    selectButton = 1;/** select button*/
    select = new Color(255, 255, 255, 0);/** change color*/
    notSelect = new Color(0, 0, 0, 0);/** color of notselect*/
    soundEffect = new Audio("assets/sounds/SELECT6.wav", "EFFECT", 100);/** set the sound */
    backgroundMusic = new Audio("assets/sounds/GAMEOVER.wav", "MUSIC", 50);/** set the backgroud music*/
    background = new Animation("assets/sprites/lose.png", 1, 4, 0.8);/** set position */
    background->addAction("lose", 0,3);/** adction of scene in  sort action*/
    background->setInterval("lose");/** define the interval ind display*/
}

LoseScene::~LoseScene(){
}
/* drawing  lose scene.
 *@return game object 
*/ 

void LoseScene::draw(){
        background->draw_instant(80, 20);

        for(auto gameObject : gameObjectsList) {
                (*gameObject.second).draw();
        }
}
/* update  gameObject.
 *@return gameObject.
*/ 
void LoseScene::update(double timeElapsed){
        selectAction();

        background->update();

        for(auto gameObject : gameObjectsList) {
        /** if button is diferent will  make another clause*/
                if(typeid(*gameObject.second) == typeid(Button)) {  
                /** if user select an diferrent oibject   will  change  to select color if don't set cpçpr tp disselect color*/  
                        if(gameObject.first == selectButton) {
                                ((Button *)(gameObject.second))->setTextColor(select);
                        }else{
                                ((Button *)(gameObject.second))->setTextColor(notSelect);
                        }
                }

                (*gameObject.second).update(timeElapsed);
        }
}
/* lose the scene.
 *@param gameObject.
*/ 

void LoseScene::load(){
        gameObjectsList.push_back(std::pair<int, GameObject*>(1,new Button("assets/fonts/font.ttf", 700, 500, 500, 500, "Continue", 50)));
        gameObjectsList.push_back(std::pair<int, GameObject*>(2,new Button("assets/fonts/font.ttf", 50, 500, 500, 500, "Menu", 50)));
        AnimationManager::instance.setBackgroundColor(new Color(255,160,156, 125));
        backgroundMusic->play(0);

}
/* change sound effect and select button  or scene acording to the pressed  button.
 *@param  InputManager.
*/ 
void LoseScene::selectAction(){
        /** change the sound effect and button if user press left , if don't move to another     
        * clause
        */  
        if(InputManager::instance.isKeyTriggered(InputManager::KeyPress::KEY_PRESS_LEFT)) {
                soundEffect->pause();
                soundEffect->play(0);
                selectButton--;
                if(selectButton <= 0) {
                        selectButton = 2;
                }
        }
        /** change the sound effect and button if user press right*/  
        else if(InputManager::instance.isKeyTriggered(InputManager::KeyPress::KEY_PRESS_RIGHT)) {
                soundEffect->pause();
                soundEffect->play(0);
                selectButton++;
                if(selectButton > 2) {
                        selectButton = 1;
                }
        }
        /**  if enter and another button is pressed together  go to next scene or to previous */     
        if(InputManager::instance.isKeyTriggered(InputManager::KeyPress::KEY_PRESS_ENTER)) {
                switch(selectButton) {
                case 1:
                        getSceneManager()->loadScene(getSceneManager()->getBeforeSceneId());
                        break;
                case 2:
                        getSceneManager()->loadScene(0);
                        break;
                default:
                        break;
                }

        }
}

void LoseScene::unload(){
}
