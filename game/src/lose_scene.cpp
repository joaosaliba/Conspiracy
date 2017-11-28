#include "lose_scene.hpp"
#include "button.hpp"
#define int  NOTSELECTEDCOLOR* ;
#define int  SELECTEDCOLOR*;
#define cons int  SOUNDEFFECT=100;
#define const int BACKGROUNMUSIC=50;
#define type def struct CORDENATES{
  Int X;
 Int Y;
}
#define type def struct POSITION{
  Int BEGIN;
 Int LAST;
}
POSITION.BEGIN= 0;
POSITION.LAST=3;
# define  type def struct SIZE{
   ROWS
  COLUMNS
}
#define type def struct SIZEOBJECT{
    int WiTDTH;
    int HEIGH ;
}
#define const  COORDENATES ANIMATIONPOSITION.X=80;
#define const   COORDENATES ANIMATIONPOSITION.Y=20;
#define const  SIZE ANIMATION
#define const SIZEOBJECT OBJECTCONTINUE;
#define const OBJECTCONTINUE.WIDTH=700;
#define const OBJECTCONTINUE.HEIGH=500;
#define ANIMATION.COLUMS=4;
#define const ANIMATION.ROWS=1;
#define POSITION OBJECTCONTINUE;
#define int
#int CONST  POSITIONCONTINUE.BEGIN=500;
#define int CONST  POSITIONCONTINUE.LAST=500;
#define const int NUMBERCONTINUE =1;
#define const int =2;
#define POSITION POSITIONMENU;
 #define POSITIONMENU.BEGIN= 500;
#define  POSITIONMENU.LAST=500;
# const SIZEOBJECT OBJECTMENU.WIDTH= 50;
#const SIZEOBJECT OBJECTMENU.HEIGH=500;
#define int const TIMESTOPLAY =0;
#define int  BUTTONCONITNUEWITHOUTDIRECTIONAL=1;
#define int const BUTTONMENUWITHOUTDIRECTIONAL=2;

 Struct type def int back_ground_color{
  int red;
 int green ; 
 int black;
 int alpha;
} 
#define  const  back_ground_color BACKGROUND.red= 255; 
#define const  back_ground_color  BACKGROUND.green=160;
#define    const  back_ground_color  BACKGROUND.black=156;
#define    const  back_ground_color  BACKGROUND.alpha=125;
 # define const int NUMBERLOWERTHANCONTINUE=0;
#define const int NUMBERMORETHANMENU=2;
,

.ROWS= 1;
ANIMATIONSIZE.COLUMNS=4;
#define double  ANINMATIONTIME= 0.8;
Const SELECTEDCOLOR[0]=255;
Const SELECTEDCOLOR[1]=255;
Const SELECTEDCOLOR[2]=255;
Const SELECTEDCOLOR[3]=0;
Conts int TIMESTOPLAY=0;  
#include <typeinfo>
#include <iostream>

using namespace engine;

LoseScene::LoseScene(int id) : Scene(id){
    selectButton = 1;
    select = new Color(SELECTEDCOLOR);
    notSelect = new Color(NOTSELECTEDCOLOR);

    soundEffect = new Audio("assets/sounds/SELECT6.wav",”EFFECT”, SOUNDEFFECT );
    backgroundMusic = new Audio("assets/sounds/GAMEOVER.wav", "MUSIC", BACKGROUNMUSIC );
    background = new Animation("assets/sprites/lose.png",ANIMATIONSIZE,ANIMATIONTIME);
    background->addAction("lose",POSITION);
    background->setInterval("lose");
}

LoseScene::~LoseScene(){
}

void LoseScene::draw(){
        background->draw_instant(ANIMATIONPOSITION);

        for(auto gameObject : gameObjectsList) {
                (*gameObject.second).draw();
        }
}

void LoseScene::update(double timeElapsed){
        selectAction();
        assert(timeElapsed>0);
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
        Button  button2=new Button("assets/fonts/font.ttf", OBJECTCONTINUE, POSITIONCONTINUE, "Continue", 50) 
        gameObjectsList.push_back(std::pair<int, GameObject*>( NUMBERCONTINUE,button2));
        Button button3=new Button("assets/fonts/font.ttf" OBJECTMENU, POSITIONMENU,"Menu", 50)
        gameObjectsList.push_back(std::pair<int, GameObject*>( NUMBERMENU,button3));
        AnimationManager::instance.setBackgroundColor(new Color(BACKGROUND));
));
        backgroundMusic->play(TIMESTOPLAY);

}
void  selectActionLessThanContinue(){
                selectButton--;
                if(selectButton <= NUMBERLOWERTHANCONTINUE ) {
                        selectButton = NUMBERMENU;
                }
}    
 void selectActionMoreThanMenu() {
                selectButton++;
             if(selectButton > NUMBERMORETHANMENU) {
                        selectButton = NUMBERCONTINUE;
                }
} 
 void selectActionEnter();
                switch(selectButton) {
                case SELECTBUTTONCONITNUEWITHOUTDIRECTIONAL:
                        getSceneManager()->loadScene(getSceneManager()->get_before_scene_id());
                        break;
                case BUTTONMENUWITHOUTDIRECTIONAL:
                        getSceneManager()->loadScene(0);
                        break;
                default:
                        break;
                }
}

void  selectActionLeftorRightButton(){ 
               soundEffect->pause();
               soundEffect->play(TIMESTOPLAY);  
if(InputManager::instance.isKeyTriggered(InputManager::KeyPress::KEY_PRESS_LEFT)){
    selectActionLessThanContinue();
}else{    
    if(InputManager::instance.isKeyTriggered(InputManager::KeyPress::KEY_PRESS_RIGHT) {
         selectActionMoreThanMenu();
}

void LoseScene::selectAction(){
if(InputManager::instance.isKeyTriggered(InputManager::KeyPress::KEY_PRESS_ENTER)){
    selectActionEnter()
}else{
    selectActionLeftorRightButton()
}
 

void LoseScene::unload(){
}
