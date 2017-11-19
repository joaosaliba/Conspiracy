#ifndef LOSE_SCENE_HPP
#define LOSE_SCENE_HPP

#include "engine.hpp"
#include "scene.hpp"
#include "animation.hpp"
#include "game_object.hpp"
#include "color.hpp"
#include "audio.hpp"

#include <vector>

using namespace engine;

class LoseScene: public Scene{
public:
    LoseScene(int id);
    ~LoseScene();
    void load();
    void draw();
    void update(double time_elapsed);
    void unload();
private:
    void selectAction();
    int selectButton;
    std::vector<std::pair<int, GameObject*>> gameObjectsList;
    Animation * background;
    Color * select;
    Color * notSelect;
    Audio * soundEffect;
    Audio * backgroundMusic;
};

#endif
