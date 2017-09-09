#ifndef ALIEN_BILU_HPP
#define ALIEN_BILU_HPP

#include "alien.hpp"

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
