/**
    @file game_scene.cpp
    @brief Manages the game scenes.
    @copyright MIT License.
*/
#include "game_scene.hpp"
#include "player.hpp"
#include "scene.hpp"
#include "engine.hpp"
#include "wall.hpp"
#include "ground.hpp"
#include "collision_manager.hpp"
#include "guard.hpp"
#include "paper.hpp"
#include "door_system.hpp"
#include "audio.hpp"
#include "table.hpp"
#include "paper_table.hpp"
#include "chair.hpp"

//#define NDEBUG *uncomment to disable assertions
#include <typeinfo>
#include <iostream>
#include <assert.h>
#include "line.hpp"

using namespace engine;

/**
    @brief Game scene constructor.
    @param[in] id is the scene identificator.
    @param[in] newTiledFile file that manages the game scene according to the game level.
*/

GameScene::GameScene(int id, std::string new_tiled_file) : Scene(id){
    assert(new_tiled_file != NULL);
    assert(id != NULL);
    tiled_file = new_tiled_file;
    skip_timer = new Timer();
    stage_timer = new Timer();
    actual_papers = 0;
    assert(tiled_file != NULL);
    assert(skip_timer != NULL);
    assert(stage_timer != NULL);
    assert(actual_papers != NULL);
}

/**
    @brief Game scene constructor.
    @param[in] id is the scene identificator.
    @param[in] newTiledFile file that manages the game scene according to the game level.
    @param[in] audioFile file whith the game music.
*/

GameScene::GameScene(int id, std::string new_tiled_file, std::string audio_file) : Scene(id){
    assert(audio_file != NULL);
    assert(new_tiled_file != NULL);
    assert(id != NULL);
    if(audio_file == "assets/sounds/TEMA3.wav"){
        background_music = new Audio(audio_file, "MUSIC", 55);
        assert(background_music != NULL);
    }else{
        background_music = new Audio(audio_file, "MUSIC", 75);
        assert(background_music != NULL);
    }
    tiled_file = new_tiled_file;
    skip_timer = new Timer();
    stage_timer = new Timer();
    actual_papers = 0;
    assert(tiled_file != NULL);
    assert(skip_timer != NULL);
    assert(stage_timer != NULL);
    assert(actual_papers != NULL);
}

/**
    @brief It will renderize the game object.
*/

void GameScene::draw(){
        for(auto gameObject : gameObjectsList) {
                (*gameObject).draw();
        }
}

/**
    @brief Dismantle player game object.
*/

void GameScene::update(double time_elapsed){
    assert(time_elapsed != NULL);
    if(!player->isDead()){
        for(auto gameObject : gameObjectsList) {
                if(typeid(gameObject) != typeid(Player)){
                    (*gameObject).update(time_elapsed);
                }
        }
    }
    verifyWinOrLose();
}

/**
    @brief It vefifies if the player has won or lost the game.
*/

void GameScene::verifyWinOrLose(){
        bool all_papers_edited = true;
        std::vector<Guard *> guards;
        int count_papers = 0;
        assert(guards != NULL);
        assert(all_papers_edited != NULL);
        assert(count_papers != NULL);
        for(auto gameObject : gameObjectsList) {
                if(typeid(*gameObject) == typeid(Guard)) {
                        guards.push_back((Guard *)(gameObject));
                }else if(typeid(*gameObject) == typeid(PaperTable)) {
                        if(!(((PaperTable*)(gameObject))->getPaper())->isEdited()) {
                            all_papers_edited = false;
                        }else{
                            count_papers++;
                        }
                }
        }
        if(count_papers >= actual_papers){
            player->updatePaperQuantity(count_papers);
            actual_papers = count_papers;
        }
        for(Guard * guard : guards) {
            guard->verifyDistance(player->getVarginha());
            guard->verifyDistance(player->getBilu());
            ((Etemer *)(player->getEtemer()))->verify_distance(guard);
        }
    if((Etemer *)(player->getEtemer())->is_in_position() &&
      (Bilu*)(player->getBilu())->is_in_position() &&
      (Varginha*)(player->getVarginha())->is_in_position()){
          aliens_in_position = true;
      }

    if(!player->isDead()){
        stage_timer->step();
    }
    if(player->isDead()){
        if(stage_timer->elapsed_time() >= 2500){
            getSceneManager()->loadScene(6);
        }

    }else if((all_papers_edited && aliens_in_position) || (InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_K) && skip_timer->total_elapsed_time() >= 500)){
        if(getSceneManager()->get_current_scene_id() == 5){
            getSceneManager()->loadScene(9);
        }else{
            getSceneManager()->loadScene(7);
        }
    }
}

/**
    @brief It starts the game collider.
*/

void GameScene::initializeColliders(){
    assert(gameObjectsList != NULL);
    for(auto gameObject: gameObjectsList){
        if(typeid(*gameObject) == typeid(Wall)){
            CollisionManager::instance.addWall(gameObject);
        }else if(typeid(*gameObject) == typeid(Guard)){
            CollisionManager::instance.addGuard(gameObject);
            CollisionManager::instance.addGuardFieldOfVision(((Guard*)gameObject)->getFieldOfVision());
        }else if(typeid(*gameObject) == typeid(CameraSystem)){
            CollisionManager::instance.addCameraFieldOfVision(((CameraSystem*)gameObject)->getCamera()->getFieldOfVision());
            CollisionManager::instance.addCameraSwitch(((CameraSystem*)gameObject)->getCameraSwitch());
            CollisionManager::instance.addCameraLever(((CameraSystem*)gameObject)->getCameraLever());
        }else if(typeid(*gameObject) == typeid(PaperTable)){
            CollisionManager::instance.addPaper(((PaperTable*)(gameObject))->getPaper());
            CollisionManager::instance.addWall(((PaperTable*)(gameObject))->getTable());
        }else if(typeid(*gameObject) == typeid(DoorSystem)){
            CollisionManager::instance.addDoor(((DoorSystem*)(gameObject))->getDoor());
            CollisionManager::instance.addSwitch(((DoorSystem*)(gameObject))->getSwitch());
            CollisionManager::instance.addWall(((DoorSystem*)(gameObject))->getTable());
        }else if(typeid(*gameObject) == typeid(Table)){
            CollisionManager::instance.addWall(((Table*)(gameObject)));
        }else if(typeid(*gameObject) == typeid(Chair)) {
            CollisionManager::instance.addChair(gameObject);
        }else if(typeid(*gameObject) == typeid(FinishPoint)){
            CollisionManager::instance.addFinishPoint(gameObject);
        }
    }
}

/**
    @brief Loads the game scene.
*/

void GameScene::load(){
    background_music->play(-1);
    aliens_in_position = false;
    stage_timer->start();
    skip_timer->start();
    skip_timer->step();
    assert(background_music != NULL);
    assert(aliens_in_position != NULL);
    assert(stage_timer != NULL);
    assert(skip_timer != NULL);

    createGround();
    createGameBorders();
    createCenary();
    createAliens();
    createGuards();
    createDoorSystems();
    createPapers();
    createTables();
    createChairs();
    createFinishPoints();

    initializeColliders();
    AnimationManager::instance.setBackgroundColor(new Color(100,100,100, 125));

}

/**
    @brief It empties the game scene.
*/

void GameScene::unload(){
    CollisionManager::instance.resetLists();
    actual_papers = 0;
    assert(actual_papers != NULL);
    for(GameObject* object: gameObjectsList){
        free(object);
    }
    gameObjectsList.clear();
}

/**
    @brief Creates tables.
*/

void GameScene::createTables(){}

/**
    @brief Creates chairs.
*/

void GameScene::createChairs(){}

/**
    @brief It defines the game borders.
*/

void GameScene::createGameBorders(){
        for(int i=0; i<=960; i+=5) {
                gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", i, HEADER_SIZE + 0, 5, 20));
                gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", i, HEADER_SIZE + 595, 5, 5));
        }
        for(int j=0; j<=600; j+=5) {
                gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", 955, HEADER_SIZE + j, 5, 5));
                gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", 0, HEADER_SIZE + j, 5, 5));
        }
}

/**
    @brief Loads ground image.
*/

void GameScene::createGround(){
        for(int i=0; i<=960; i+=20) {
                for(int j=0; j<=600; j+=20) {
                        gameObjectsList.push_back(new Ground("assets/sprites/cenary/chao.png", i, HEADER_SIZE + j, 20, 20));
                }
        }
}

/**
    @brief Builds the game scene according to the game level.
*/

void GameScene::createCenary(){
    std::ifstream tile_file;
    assert(tile_file != NULL);
    tile_file.open(tiled_file);
    if(tile_file.is_open()) {
        char c;
        int compare;
        for(int i=0; i<=600; i+=20) {
            for(int j=0; j<=960; j+=20) {
                tile_file.get(c);
                compare = c-48;
                switch(compare) {
                    case 1: gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede2.png", j, HEADER_SIZE + i+25, 20, 40)); break;

                    case 2: gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j+15, HEADER_SIZE + i, 0, 0));
                            gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j+15, HEADER_SIZE + i+5, 5, 15));
                            gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j+15, HEADER_SIZE + i+10, 5, 15));
                            gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j+15, HEADER_SIZE + i+15, 5, 30));
                            gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j+15, HEADER_SIZE + i-5, 0, 0));
                            gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j+15, HEADER_SIZE + i-10, 0, 0));
                            gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j+15, HEADER_SIZE + i-15, 0, 0)); break;

                    case 3: gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j, HEADER_SIZE + i+15, 5, 5));
                            gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j+5, HEADER_SIZE + i+15, 5, 5));
                            gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j+10, HEADER_SIZE + i+15, 5, 5));
                            gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j+15, HEADER_SIZE +i+15, 5, 5)); break;

                    case 4: gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j, HEADER_SIZE + i, 0, 0));
                            gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j, HEADER_SIZE + i+5, 5, 15));
                            gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j, HEADER_SIZE + i+10, 5, 15));
                            gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j, HEADER_SIZE + i+15, 5, 30));
                            gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j, HEADER_SIZE + i-5, 0, 0));
                            gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j, HEADER_SIZE + i-10, 0, 0));
                            gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j, HEADER_SIZE + i-15, 0, 0)); break;

                    case 5: gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_door.png", j+15, HEADER_SIZE + i-20, 5, 60)); break;

                    case 6: gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_door.png", j, HEADER_SIZE + i-20, 5, 60));break;
                }
            }
        }
    }
}
