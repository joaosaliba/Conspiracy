#include "tutorial_scene.hpp"

TutorialScene::TutorialScene(int id, std::string background_file, int next_scene): Scene(id) {
    background = new Sprite(background_file);
    new_next_scene = next_scene;
    scene_timer = new Timer();
}

void TutorialScene::draw() {
    background->draw(0,0);
}

void TutorialScene::update(double time_elapsed) {
    time_elapsed = time_elapsed;
    if(InputManager::instance.isKeyTriggered(InputManager::KeyPress::KEY_PRESS_ENTER) || scene_timer->total_elapsed_time() >= 4000) {
        getSceneManager()->loadScene(new_next_scene);
    }
}

void TutorialScene::load() {
    scene_timer->start();
    gameObjectsList.push_back(std::pair<int, GameObject*>(2,new Button("assets/fonts/font.ttf", 350, 400, 500, 500, "Continue", 50)));
}

void TutorialScene::unload() {

}
