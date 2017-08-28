#ifndef TUTORIAL_SCENE_HPP
#define TUTORIAL_SCENE_HPP

#include "engine.hpp"
#include "button.hpp"
#include "timer.hpp"


using namespace engine;

class TutorialScene: public Scene {
public:
    TutorialScene(int id, std::string background_file, int next_scene);
    void load();
    void update(double time_elapsed);
    void draw();
    void unload();
private:
    Timer* scene_timer;
    Sprite* background;
    int new_next_scene;
    std::vector<std::pair<int, GameObject*>> gameObjectsList;
};

#endif
