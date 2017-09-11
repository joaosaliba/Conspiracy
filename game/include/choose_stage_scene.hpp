/**class to object of choose_stage_scene, where you can find some values, files,
 *objects and meths to the same.
 */

#ifndef CHOOSE_STAGE_SCENE_HPP
#define CHOOSE_STAGE_SCENE_HPP

#include "engine.hpp"
#include "scene.hpp"
#include "sprite.hpp"
#include "game_object.hpp"
#include "color.hpp"
#include "audio.hpp"
#include "save_manager.hpp"

#include <vector>

using namespace engine;

class ChooseStageScene: public Scene{
public:
    ChooseStageScene(int id);
    ~ChooseStageScene();
    void load();
    void draw();
    void update(double time_elapsed);
    void unload();
private:
    void select_action();
    int select_button;
    std::vector<std::pair<int, GameObject*>> game_objects_list;
    Sprite * background;
    Color * select;
    Color * not_select;
    Audio * sound_effect;
};

#endif
