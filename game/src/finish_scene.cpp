#include "finish_scene.hpp"
#include "button.hpp"
#include <typeinfo>
#include <iostream>

using namespace engine;

finish_scene::finish_scene(int id) : Scene(id) {
    select_button = 1;
    select = new color(255, 255, 255, 0);
    not_select = new color(0, 0, 0, 0);
    sound_effect = new audio("assets/sounds/SELECT6.wav", "EFFECT", 100);
    background_sound = new audio("assets/sounds/FINAL.wav", "MUSIC", 50);
    background = new animation("assets/sprites/finish.png", 1, 1, 0.8);
    background->add_action("finish", 0,0);
    background->set_interval("finish");
}

finish_scene::~finish_scene() {
}

void finish_scene::draw() {
        background->draw_instant(80, 20);

        for(auto game_object : game_object_list) {
                (*game_object.second).draw();
        }
}

void finish_scene::update(double time_elapsed) {
        select_action();

        background->update();

        for(auto game_object : game_object_list) {
                if(typeid(*game_object.second) == typeid(button)) {
                        if(game_object.first == select_button) {
                                ((button *)(game_object.second))->set_text_color(select);
                        }else{
                                ((button *)(game_object.second))->set_text_color(not_select);
                        }
                }

                (*game_object.second).update(time_elapsed);
        }
}

void finish_scene::load() {
        game_object_list.push_back(std::pair<int, game_object*>(1,new button(
                "assets/fonts/font.ttf", 420, 500, 500, 500, "Menu", 50)));
        animation_manager::instance.set_background_color(new color(158,228,159, 125));
        background_sound->play(-1);

}

void finish_scene::select_action() {
        if(input_manager::instance.isKeyTriggered(input_manager::KeyPress::KEY_PRESS_ENTER)) {
                switch(select_button) {
                case 1:
                        get_scene_manager()->load_scene(0);
                        break;
                default:
                        break;
                }

        }
}

void finish_scene::unload() {
}
