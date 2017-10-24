/**
 * @file door_switch.hpp
 * @brief class to object of door_switch, where you can find some values, files,
 * others objects used in this class and methods to the same.
 * @copyright  GNU GENERAL PUBLIC LICENSE.
 */

#ifndef DOOR_SWITCH_HPP
#define DOOR_SWITCH_HPP

#include "engine.hpp"
#include "animation.hpp"
#include "game_object.hpp"
#include "audio.hpp"
#include "progress_bar.hpp"

using namespace engine;



class DoorSwitch: public GameObject{
public:
    DoorSwitch(std::string object_name, double door_switch_position_x, double door_switch_position_y, int door_switch_width, int door_switch_height);
    /**
      *    @brief door_switch object destructor.
     */
    ~DoorSwitch();
    void update(double time_elapsed);
    void draw();
    void init();
    Animation * getAnimation();
    void animate();
    void stop_animation();
    bool is_pressed();
    void play_effect();
    void stop_effect();
    double get_hacking_bar_percent();
    void reset_hacking_progress();
protected:
    bool pressed = true;
    Animation* animator = nullptr;
private:
    Audio *hacking_effect = nullptr;
    ProgressBar *hacking_bar = nullptr;
};

#endif
