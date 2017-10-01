#ifndef ALIEN_HPP
#define ALIEN_HPP

#include "engine.hpp"
#include "input_manager.hpp"
#include "animation.hpp"
#include "game_object.hpp"
#include "collision_manager.hpp"
#include "audio.hpp"
#include "finish_point.hpp"

/** The class Alien receives an GameObject public class where the parameters to be defined
* received, such as position, type, and methods. The attributes that will be defined
* public and private
*/

using namespace engine;

class Alien: public GameObject {
public:
/**
 * Builder method
 * <p>This method performs the action of constructing the methods and passing the variables
 *used in class alien_bilu.hpp</p>
 * @param unsigned double-alien_position_x
 * @param unsigned double-alien_position_y
 * @param unsigned int-width
 * @param unsigned int-height
 * @param unsigned double-time_elapsed
 * @param unsigned double-alien_in_x
 * @param unsigned double-alien_in_y
 * @param unsigned bool-block_movement
 * @param unsigned bool-is_selected
 * @param unsigned bool-in_position
 */
    Alien(std::string objectName, double alien_position_x, double alien_position_y,
    int width, int height);
    ~Alien();
    virtual void update(double time_elapsed) = 0;
    void draw();
    void init();
    Animation * get_animation();
    void set_alien_selected();
    void set_alien_deselect();
    bool is_in_position();

protected:
    void walk_in_x(double & alien_in_x);
    void walk_in_y(double & alien_in_y, double alien_in_x);
    Animation* animator;
    int idle_animation_number; // delcaring variable idle animation number
    std::string alienName;
    bool block_movement; // delclarion  variable block movement
    bool is_selected; // delcaring  varible  that reference if the personage is selected
    bool in_position;// declaring variable in position
    Audio *movement_sound_effect;
};

#endif
