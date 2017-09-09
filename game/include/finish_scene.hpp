#ifndef FINISH_SCENE_HPP
#define FINISH_SCENE_HPP

#include "engine.hpp"
#include "scene.hpp"
#include "animation.hpp"
#include "game_object.hpp"
#include "color.hpp"
#include "audio.hpp"

#include <vector>

/**class to object of finish_scene, where you can find some values and meths "constructor"
 * and "destructor" to the same.
 *
 */

using namespace engine;

class FinishScene: public Scene{
public:
    FinishScene(int id);
    ~FinishScene();
    void load();
    void draw();
    void update(double time_elapsed);
    void unload();
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
