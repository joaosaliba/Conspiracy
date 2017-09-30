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
<<<<<<< HEAD
#include <typeinfo>
#include <iostream>
=======

//#define NDEBUG *uncomment to disable assertions
#include <typeinfo>
#include <iostream>
#include <assert.h>
>>>>>>> origin/Development
#include "line.hpp"

using namespace engine;

<<<<<<< HEAD
game_scene::game_scene(int id, std::string new_tiled_file) : scene(id) {
    tiled_file = new_tiled_file;
    skip_timer = new timer();
    stage_timer = new timer();
    actual_papers = 0;
}

game_scene::game_scene(int id, std::string new_tiled_file, std::string audio_file) : scene(id) {
    if(audio_file == "assets/sounds/TEMA3.wav") {
        background_music = new audio(audio_file, "MUSIC", 55);
    }else {
        background_music = new audio(audio_file, "MUSIC", 75);
    }
    tiled_file = new_tiled_file;
    skip_timer = new timer();
    stage_timer = new timer();
    actual_papers = 0;
}
void game_scene::draw() {
        for(auto game_object : game_object_list) {
                (*game_object).draw();
        }
}

void game_scene::update(double time_elapsed) {
    if(!player->is_dead()) {
        for(auto game_object : game_object_list) {
                if(type_id(game_object) != type_id(Player)) {
                    (*game_object).update(time_elapsed);
=======
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
>>>>>>> origin/Development
                }
        }
    }
    verify_win_or_lose();
}

<<<<<<< HEAD
void game_scene::verify_win_or_lose() {
        bool all_papers_edited = true;
        std::vector<guard *> guards;
        int count_papers = 0;
        for(auto game_object : game_object_list) {
                if(type_id(*game_object) == type_id(guard)) {
                        guards.push_back((guard *)(game_object));
                }else if(type_id(*game_object) == type_id(paper_table)) {
                        if(!(((paper_table*)(game_object))->get_paper())->is_edited()) {
=======
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
>>>>>>> origin/Development
                            all_papers_edited = false;
                        }else{
                            count_papers++;
                        }
                }
        }
<<<<<<< HEAD
        if(count_papers >= actual_papers) {
            player->update_paper_quantity(count_papers);
=======
        if(count_papers >= actual_papers){
            player->updatePaperQuantity(count_papers);
>>>>>>> origin/Development
            actual_papers = count_papers;
        }
        for(guard * guard : guards) {
            guard->verify_distance(player->get_varginha());
            guard->verify_distance(player->get_bilu());
            ((etemer *)(player->get_etemer()))->verify_distance(guard);
        }
<<<<<<< HEAD
    if((etemer *)(player->get_etemer())->is_in_position() &&
      (bilu*)(player->get_bilu())->is_in_position() &&
      (varginha*)(player->get_varginha())->is_in_position()) {
          aliens_in_position = true;
      }

    if(!player->is_dead()) {
        stage_timer->step();
    }
    if(player->is_dead()) {
        if(stage_timer->elapsed_time() >= 2500) {
            get_scene_manager()->load_scene(6);
        }

    }else if((all_papers_edited && aliens_in_position) || 
    (input_manager::instance.is_key_pressed(input_manager::KeyPress::KEY_PRESS_K) && 
    skip_timer->total_elapsed_time() >= 500)) {
        if(get_scene_manager()->get_current_scene_id() == 5) {
            get_scene_manager()->load_scene(9);
        }else {
            get_scene_manager()->load_scene(7);
=======
    if((Etemer *)(player->getEtemer())->isInPosition() &&
      (Bilu*)(player->getBilu())->isInPosition() &&
      (Varginha*)(player->getVarginha())->isInPosition()){
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
>>>>>>> origin/Development
        }
    }
}

<<<<<<< HEAD
void game_scene::initialize_colliders() {
    for(auto game_object: game_object_list) {
        if(type_id(*game_object) == type_id(wall)) {
            collision_manager::instance.add_wall(game_object);
        }else if(type_id(*game_object) == type_id(guard)) {
            collision_manager::instance.add_guard(game_object);
            collision_manager::instance.add_guard_field_of_vision(((guard*)game_object)->
            get_field_of_vision());
        }else if(type_id(*game_object) == type_id(camera_system)) {
            collision_manager::instance.add_camera_field_of_vision(((camera_system*)game_object)->
            get_camera()->get_field_of_vision());
            collision_manager::instance.add_camera_switch(((camera_system*)game_object)->
            get_camera_switch());
            collision_manager::instance.add_camera_lever(((camera_system*)game_object)->
            get_camera_lever());
        }else if(type_id(*game_object) == type_id(paper_table)) {
            collision_manager::instance.add_paper(((paper_table*)(game_object))->
            get_paper());
            collision_manager::instance.add_wall(((paper_table*)(game_object))->
            gettable());
        }else if(type_id(*game_object) == type_id(door_system)) {
            collision_manager::instance.add_door(((door_system*)(game_object))->
            get_door());
            collision_manager::instance.add_switch(((door_system*)(game_object))->
            get_switch());
            collision_manager::instance.add_wall(((door_system*)(game_object))->
            get_table());
        }else if(type_id(*game_object) == type_id(table)) {
            collision_manager::instance.add_wall(((table*)(game_object)));
        }else if(type_id(*game_object) == type_id(Chair)) {
            collision_manager::instance.add_chair(game_object);
        }else if(type_id(*game_object) == type_id(FinishPoint)) {
            collision_manager::instance.add_finish_point(game_object);
=======
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
>>>>>>> origin/Development
        }
    }
}

<<<<<<< HEAD
void game_scene::load() {
=======
/**
    @brief Loads the game scene.
*/

void GameScene::load(){
>>>>>>> origin/Development
    background_music->play(-1);
    aliens_in_position = false;
    stage_timer->start();
    skip_timer->start();
    skip_timer->step();
<<<<<<< HEAD

    create_ground();
    create_game_borders();
    create_cenary();
    create_aliens();
    create_guards();
    create_door_systems();
    create_papers();
    create_tables();
    create_chairs();
    create_finish_points();

    initialize_colliders();
    animation_manager::instance.set_background_color(new color(100,100,100, 125));

}

void game_scene::unload() {
    collision_manager::instance.reset_lists();
    actual_papers = 0;
    for(game_object* object: game_object_list) {
=======
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
>>>>>>> origin/Development
        free(object);
    }
    game_object_list.clear();
}

<<<<<<< HEAD
void game_scene::createtables() {
}

void game_scene::createChairs() {
}

void game_scene::create_game_borders() {
=======
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
>>>>>>> origin/Development
        for(int i=0; i<=960; i+=5) {
                game_object_list.push_back(new wall(
                    "assets/sprites/cenary/parede_cima1.png", i, HEADER_SIZE + 0, 5, 20));
                game_object_list.push_back(new wall(
                    "assets/sprites/cenary/parede_cima1.png", i, HEADER_SIZE + 595, 5, 5));
        }
        for(int j=0; j<=600; j+=5) {
                game_object_list.push_back(new wall(
                    "assets/sprites/cenary/parede_cima1.png", 955, HEADER_SIZE + j, 5, 5));
                game_object_list.push_back(new wall(
                    "assets/sprites/cenary/parede_cima1.png", 0, HEADER_SIZE + j, 5, 5));
        }
}

<<<<<<< HEAD
void game_scene::create_ground() {
=======
/**
    @brief Loads ground image.
*/

void GameScene::createGround(){
>>>>>>> origin/Development
        for(int i=0; i<=960; i+=20) {
                for(int j=0; j<=600; j+=20) {
                        game_object_list.push_back(new ground(
                            "assets/sprites/cenary/chao.png", i, HEADER_SIZE + j, 20, 20));
                }
        }
}

<<<<<<< HEAD
void game_scene::create_cenary() {
    std::ifstream tile_file;
=======
/**
    @brief Builds the game scene according to the game level.
*/

void GameScene::createCenary(){
    std::ifstream tile_file;
    assert(tile_file != NULL);
>>>>>>> origin/Development
    tile_file.open(tiled_file);
    if(tile_file.is_open()) {
        char c;
        int compare;
        for(int i=0; i<=600; i+=20) {
            for(int j=0; j<=960; j+=20) {
                tile_file.get(c);
                compare = c-48;
                switch(compare) {
                    case 1: game_object_list.push_back(new wall(
                    "assets/sprites/cenary/parede2.png", j, HEADER_SIZE + i+25, 20, 40)); 
                        break;

                    case 2: game_object_list.push_back(new wall(
                    "assets/sprites/cenary/parede_cima1.png", j+15, HEADER_SIZE + i, 0, 0));
                            game_object_list.push_back(new wall(
                    "assets/sprites/cenary/parede_cima1.png", j+15, HEADER_SIZE + i+5, 5, 15));
                            game_object_list.push_back(new wall(
                    "assets/sprites/cenary/parede_cima1.png", j+15, HEADER_SIZE + i+10, 5, 15));
                            game_object_list.push_back(new wall(
                    "assets/sprites/cenary/parede_cima1.png", j+15, HEADER_SIZE + i+15, 5, 30));
                            game_object_list.push_back(new wall(
                    "assets/sprites/cenary/parede_cima1.png", j+15, HEADER_SIZE + i-5, 0, 0));
                            game_object_list.push_back(new wall(
                    "assets/sprites/cenary/parede_cima1.png", j+15, HEADER_SIZE + i-10, 0, 0));
                            game_object_list.push_back(new wall(
                    "assets/sprites/cenary/parede_cima1.png", j+15, HEADER_SIZE + i-15, 0, 0)); 
                        break;

                    case 3: game_object_list.push_back(new wall(
                    "assets/sprites/cenary/parede_cima1.png", j, HEADER_SIZE + i+15, 5, 5));
                            game_object_list.push_back(new wall(
                    "assets/sprites/cenary/parede_cima1.png", j+5, HEADER_SIZE + i+15, 5, 5));
                            game_object_list.push_back(new wall(
                    "assets/sprites/cenary/parede_cima1.png", j+10, HEADER_SIZE + i+15, 5, 5));
                            game_object_list.push_back(new wall(
                    "assets/sprites/cenary/parede_cima1.png", j+15, HEADER_SIZE +i+15, 5, 5)); 
                        break;

                    case 4: game_object_list.push_back(new wall(
                    "assets/sprites/cenary/parede_cima1.png", j, HEADER_SIZE + i, 0, 0));
                            game_object_list.push_back(new wall(
                    "assets/sprites/cenary/parede_cima1.png", j, HEADER_SIZE + i+5, 5, 15));
                            game_object_list.push_back(new wall(
                    "assets/sprites/cenary/parede_cima1.png", j, HEADER_SIZE + i+10, 5, 15));
                            game_object_list.push_back(new wall(
                    "assets/sprites/cenary/parede_cima1.png", j, HEADER_SIZE + i+15, 5, 30));
                            game_object_list.push_back(new wall(
                    "assets/sprites/cenary/parede_cima1.png", j, HEADER_SIZE + i-5, 0, 0));
                            game_object_list.push_back(new wall(
                    "assets/sprites/cenary/parede_cima1.png", j, HEADER_SIZE + i-10, 0, 0));
                            game_object_list.push_back(new wall(
                    "assets/sprites/cenary/parede_cima1.png", j, HEADER_SIZE + i-15, 0, 0)); 
                        break;

                    case 5: game_object_list.push_back(new wall(
                    "assets/sprites/cenary/parede_door.png", j+15, HEADER_SIZE + i-20, 5, 60)); 
                        break;

                    case 6: game_object_list.push_back(new wall(
                    "assets/sprites/cenary/parede_door.png", j, HEADER_SIZE + i-20, 5, 60));
                        break;
                }
            }
        }
    }
}
