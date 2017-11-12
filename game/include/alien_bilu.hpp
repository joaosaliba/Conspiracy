#ifndef ALIEN_BILU_HPP
#define ALIEN_BILU_HPP
#include "alien.hpp"
#include "log.h"
#include "paper.hpp"
#include "door_switch.hpp"


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
    
    bool editing = true; // declaring variable editing "documents
    bool last_action = true; // declaring variablre last action
    void set_special_action_animator();
    void editing_paper(Paper* paper,bool &editing, bool &block_movement);
    void check_final_position(FinishPoint* finish_point,bool &in_position);
    void idle_animator(double &move_bilu_in_x, double &move_bilu_in_y, int &idle_animation_number);
    void walk(bool &block_movement, bool &is_selected, double &move_bilu_in_x, 
    double &move_bilu_in_y);
    void hacking_bilu(DoorSwitch* doorSwitch,bool &hacking, bool &block_movement);
    void bilu_position(double &bilu_position_x,double &bilu_position_y, int &SCREEN_INITIAL,
    int &SCREEN_WIDTH); 
    void verify_collision();
    void editing_percent(Paper* paper,bool &block_movement, bool &editing);
    void interaction(DoorSwitch* doorSwitch, bool &hacking, bool &block_movement);
    void instance_actions(DoorSwitch* doorSwitch,Paper* paper, bool &block_movement, bool &editing,
    bool &hacking);
    
};

#endif
