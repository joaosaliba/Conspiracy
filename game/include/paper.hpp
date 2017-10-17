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
    Paper(std::string object_name, double paper_position_x, double paper_position_y, int paper_width, int paper_height);
    ~Paper();
    void update(double time_elapsed);
    void draw();
    void init();
    Animation * getAnimation();
    void animate();
    void stopAnimation();
    bool isEdited();
    double getEditingBarPercent();
    void resetEditingProgress();
    void playEffect();
    void stopEffect();
    void getPercentage();
protected:
    Animation* animator;
    ProgressBar *paper_editing_bar;
    bool paper_edited;
    bool paper_is_being_edited;
    Audio* paper_editing_sound;
};

#endif
