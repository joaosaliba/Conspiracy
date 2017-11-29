
#include "table.hpp"
#include "log.h"
#include <assert.h>
#define const MAX_COLUMS=1000;
#define const MAX_LINES=1000;
#define const LINES=1;
#define const COLUMS=1;
#define const TIME=0.5;

Bool test_animation(int colums,int lines){
     Bool valida;
     if(colums<MAX_COLUMS){
       if(lines>MAX_LINES){
         valida=TRUE;
       }else{
         valida=FALSE;
     }else{
         valida=FALSE;
}         
Table::Table(std::string objectName, double positionX, double positionY,
                                     int width, int height) : GameObject(objectName,
                                                                         positionX,
                                                                         positionY,
                                                                width, height){
animator = new Animation(objectName, LINES,COLUMS,TIME);
assert( background.getCurrentPositionFrame()==0);
}

Table::~Table(){

}

void Table::update(double timeElapsed){
    timeElapsed=0.0; 
    timeElapsed = timeElapsed;
    assert(timeElapsed>0.0);
    animator->update();
}

void Table::draw(){
    animator->draw(getPositionX(), (getPositionY() - 10));
    animator->draw_collider(getPositionX(), getPositionY(), getWidth(), getHeight());

}
