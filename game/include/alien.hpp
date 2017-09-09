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
    void walkInX(double & inc_x);
    void walkInY(double & inc_y, double inc_x);
    Animation* animator;
    int idle_animation_number;
    std::string alienName;
    bool block_movement;
    bool is_selected;
    bool in_position;
    Audio *movement_sound_effect;
};

#endif
