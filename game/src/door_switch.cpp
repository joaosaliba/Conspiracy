#include "door_switch.hpp"

/**class to object of door_switch, where you can find some values and meths to the same.
 *
 */

DoorSwitch::DoorSwitch(std::string object_name, double position_x, double position_y,
                                     int width, int height) : GameObject(object_name,
                                                                         position_x,
                                                                         position_y,
                                                                         width, height) {
    animator = new Animation(object_name, 1, 6, 0.5);

    hacking_effect = new Audio("assets/sounds/PCNOISE.wav", "EFFECT", 60);
    hacking_bar = new ProgressBar(position_x-7, position_y-10, 45, 5, 0.002);

    animator->add_action("beingHacked", 1,5);
    animator->add_action("idle", 0, 0);
    pressed = false;
}

DoorSwitch::~DoorSwitch(){}

void DoorSwitch::update(double time_elapsed) {
    time_elapsed = time_elapsed;
    animator->update();
    if(is_pressed())) {
        hacking_bar->update(time_elapsed);
    }
}

void DoorSwitch::draw() {
    INFO("DoorSwitch DRAW");
    if(is_pressed()) {
        animator->set_interval("beingHacked");
        AnimationManager::instance.addProgressBar(hacking_bar);
        if(hacking_bar->get_percent() <= 0.0) {
            pressed = false;
            set_enabled(false);
        }
    }else {
        animator->set_interval("idle");
    }
    animator->draw(get_position_x(), get_position_y());
}

Animation * DoorSwitch::getAnimation() {
  return animator;
}

void DoorSwitch::animate() {
    pressed = true;
}

void DoorSwitch::stop_animation() {
    pressed = false;
}

bool DoorSwitch::is_pressed() {
    return pressed;
}

void DoorSwitch::play_effect() {
    hacking_effect->play(2);
}

void DoorSwitch::stop_effect() {
    hacking_effect->stop();
}

double DoorSwitch::get_hacking_bar_percent() {
    return hacking_bar->get_percent();
}

void DoorSwitch::reset_hacking_progress() {
    hacking_bar->reset_percent();
}
