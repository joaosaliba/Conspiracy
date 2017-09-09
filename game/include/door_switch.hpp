#ifndef DOOR_SWITCH_HPP
#define DOOR_SWITCH_HPP

#include "engine.hpp"
#include "animation.hpp"
#include "game_object.hpp"
#include "audio.hpp"
#include "progress_bar.hpp"

using namespace engine;

/**class to object of door_switch, where you can find some values and meths to the same.
 *
 */

class DoorSwitch: public GameObject{
public:
    DoorSwitch(std::string object_name, double position_x, double position_y, int width, int height);
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
    bool pressed;
    Animation* animator;
private:
    Audio *hacking_effect;
    ProgressBar *hacking_bar;
};

#endif
