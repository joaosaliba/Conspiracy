#ifndef SELECT_ALIEN_HPP
#define SELECT_ALIEN_HPP

#include "animation.hpp"
#include "game_object.hpp"
#include "text.hpp"

using namespace engine;

class Header: public GameObject{
public:
    Header(double positionX, double positionY, int maxPapers, int stageNumber);
    ~Header();
    void update(double timeElapsed);
    void draw();
    void init();
    void setAlienSelect(int select);
    Animation * getAnimation();
    void updatePaperQuantity(int newValue);
private:
    Animation* animator;
    Animation* paper_icon;
    Text* paper_text;
    Text* stage_text;
    int total_papers; //declareting variables total papers
    int alien_select; // declareting variables alien selection
    Text* convertToText(int newValue);
    void verifySelect();

};
#endif
