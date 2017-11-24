#include "header.hpp"
#include "log.h"
#include <assert.h>
#define FILENAME "assets/sprites/selecao_personagens_sheet(68X20).png"
#define WIDTH 68
#define HEIGHT 20

#define MARGIN 5

Header::Header(double positionAxisX, double positionAxisY, int max_papers, int stageNumber) : GameObject(FILENAME, positionAxisX, positionAxisY, WIDTH, HEIGHT){
       assert(positionAxisX>0);
       assert(positionAxisY>0);    
        stageText = new Text("Stage "+std::to_string(stageNumber),"assets/fonts/font.ttf", 40, true, new Color(100,100,100,1), new Color(0,0,0,0));
        paperIcon = new Animation("assets/sprites/papeis(19X21).png", 1, 4, 0.5);
        paperIcon->setDrawSize(40,50);
        paperIcon->addAction("static", 0,0);
        paperIcon->setInterval("static");
        total_papers=0;
        total_papers = max_papers;
        assert(total_papers>0);
        updatePaperQuantity(0);
        animator = new Animation(FILENAME, 1, 4, 0.5);
        animator->addAction("none", 0,0);
        animator->addAction("Etemer", 1,1);
        animator->addAction("Etbilu", 2,2);
        animator->addAction("Etvarginha", 3,3);

        alienSelect = 1;
}

Header::~Header(){
}

void Header::update(double timeElapsed){
        assert(timeElapsed>0);
        timeElapsed = timeElapsed;
        verifySelect();
        animator->update();
        paperIcon->update();
}

void Header::draw(){
        assert(getPositionY()>0);//assert para verificar se y e positivo.
        assert(getPositionX()>0);
        animator->draw(getPositionX()+MARGIN, getPositionY()+MARGIN);
        paperIcon->draw(getPositionX()+800, getPositionY()- MARGIN);
        paper_text->draw(getPositionX()+840, getPositionY()+MARGIN);
        stageText->draw(getPositionX()+400, getPositionY()+MARGIN);
}

void Header::updatePaperQuantity(int newValue){// assert para verificar se  newValue apresenta algum valor.
   assert(newValue!=NULL);
    paper_text = convertToText(newValue);
}

Text* Header::convertToText(int newValue){// assert para verificar se  newValue apresenta algum valor.
       assert(newValue!=NULL);
       return new Text(std::to_string(newValue)+"/"+std::to_string(totalPapers),"assets/fonts/font.ttf", 40, true, new Color(100,100,100,1), new Color(0,0,0,0));
}
void Header::verifySelect(){
        switch(alienSelect) {
        case 0:
                animator->setInterval("none");
                break;
        case 1:
                animator->setInterval("Etemer");
                break;
        case 2:
                animator->setInterval("Etbilu");
                break;
        case 3:
                animator->setInterval("Etvarginha");
                break;
        default:
                // Nothing to do.
                break;
        }
}

void Header::setAlienSelect(int select){
        alienSelect = select;
}
