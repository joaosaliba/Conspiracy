#ifndef ALIEN_VARGINHA_HPP
#define ALIEN_VARGINHA_HPP

#include "alien.hpp"
#include "camera_switch.hpp"
#include "camera_lever.hpp"
#include "timer.hpp"

/** The class Varginha receives an Alien public class where the parameters to be defined
*received, such as position, type, and methods. The attributes that will be defined
*public and private
*/

class Varginha: public Alien {
public:
    Varginha(double position_x, double position_y);
    void update(double time_elapsed);
    void draw();
    void set_default();
protected:
    void special_action();
private:
    void verify_turn();
    bool is_invisible;
    bool turn_off;
    Timer * timer_turn;
};

#endif
