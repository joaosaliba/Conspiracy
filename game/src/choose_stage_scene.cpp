#include "choose_stage_scene.hpp"
#include "choice.hpp"
#include <typeinfo>
#include <iostream>

using namespace engine;

#define MAX_choice 5
#define MIN_choice 0


choose_stage_scene::choose_stage_scene(int id) : scene(id) {
    select_button = 1;
    select = new color(255, 255, 255, 0);
    not_select = new color(0, 0, 0, 0);
    background = new sprite("assets/sprites/selecao_fases.png");
    sound_effect = new audio("assets/sounds/SELECT6.wav", "EFFECT", 100);
}

choose_stage_scene::~choose_stage_scene() {
}

void choose_stage_scene::draw() {
        background->draw(80, 20);

        for(auto game_object : game_object_list) {
                (*game_object.second).draw();
        }
}

void choose_stage_scene::update(double time_elapsed) {
        select_action();

        for(auto game_object : game_object_list) {
                if(typeid(*game_object.second) == typeid(choice)) {
                        if(game_object.first == select_button) {
                                ((choice *)(game_object.second))->set_text_color(select);
                                ((choice *)(game_object.second))->set_chosen(true);
                        }else {
                                ((choice *)(game_object.second))->set_text_color(not_select);
                                ((choice *)(game_object.second))->set_chosen(false);
                        }

                        if(game_object.first <= save_manager::instance.get_stage_number_unlock()) {
                                ((choice *)(game_object.second))->set_unlock(true);
                        }
                }

                if(!game_object.first) {
                        if(game_object.first == select_button) {
                          ((button *)(game_object.second))->set_text_color(select);
                        }else{
                          ((button *)(game_object.second))->set_text_color(not_select);
                        }
                }

                (*game_object.second).update(time_elapsed);
        }
}

void choose_stage_scene::load() {
        game_object_list.push_back(std::pair<int, game_object*>(0,new button(
                "assets/fonts/font.ttf", 20, 20, 100, 100, "Voltar", 30)));
        game_object_list.push_back(std::pair<int, game_object*>(1,new choice(
                "assets/sprites/choices/stage_1.png", 50, 100, 200, 150, "Fase 1", 40)));
        game_object_list.push_back(std::pair<int, game_object*>(2,new choice(
                "assets/sprites/choices/stage_2.png", 720, 100, 200, 150, "Fase 2", 40)));
        game_object_list.push_back(std::pair<int, game_object*>(3,new choice(
                "assets/sprites/choices/stage_3.png", 50, 400, 200, 150, "Fase 3", 40)));
        game_object_list.push_back(std::pair<int, game_object*>(4,new choice(
                "assets/sprites/choices/stage_4.png", 720, 400, 200, 150, "Fase 4", 40)));
        game_object_list.push_back(std::pair<int, game_object*>(5,new choice(
                "assets/sprites/choices/stage_5.png", 400, 250, 200, 150, "Fase 5", 40)));
        animation_manager::instance.set_background_color(new color(255,225,142, 125));
}

void choose_stage_scene::select_action() {
        if(input_manager::instance.is_key_triggered(input_manager::KeyPress::KEY_PRESS_LEFT)) {
                sound_effect->pause();
                sound_effect->play(0);
                select_button--;
                if(select_button < MIN_choice) {
                        select_button = MAX_choice;
                }
        }
        else if(input_manager::instance.is_key_triggered(input_manager::KeyPress::KEY_PRESS_RIGHT)) {
                sound_effect->pause();
                sound_effect->play(0);
                select_button++;
                if(select_button > MAX_choice) {
                        select_button = MIN_choice;
                }
        }

        if(input_manager::instance.is_key_triggered(input_manager::KeyPress::KEY_PRESS_ENTER)) {
                switch(select_button) {
                  case 0:
                          get_scene_manager()->load_scene(0);
                          break;
                  case 1:
                          if(select_button <= save_manager::instance.get_stage_number_unlock()) {
                              get_scene_manager()->load_scene(22);
                          }
                          break;
                  case 2:
                          if(select_button <= save_manager::instance.get_stage_number_unlock()) {
                              get_scene_manager()->load_scene(2);
                          }
                          break;
                  case 3:
                          if(select_button <= save_manager::instance.get_stage_number_unlock()) {
                              get_scene_manager()->load_scene(3);
                          }
                          break;
                  case 4:
                          if(select_button <= save_manager::instance.get_stage_number_unlock()) {
                              get_scene_manager()->load_scene(4);
                          }
                          break;
                  case 5:
                          if(select_button <= save_manager::instance.get_stage_number_unlock()) {
                              get_scene_manager()->load_scene(5);
                          }
                          break;
                default:
                        break;
                }

        }
}

void choose_stage_scene::unload() {
}
