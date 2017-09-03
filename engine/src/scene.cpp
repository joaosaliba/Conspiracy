#include "scene.hpp"

using namespace engine;

Scene::Scene(int id){
    setId(id);
}

void Scene::load(){}
void Scene::draw(){}
void Scene::unload(){}

int Scene::getId(){
    return scene_id;
}
void Scene::setId(int new_id){
    sceneId = new_id;
}
