#include "paper_table.hpp"
#include "log.h"
#include <assert.h>
 
PaperTable::PaperTable(std::string objectName, double PositionAxisX, double PositionAxisY,
                                     int width, int height) : GameObject(objectName,
                                                                         positionX,
                                                                         positionY,
                                                                         width, height){
assert(x>0);
assert(y>0);                                                                         
table = new Table("assets/sprites/mesa.png", PositionAxisX, PositionAxisY, width, height);
paper = new Paper("assets/sprites/papeis(19X21).png", PositionAxisX + 20, PositionAxisY - 2, 10, 40);
}

PaperTable::~PaperTable(){

}

void PaperTable::update(double timeElapsed){
   assert(timeElapsed>0);\\ assert para verificar se timeelapsed e positivo. 
   table->update(timeElapsed);
   paper->update(timeElapsed);
}

void PaperTable::draw(){
   table->draw();
   paper->draw();
}

Paper* PaperTable::getPaper(){
    return paper;
}

Table* PaperTable::getTable(){
    return table;
}
