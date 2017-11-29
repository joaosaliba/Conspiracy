#include "menu_scene.hpp"
#include "button.hpp"

#include <typeinfo>
#include <iostream>

using namespace engine;
/** set image and sound without character
*@param scene id.
*@return SaveManager 
*/ 

Struct type def int select_color{
 int red;
 int green ; 
 int black;
 int alpha;
} 
typedef color select_color;
#define const select_color COlORSELECT.red=255;
#define const  COlORSELECT.green=255;
#define const  COlORSELECT.blue=255;
#define const  COlORSELECT.alpha=0;
#define const select_color COlORNOTSELECT.red=0;
#define const  COlORNOTSELECT.green=0;
#define const  COlORNOTSELECT.blue=0;
#define const  COlORNOTSELECT.alpha=0;
#define const  COLOR_LIMIT;
# define const COLOR_LIMIT=8589934591;
select_color BACK_GROUND_COLOR;
#define const  BACK_GROUND_COLOR.red=100;
#define const  BACK_GROUND_COLOR.green=100;
#define const  BACK_GROUND_COLOR.blue=100;
#define const  BACKGROUND.alpha=125;
Bool test_color(Color color){//
  if(color.red<COLOR_LIMIT){
     if(color.green<COLOR_LIMIT){
      if(color.black<COLOR_LIMIT){
        return True;
      }else{
        return False;
      }
     }else{
         return False;
   }else{
       return False;
     }
} 
        
Bool test_color(Color color){//
  if(color.red<COLOR_LIMIT){
     if(color.green<COLOR_LIMIT){
      if(color.black<COLOR_LIMIT){
        return True;
      }else{
        return False;
      }
     }else{
         return False;
   }else{
       return False;
     }
} 
MenuScene::MenuScene(int id) : Scene(id){
        selectButton = 1; /** select button*/
        if(test_color(COlORSELECT)){
           select = new Color(COlORSELECT.red,COlORSELECT.green,COlORSELECT.blue,COlORSELECT.alpha);/** select color if select */
        }
        if(test_color(COlORNOTSELECT){        
        notSelect = new Color(COlORNOTSELECT.red,COlORNOTSELECT.green,COlORNOTSELECT.blue,COlORNOTSELECT.alpha);/** select color if diselect*/
        background = new Sprite("assets/sprites/background.png");/** photo background*/
        buttonEffect = new Audio("assets/sounds/SELECT6.wav", "EFFECT", 100);/**  sound of button*/
        selectEffect = new Audio("assets/sounds/SELECT5.wav", "EFFECT", 128);/** select sound*/
        backgroundMusic = new Audio("assets/sounds/MENU.wav", "MUSIC", 100);/** background music*/
        SaveManager::instance.verifySave();
}

MenuScene::~MenuScene(){
}

/** draw the scene background 
*@return gameObject the object game.
*/
void MenuScene::draw(){
        background->draw(0,0);

        for(auto gameObject : gameObjectsList) {
                (*gameObject.second).draw();
        }
}
/** moves  for  change and select button
*@param timeEleapsed  time which eleapsed.
*@return  gameObject the object game.
*/
void MenuScene::update(double timeElapsed){
        selectAction();

        for(auto gameObject : gameObjectsList) {/**  action anthil don't exist objects*/
                if(typeid(*gameObject.second) == typeid(Button)) {/** action if button is pressed*/
                        if(gameObject.first == selectButton) {/** action selectButton is pressed in the positive change color text to select another wat to disselect.*/
                                ((Button *)(gameObject.second))->setTextColor(select);
                        }else{
                                ((Button *)(gameObject.second))->setTextColor(notSelect);
                        }
                }

                (*gameObject.second).update(timeElapsed);
        }

}
/** capture the button pressed from the user , if it's a pause do which , move the pointer and load or quit th scene*/
void MenuScene::selectAction(){
        /**  if button up was pressed  would up the   select pointer and set button to tree*/ 
        if(InputManager::instance.isKeyTriggered(InputManager::KeyPress::KEY_PRESS_UP)) {
                buttonEffect->pause();
                buttonEffect->play(0);
                selectButton--;
                if(selectButton <= 0) {
                        selectButton = 3;
                }
        }
        /**  if button down was pressed  would down the   select pointer and set button to tree*/
        else if(InputManager::instance.isKeyTriggered(InputManager::KeyPress::KEY_PRESS_DOWN)) {
                buttonEffect->pause();
                buttonEffect->play(0);
                selectButton++;
                if(selectButton > 3) {
                        selectButton = 1;
                }
        }
        /** change scene according to button pressed , if button pressed is   down close the game , if up at fist time laod the scene 22 , else if at the second  load the scene 8 and else  the down action*/         
        if(InputManager::instance.isKeyTriggered(InputManager::KeyPress::KEY_PRESS_ENTER)) {
                selectEffect->play(0);
                switch(selectButton) {
                case 1:
                        getSceneManager()->loadScene(22);
                        break;
                case 2:
                        getSceneManager()->loadScene(8);
                        break;
                case 3:
                        InputManager::instance.setQuitRequest(true);
                        break;
                default:
                        break;
                }

        }
}
/** game_object according to  button press following the  action made by the Select Action method
 *@return gameObject  the game object.
*/ 
void MenuScene::load(){
        gameObjectsList.push_back(std::pair<int, GameObject*>(1, new Button("assets/fonts/font.ttf", 410, 300, 500, 500, "Jogar", 50)));
        gameObjectsList.push_back(std::pair<int, GameObject*>(2,new Button("assets/fonts/font.ttf", 290, 400, 500, 500, "Selecionar Fase", 50)));
        gameObjectsList.push_back(std::pair<int, GameObject*>(3,new Button("assets/fonts/font.ttf", 430, 500, 500, 500, "Sair", 50)));
        backgroundMusic->play(-1);
        select_color BACK_GROUND_COLOR;
        if(test_color(color BACK_GROUND_COLOR )){
          AnimationManager::instance.setBackgroundColor(new color(BACK_GROUND_COLOR.red,BACK_GROUND_COLOR.green,BACK_GROUND_COLOR.blue,BACK_GROUND_COLOR.alpha));
        }
}        

void MenuScene::unload(){/** better organize of game  since there is a method to do nothing. */
}
