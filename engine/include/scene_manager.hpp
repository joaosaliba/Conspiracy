#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include <unordered_map>
#include "scene.hpp"

namespace engine{
    class SceneManager{
    public:
        SceneManager();
        void addScene(Scene* scene);
        void loadScene(int id);
        Scene* get_current_scene();
        int get_current_scene_id();
        int get_before_scene_id();
        void set_current_scene_id(int id);
    private:
        std::unordered_map< int, Scene *> scenes;
        Scene * current_scene;
        int current_scene_id;
        int before_scene_id;
    };
}
#endif
