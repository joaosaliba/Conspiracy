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
/**
 * Builder method
 * <p>This method performs the action of constructing the methods and passing the variables
 *used in class alien_varginha.hpp</p>
 * @param unsigned double-varginha_position_x
 * @param unsigned double-varginha_position_y
 * @param unsigned double-time_elapsed
 * @param unsigned bool-is_invisible
 * @param unsigned bool-turn_off
 */
    Varginha(double varginha_position_x, double varginha_position_y);
    void update(double time_elapsed);
    void draw();
    void set_default();
protected:
    void special_action();
private:
    void verify_turn();
    bool is_invisible = true;
    bool turn_off = true;
    Timer * timer_turn = nullptr;
    void varginha_position(double &varginha_position_x, double &varginha_position_y,
    int &SCREEN_INITIAL, int &SCREEN_WIDTH);  
    void check_final_position(FinishPoint* finish_point, bool &in_position);
    void verify_colision();
    void idle_animator(double &varginha_in_x, double &varginha_in_y, int &idle_animation_number,
    bool &turn_off, bool &is_selected); 
};

#endif
