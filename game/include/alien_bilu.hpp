#ifndef ALIEN_BILU_HPP
#define ALIEN_BILU_HPP
#include "alien.hpp"

/** The class Bilu receives an Alien public class where the parameters to be defined
*received, such as position, type, and methods. The attributes that will be defined
*public and private
*/
class Bilu: public Alien {
public:
/**
 * Builder method
 * <p>This method performs the action of constructing the methods and passing the variables
 *used in class alien_bilu.hpp</p>
 * @param unsigned double-bilu_position_x
 * @param unsigned double-bilu_position_y
 * @param unsigned double-time_elapsed
 * @param unsigned bool-hacking
 * @param unsigned bool-editing
 * @param unsigned bool-last_action
 */
    Bilu(double bilu_position_x, double bilu_position_y);
    void draw();// draw the lever of bilu
    void update(double time_elapsed);// update the bilu lever durign time

protected:
    void special_action();

private:
    bool hacking = true; //declaring variable hacking "computers
    bool editing = true; // declaring variable editing "documents
    bool last_action = true; // declaring variablre last action
    void set_special_action_animator();
};

#endif
