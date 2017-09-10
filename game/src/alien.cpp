#include "alien.hpp"
/* Verify    this method inicilize  characters and put  them  at right position.   
* @param width, heigh , Object name , position_x , position _y, animator.  
* @return Object name e o um dado de entrada que representa o personagem.
*/ 
/** width is the width of character.
* position_x represents the x position x  character.
* position_y  represents the y pósition caracter.
* height presents the heigh character
* which   variables set the nimator object.  
*/ 
Alien::Alien(std::string object_name, double position_x, double position_y,
                                     int width, int height) : GameObject(object_name,
                                                                         position_x,
                                                                         position_y,
                                                                         width, height){
  
  /** verifys if name charcter is Bilu  will select the image  of Bilu 
  if isn't verifys the next verifys the next controls *structure*/
    if(objectName.compare("assets/sprites/bilu_sheet.png") == 0){
        alienName = "Bilu";
  /** verifys if name charcter is vargina   ,will select  the image of vargina. 
  *if don't verifys the next verifys the next controls structure*/   
    }else if(objectName.compare("assets/sprites/varginha_sheet.png") == 0){
        alienName = "Varginha";
   /** verifys if  charcter name is  etemer  will select etemer image ,
   if isn't verifys the next verifys the next controls *structure*/     
    }else if(objectName.compare("assets/sprites/etemer_sheet.png") == 0){
        alienName = "Etemer";
    }
    animator = new Animation(objectName, 2, 10, 0.5);
/* this  paragraph set character position .*/ 
    animator->addAction("right",6,9);
    animator->addAction("left",1,4);
    animator->addAction("up",6,9);
    animator->addAction("down",1,4);
    animator->addAction("idle_right",5,5);
    animator->addAction("idle_left",0,0);
    animator->addAction("idle_up",5,5);
    animator->addAction("idle_down",0,0);
/**  this paragraph initialize variables of character  expect his position */
    idleAnimationNumber = 5;
    blockMovement = false;
    inPosition = false;
    movement_sound_effect = new Audio("assets/sounds/FOOTSTEP.wav", "EFFECT", 128);
}

Alien::~Alien(){}
/** this method  move characters  since which controls all moves of them.  
    * @param animator postion of charcter position_x .   the  incx the inicial position in x .
    * @return  animator ,itś the character position.
*/

void Alien::walkInX(double & incX){
     /** the chacter position since up is pressed will move up the character 
    *if don't move to next *condition */ 
    if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_RIGHT)){
        incX = incX;
        idleAnimationNumber = 5;
        animator->setInterval("right");
    }
  /** character moves since down is pressed , if don't press  down button move to next condition *.*/
    else if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_LEFT)){
        //movement_sound_effect->play(-1);
        incX = incX * (0-1);
        idleAnimationNumber = 0;
        animator->setInterval("left");
    }
    else {
        incX = 0;
    }
    setPositionX(getPositionX()+incX);
    if(CollisionManager::instance.verifyCollisionWithWallsAndChairs(this)){
        setPositionX(getPositionX()+(incX*(0-1)));
    }
}
/** Controls personagem movement in the y axis.  They paramerts ate incx , inc y and object   
   *@param Incx is a an enter parameter as inc y .  the exit parameter is the objetct chacter.   
*/

void Alien::walkInY(double & inc_y, double inc_x){

    if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_UP)){
        inc_y = inc_y * (0-1);
        idleAnimationNumber = 5;
        if(inc_x == 0){
            animator->setInterval("up");
        }
    }
  /** moves character since up  is pressed   if don't  moves to next  clause*/
    else if(engine::InputManager::instance.isKeyPressed(engine::InputManager::KeyPress::KEY_PRESS_DOWN)){
        incY = inc_y;
        idleAnimationNumber = 0;
        if(inc_x == 0){
            animator->setInterval("down");
        }
    }
    else {
        incY = 0;
    }
    setPositionY(getPositionY()+inc_y);
  /** Verifys the collison with objects and walls*/
    if(CollisionManager::instance.verifyCollisionWithWallsAndChairs(this)){
        setPositionY(getPositionY()+(inc_y*(0-1)));
    }
}
/** This method draw in display since 
   *@param animator ,  the positiuon character. 
   *@return the position character  
*/    

void Alien::draw(){
    INFO("ALIEN DRAW");
    animator->draw(getPositionX(), getPositionY());
}
/**
*This method  select  the object chater. The enter and exit  attribute is the object character*/
*@param animator    chacter  position
*/
Animation * Alien::getAnimation(){
  return animator;
}
/**  select the   allien character*/
void Alien::setAlienSelected(){
    isSelected = true;
}
/* disselect the alien character*/
void Alien::setAlienDeselect(){
    isSelected = false;
}
/* return the allien position which is stored in animator*/
bool Alien::isInPosition(){
    return inPosition;
}
