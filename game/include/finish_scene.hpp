#ifndef FINISH_SCENE_HPP
#define FINISH_SCENE_HPP

#include "engine.hpp"
#include "scene.hpp"
#include "animation.hpp"
#include "game_object.hpp"
#include "color.hpp"
#include "audio.hpp"
#include <vector>

using namespace engine;

class finish_scene: public scene {
public:
    finish_scene(int id);
    ~finish_scene();
    void load();
    void draw();
    void update(double time_elapsed);
    void unload();
private:
    void select_action();
    int select_button;
    std::vector<std::pair<int, game_object*>> game_objects_list;
    animation * background;
    color * select;
    color * not_select;
    audio * sound_effect;
    audio * background_sound;
};

#endif
