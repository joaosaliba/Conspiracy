#include "scene_manager.hpp"
#include "scene.hpp"
#include "save_manager.hpp"

using namespace engine;

SceneManager::SceneManager() {
    before_scene_id = 0;
    current_scene_id = 0;
}

void SceneManager::addScene(Scene* scene) {
    if(scenes.find(scene->get_id()) != scenes.end()) {
        INFO("Failed to load scene");
    }else{
        scenes[scene->get_id()] = scene;
    }
}

void SceneManager::loadScene(int id) {
    if(scenes.find(id) == scenes.end()){
        INFO("Invalid Scene ID to Load");
    }else{
        Scene* scene = current_scene;
        if(scene != NULL) {
            scene->unload();
        }
        current_scene = scenes[id];
        current_scene->load();
        before_scene_id = current_scene_id;
        current_scene_id = current_scene->get_id();
        if (before_scene_id >= SaveManager::instance.getStageNumberUnlock() && before_scene_id < 6 && current_scene_id != 6) {
              SaveManager::instance.saveActualSituation(before_scene_id + 1);
        }
    }
}

Scene* SceneManager::get_current_scene() {
    return current_scene;
}

int SceneManager::get_current_scene_id() {
    return current_scene_id;
}

int SceneManager::get_before_scene_id() {
    return before_scene_id;
}

void SceneManager::set_current_scene_id(int id){
    current_scene_id = id;
}
