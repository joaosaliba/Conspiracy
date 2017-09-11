#ifndef ALIEN_HPP
#define ALIEN_HPP

#include "engine.hpp"
#include "input_manager.hpp"
#include "animation.hpp"
#include "game_object.hpp"
#include "collision_manager.hpp"
#include "audio.hpp"
#include "finish_point.hpp"

/** the class Alien receives an GameObject public class where the parameters to be defined
*received, such as position, type, and methods. The attributes that will be defined
*public and private
*/

using namespace engine;

class Alien: public GameObject {
public:
    Alien(std::string objectName, double position_x, double position_y, int width, int height);
    ~Alien();
    virtual void update(double time_elapsed) = 0;
    void draw();
    void init();
    Animation * get_animation();
    void set_alien_selected();
    void set_alien_deselect();
    bool is_in_position();

protected:
    void walk_in_x(double & inc_x);
    void walk_in_y(double & inc_y, double inc_x);
    Animation* animator;
    int idle_animation_number;
    std::string alienName;
    bool block_movement;
    bool is_selected;
    bool in_position;
    Audio *movement_sound_effect;
};

#endif
