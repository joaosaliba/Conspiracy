#ifndef ALIEN_ETEMER_HPP
#define ALIEN_ETEMER_HPP

#include "alien.hpp"
#include <time.h>

/** the class Etemer receives an Alien public class where the parameters to be defined
*received, such as position, type, and methods. The attributes that will be defined
*public,private and protected
*/

class Etemer: public Alien {
public:
    Etemer(double position_x, double position_y);
    void update(double time_elapsed);
    void draw();
    void verify_distance(GameObject* guard);
protected:
    void special_action(GameObject* guard, double distance);
    void walk_in_X(double & inc_x);
    void walk_in_Y(double & inc_y, double );

private:
    bool talking;
    void move_chair();
};

#endif
