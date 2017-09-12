#include "finish_scene.hpp"
#include "button.hpp"

#include <typeinfo>
#include <iostream>

using namespace engine;

/**class to object of finish_scene, where you can find some values and meths
 * to the same.
 *
 */

FinishScene::FinishScene(int id) : Scene(id) {
    select_button = 1;
    select = new Color(255, 255, 255, 0);
    not_select = new Color(0, 0, 0, 0);
    sound_effect = new Audio("assets/sounds/SELECT6.wav", "EFFECT", 100);
    background_sound = new Audio("assets/sounds/FINAL.wav", "MUSIC", 50);
    background = new Animation("assets/sprites/finish.png", 1, 1, 0.8);
    background->add_action("finish", 0,0);
    background->set_interval("finish");
}

FinishScene::~FinishScene() {
}

/**
* Método draw
* <p>Esse método executa a função de desenhar ao fundo da fase,
* utilizando o método draw</p>
*/

void FinishScene::draw() {
    background->draw_instant(80, 20);

    for(auto gameObject : game_objects_list) {
        (*gameObject.second).draw();
    }
}

/**
* Método update
* <p>Esse método utiliza o time_elapsed para saber quando tem que atualizar a interface da fase,
*  e usa um array para saber o que mostrar para o user.</p>
*/

void FinishScene::update(double time_elapsed) {
    select_action();

    background->update();

    for(auto gameObject : game_objects_list) {
        if(typeid(*gameObject.second) == typeid(Button)) {
            if(gameObject.first == select_button) {
                ((Button *)(gameObject.second))->set_text_color(select);
            }else{
                ((Button *)(gameObject.second))->set_text_color(not_select);
                 }
            }

    (*gameObject.second).update(time_elapsed);
    }
}

/**
* Método load
* <p>Esse método carrega todo o style padrão aplicado na fase.</p>
*/
void FinishScene::load() {
    game_objects_list.push_back(std::pair<int, GameObject*>(1,new Button("assets/fonts/font.ttf", 420, 500, 500, 500, "Menu", 50)));
    AnimationManager::instance.set_background_color(new Color(158,228,159, 125));
    background_sound->play(-1);

}

/**
* Método select_action
* <p>Esse método utiliza o select_action para carregar a próxima cena do jogo.</p>
*/
void FinishScene::select_action() {
    if(InputManager::instance.is_key_triggered(InputManager::KeyPress::KEY_PRESS_ENTER)) {
        switch(select_button) {
        case 1:
            get_scene_manager()->load_scene(0);
            break;
        default:
            break;
        }

    }
}

void FinishScene::unload() {
}
