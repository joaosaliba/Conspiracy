#ifndef ALIEN_HPP
#define ALIEN_HPP

#include "engine.hpp"
#include "input_manager.hpp"
#include "animation.hpp"
#include "game_object.hpp"
#include "collision_manager.hpp"
#include "audio.hpp"
#include "finish_point.hpp"

using namespace engine;

class Alien: public GameObject{
public:
    Alien(std::string objectName, double position_x, double position_y, int width, int height);
    ~Alien();
    virtual void update(double time_elapsed) = 0;
    void draw();
    void init();
    Animation * getAnimation();
    void setAlienSelected();
    void setAlienDeselect();
    bool isInPosition();

protected:
    void walk_in_x(double & inc_x);
    void walk_in_y(double & inc_y, double inc_x);
    Animation* animator;
    int idle_animation_number; // delcaring variable idle animation number
    std::string alienName;
    bool block_movement; // delclarion  variable block movement
    bool is_selected; // delcaring  varible  that reference if the personage is selected
    bool in_position;// declaring variable in position
    Audio *movement_sound_effect;
};

#endif
