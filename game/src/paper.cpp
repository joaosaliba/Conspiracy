//#define NDEBUG *uncomment to disable assertions
#include "paper.hpp"
#include <assert.h>

Paper::Paper(std::string object_name, double position_x, double position_y,
                                     int width, int height) : GameObject(object_name,
                                                                         position_x,
                                                                         position_y,
                                                                         width, height) {

    animator = new animation(object_name, 1, 4, 0.5);

    std::vector<unsigned int> back_color = {22, 206, 26, 1};
    std::vector<unsigned int> front_color = {116, 225, 117, 1};
    editing_bar = new ProgressBar(position_x-3, position_y-8, 22.5, 5, 0.005, back_color, front_color);

    paper_editing_sound = new Audio("assets/sounds/PAPEROISE.wav", "EFFECT", 100);

    animator->add_action("idle",0,0);
    animator->add_action("being_edited",1,3);
    edited = false;
    is_being_edited = false;
    assert(paper_edited != NULL);
    assert(paper_is_being_edited != NULL);
}

Paper::~Paper() {}

void Paper::update(double time_elapsed) {
    time_elapsed = time_elapsed;
    if(is_being_edited) {
        editing_bar->update(time_elapsed);
        animator->set_interval("being_edited");
        if(editing_bar->get_percent() <= 0.0) {
            is_being_edited = false;
            edited = true;
            assert(paper_edited != NULL);
            assert(paper_is_being_edited != NULL);
        }
    }else{
        animator->set_interval("idle");
    }
    animator->update();
}

void Paper::animate() {
    is_being_edited = true;
     assert(paper_is_being_edited != NULL);
}

void Paper::stop_animation() {
    is_being_edited = false;
    assert(paper_is_being_edited != NULL);
}

bool Paper::is_edited() {
    return edited;
}

void Paper::draw() {
    INFO("Paper DRAW");
    animator->draw(get_position_x(), get_position_y());
    animator->draw_collider(get_position_x(), get_position_y(), get_width(), get_height());
    if(is_being_edited) {
        animation_manager::instance.add_progress_bar(editing_bar);
    }
}

animation * Paper::get_animation() {
  return animator;
  assert(animator != NULL);
}

double Paper::get_editing_bar_percent() {
    return editing_bar->get_percent();
}

void Paper::reset_editing_progress() {
    editing_bar->reset_Percent();
}

void Paper::play_effect() {
    paper_editing_sound->play(0);
}

void Paper::stop_effect() {
    paper_editing_sound->stop();
}
