#include "scene.hpp"

using namespace engine;

Scene::Scene(int id) {
    set_id(id);
}

void Scene::load() {
}
void Scene::draw() {
}
void Scene::unload() {
}

int Scene::get_id() {
    return scene_id;
}
void Scene::set_id(int new_id) {
    scene_id = new_id;
}
