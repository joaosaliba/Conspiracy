#include "header.hpp"
#include "log.h"

#define FILENAME "assets/sprites/selecao_personagens_sheet(68X20).png"
#define WIDTH 68
#define HEIGHT 20

#define MARGIN 5

Header::Header(double position_x, double position_y, int max_papers, int stage_number) : GameObject(FILENAME, position_x, position_y, WIDTH, HEIGHT) {

        stage_text = new Text("Stage "+std::to_string(stage_number),"assets/fonts/font.ttf", 40, true, new Color(100,100,100,1), new Color(0,0,0,0));
        paper_icon = new Animation("assets/sprites/papeis(19X21).png", 1, 4, 0.5);
        paper_icon->setDrawSize(40,50);
        paper_icon->add_action("static", 0,0);
        paper_icon->set_interval("static");

        total_papers = max_papers;

        updatePaperQuantity(0);

        animator = new Animation(FILENAME, 1, 4, 0.5);
        animator->add_action("none", 0,0);
        animator->add_action("Etemer", 1,1);
        animator->add_action("Etbilu", 2,2);
        animator->add_action("Etvarginha", 3,3);

        alien_select = 1;
}

Header::~Header() {

}

void Header::update(double timeElapsed) {
        timeElapsed = timeElapsed;
        verifySelect();
        animator->update();
        paper_icon->update();
}

void Header::draw() {
        animator->draw(get_position_x()+MARGIN, get_position_y()+MARGIN);
        paper_icon->draw(get_position_x()+800, get_position_y()- MARGIN);
        paper_text->draw(get_position_x()+840, get_position_y()+MARGIN);
        stage_text->draw(get_position_x()+400, get_position_y()+MARGIN);
}

void Header::updatePaperQuantity(int new_value) {
    paper_text = convertToText(new_value);
}

Text* Header::convertToText(int new_value) {
    return new Text(std::to_string(new_value)+"/"+std::to_string(total_papers),"assets/fonts/font.ttf", 40, true, new Color(100,100,100,1), new Color(0,0,0,0));
}
void Header::verifySelect() {
        switch(alien_select) {
        case 0:
                animator->set_interval("none");
                break;
        case 1:
                animator->set_interval("Etemer");
                break;
        case 2:
                animator->set_interval("Etbilu");
                break;
        case 3:
                animator->set_interval("Etvarginha");
                break;
        default:
                // Nothing to do.
                break;
        }
}

void Header::setAlienSelect(int select) {
        alien_select = select;
}
