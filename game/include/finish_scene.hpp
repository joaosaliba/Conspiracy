/**
 * @file finish_scene.cpp
 * @brief class to object of finish_scene, where you can find some values, files,
 * others objects used in this class and methods to the same.
 * @copyright  GNU GENERAL PUBLIC LICENSE.
 */

#ifndef FINISH_SCENE_HPP
#define FINISH_SCENE_HPP

#include "engine.hpp"
#include "scene.hpp"
#include "animation.hpp"
#include "game_object.hpp"
#include "color.hpp"
#include "audio.hpp"
#include "log.h"

#include <vector>



using namespace engine;

class FinishScene: public Scene{



public:
    FinishScene(int id);
    ~FinishScene();

    void load();
    void update(double time_elapsed);
    void unload();

    void draw();

private:
    void select_action();
    int select_button;
    
    std::vector<std::pair<int, GameObject*>> game_objects_list;
    Animation * background;
    Color * select;
    Color * not_select;
    Audio * sound_effect;
    Audio * background_sound;
};

#endif
