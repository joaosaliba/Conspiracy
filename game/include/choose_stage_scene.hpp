#ifndef CHOOSE_STAGE_scene_HPP
#define CHOOSE_STAGE_scene_HPP

#include "engine.hpp"
#include "scene.hpp"
#include "sprite.hpp"
#include "game_object.hpp"
#include "color.hpp"
#include "audio.hpp"
#include "save_manager.hpp"
#include <vector>

using namespace engine;

class choose_stage_scene: public scene {
public:
    choose_stage_scene(int id);
    ~choose_stage_scene();
    void load();
    void draw();
    void update(double time_elapsed);
    void unload();
private:
    void select_action();
    int select_button;
    std::vector<std::pair<int, game_object*>> game_objects_list;
    sprite * background;
    color * select;
    color * not_select;
    audio * sound_effect;
};

#endif
