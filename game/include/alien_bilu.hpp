#ifndef ALIEN_BILU_HPP
#define ALIEN_BILU_HPP

#include "alien.hpp"

class Bilu: public Alien{
public:
    Bilu(double positionX, double positionY);
    void draw();
    void update(double timeElapsed);

protected:
    void specialAction();

private:
    bool hacking; //declaring variable hacking "computers
    bool editing; // declaring variable editing "documents
    bool last_action; // declaring variablre last action 
    void setSpecialActionAnimator();
};

#endif
