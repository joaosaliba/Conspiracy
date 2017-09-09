#ifndef ALIEN_BILU_HPP
#define ALIEN_BILU_HPP
#include "alien.hpp"

/** the class Bilu receives an Alien public class where the parameters to be defined
received, such as position, type, and methods. The attributes that will be defined
public and private
*/
class Bilu: public Alien {
public:
    Bilu(double position_x, double position_y);
    void draw();
    void update(double time_elapsed);

protected:
    void special_action();

private:
    bool hacking;
    bool editing;
    bool last_action;
    void set_special_action_animator();
};

#endif
