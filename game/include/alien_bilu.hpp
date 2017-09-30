#ifndef ALIEN_BILU_HPP
#define ALIEN_BILU_HPP
#include "alien.hpp"

/** The class Bilu receives an Alien public class where the parameters to be defined
*received, such as position, type, and methods. The attributes that will be defined
*public and private
*/
class Bilu: public Alien {
public:
    Bilu(double bilu_position_x, double bilu_position_y);
    void draw();// draw the lever of bilu
    void update(double time_elapsed);// update the bilu lever durign time

protected:
    void special_action();

private:
<<<<<<< HEAD
    bool hacking;
    bool editing;
    bool last_action;
    void set_special_action_animator();
=======
    bool hacking; //declaring variable hacking "computers
    bool editing; // declaring variable editing "documents
    bool last_action; // declaring variablre last action 
    void setSpecialActionAnimator();
>>>>>>> origin/Development
};

#endif
