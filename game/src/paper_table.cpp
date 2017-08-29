#include "paper_table.hpp"
#include "log.h"

PaperTable::PaperTable(std::string object_name, double position_x, double position_y,
                                     int width, int height) : GameObject(object_name,
                                                                         position_x,
                                                                         position_y,
                                                                         width, height){
table = new Table("assets/sprites/mesa.png", position_x, position_y, width, height);
paper = new Paper("assets/sprites/papeis(19X21).png", position_x + 20, position_y - 2, 10, 40);
}

PaperTable::~PaperTable(){

}

void PaperTable::update(double timeElapsed){
   table->update(timeElapsed);
   paper->update(timeElapsed);
}

void PaperTable::draw(){
   table->draw();
   paper->draw();
}

Paper* PaperTable::get_paper(){
    return paper;
}

Table* PaperTable::get_table(){
    return table;
}
