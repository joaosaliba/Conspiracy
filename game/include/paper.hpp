#ifndef PAPER_HPP
#define PAPER_HPP

#include "engine.hpp"
#include "animation.hpp"
#include "animation_manager.hpp"
#include "progress_bar.hpp"
#include "audio.hpp"

using namespace engine;

class Paper: public GameObject{
public:
    Paper(std::string object_name, double position_x, double position_y, int width, int height);
    ~Paper();
    void update(double time_elapsed);
    void draw();
    void init();
    Animation * get_animation();
    void animate();
    void stop_animation();
    bool is_edited();
    double get_editing_bar_percent();
    void reset_editing_progress();
    void play_effect();
    void stop_effect();
protected:
    animation* animator;
    progress_bar *editing_bar;
    bool edited;
    bool is_being_edited;
    Audio* paper_editing_sound;
};

#endif
