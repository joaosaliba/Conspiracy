#ifndef WIN_SCENE_HPP
#define WIN_SCENE_HPP

#include "engine.hpp"
#include "scene.hpp"
#include "animation.hpp"
#include "game_object.hpp"
#include "color.hpp"
#include "audio.hpp"

#include <vector>


using namespace engine;

class WinScene: public Scene{
public:
    WinScene(int id);
    ~WinScene();

private:
  void load();
  void draw();
  void update(double timeElapsed);
  void unload();
    void selectAction();
    int selectButton;
    std::vector<std::pair<int, GameObject*>> gameObjectsList;
    Animation * background;
    Color * select;
    Color * notSelect;
    Audio * soundEffect;
};

#endif
