#ifndef ALIEN_ETEMER_HPP
#define ALIEN_ETEMER_HPP

#include "alien.hpp"
#include <time.h>

/** The class Etemer receives an Alien public class where the parameters to be defined
*received, such as position, type, and methods. The attributes that will be defined
*public,private and protected
*/

class Etemer: public Alien {
public:
/**
 * Builder method
 * <p>This method performs the action of constructing the methods and passing the variables
 *used in class alien_etemer.hpp</p>
 * @param unsigned double-etemer_position_x
 * @param unsigned double-etemer_position_y
 * @param unsigned double-etemer_distance
 * @param unsigned double-etemer_in_x
 * @param unsigned double-etemer_in_y
 * @param unsigned bool-talking
 */
    Etemer(double etemer_position_x, double etemer_position_y);
    void update(double time_elapsed);// update the Etermer lever durign time
    void draw();// draw the lever of Etemer
    void verify_distance(GameObject* guard);
protected:
    void special_action(GameObject* guard, double etemer_distance);
    void walk_in_X(double & etemer_in_x);
    void walk_in_Y(double & etemer_in_y, double );

private:
    bool talking;
    void move_chair();
};

#endif
