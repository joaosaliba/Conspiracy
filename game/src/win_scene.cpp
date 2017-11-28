#include "win_scene.hpp"
#include "button.hpp"

#include <typeinfo>
#include <iostream>
# define  type def struct SIZE{
   ROWS
  COLUMNS
}
# define  type def struct Color{
  int  green;
  int red;
  int blue;
  double alpha;
  COLUMNS
}
#define type  def struct position{
     int x;
     int y;
}3
#define const  position DRAW.x=80;
#define const position DRAW.y=20;
#define const color SELECTCOLOR;
#define color SELECTCOLOR.red=255;
#define color SELECTCOLOR.green=255;
#define color SELECTCOLOR.blue=255;
#define color SELECTCOLOR.alpha=0.0;
#define const color SELECTCOLOR;
# color NOTSELECTCOLOR.red=0;
#define color NOTSELECTCOLOR.green=0;
#define color NOTSELECTCOLOR.blue=0;
#define color NOTSELECTCOLOR.alpha=0.0;
#define const site ANIMATION;
#define const ANIMATION.ROWS=1;
#define const ANIMATION.COLUMNS=5;
#define const int NOTUPDATE=0;
# define color ANIMATION.red=158;
# define color ANIMATION.green=228;    
# define color ANIMATION.red=158;
# define color ANIMATION.alpha=125.0;
#define type def struct SIZEOBJECT{
    int WiTDTH;
    int HEIGH ;
}
#define type def struct POSITION{
  Int BEGIN;
 Int LAST;
}
#define const SIZEOBJECT SIZECONTINUE.WITDH=700;
#define const SIZEOBJECT  SIZECONTINUE.HEIGH=500;
#define const POSITION POSITIONCONTINUE.BEGIN=500;
#define const POSITION POSITIONCONTINUE.LAST=500;

#define const SIZEOBJECT SIZEMENU.WITDH=50;
#define const SIZEOBJECT  SIZEMENU.HEIGH=500;
#define const POSITION POSITIONMENU.BEGIN=500;
#define const POSITION POSITIONMENU.LAST=500;
SIZEMENU,POSITIONMENU
using namespace engine;


WinScene::WinScene(int id) : Scene(id){
    selectButton = 1;
    select = new Color( SELECTCOLOR);
    notSelect = new Color(NOTSELECTCOLOR);
    soundEffect = new Audio("assets/sounds/SELECT6.wav", "EFFECT",100);
    background = new Animation("assets/sprites/win.png", ANIMATION, ANIMATIONTIME);
    background->addAction("win", 0, 4);
    assert(std::get<animator->list_actions[beignEdited][1]>==NOTUPDATE);
    background->setInterval("win");
    assert(background->interval.first==win);
    
}

WinScene::~WinScene(){
}


void WinScene::draw(){
        background->draw_instant(DRAW);
        for(auto gameObject : gameObjectsList) {// controla o desenho da cena na tela. 
                (*gameObject.second).draw();
        }
}


void WinScene::update(double timeElapsed){
        selectAction();

        background->update();

        for(auto gameObject : gameObjectsList) {
                if(typeid(*gameObject.second) == typeid(Button)) {
                        if(gameObject.first == selectButton) {
                                ((Button *)(gameObject.second))->setTextColor(select);
                        }else{
                                ((Button *)(gameObject.second))->setTextColor(notSelect);
                        }else{
                        //do nothing
                }

                (*gameObject.second).update(timeElapsed);
        }
}

void WinScene::load(){
        Button button1 =new Button("assets/fonts/font.ttf", SIZECONTINUE,POSITIONCONTINUE, "Continue", 50)    
        gameObjectsList.push_back(std::pair<int,button1, GameObject*>(1,));
        assert(get<gameObjectsList.back.[1]==1>);
        Button button2=new Button("assets/fonts/font.ttf",SIZEMENU,POSITIONMENU, "Menu", 50) 
        gameObjectsList.push_back(std::pair<int,button2, GameObject*>(2,));
        assert(get<gameObjectsList.back.[1]==2>);
        AnimationManager::instance.setBackgroundColor(new Color(ANIMATION ));

}
  
void load_and_get_before_scene(){  
    if(getSceneManager()->get_before_scene_id() == 1){
               getSceneManager()->loadScene(25);
    }else if(getSceneManager()->get_before_scene_id() == 2){
               getSceneManager()->loadScene(23);
    }else{
       getSceneManager()->loadScene(getSceneManager()->get_before_scene_id()+1);
    }
 }
void  EnterSelect ()  {
                switch(selectButton) {
                case 1:
                        load_and_get_before_scene();                        
                        break;
                case 2:
                        getSceneManager()->loadScene(0);
                        break;
                default:
                        break;
                }

        }
}
void RightorLeft(){
  if(InputManager::instance.isKeyTriggered(InputManager::KeyPress::KEY_PRESS_RIGHT)) {
                selectButton++;
                if(selectButton > 2) {
                        selectButton = 1;
                }
        }else {
 if(InputManager::instance.isKeyTriggered(InputManager::KeyPress::KEY_PRESS_LEFT)) {
                selectButton--;
                if(selectButton <= 0) {
                        selectButton = 2;
                }
        }
void WinScene::unload(){
}
