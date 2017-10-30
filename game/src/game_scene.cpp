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

#define DEAD_TIME 2500
#define WIN_TIME 500
#define COMPARE_CONSTANT 48
#define POSITION_CONST 15
#define WALL_POSITION_CONST 10

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

    //Verifies if tha audio file is TEMA3.wav and it assigns a background music
    if(audio_file == "assets/sounds/TEMA3.wav"){
        background_music = new Audio(audio_file, "MUSIC", 55);
        assert(background_music != NULL);
    //Assigns a default background music
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
        //For each game object detected it draws
        for(auto gameObject : gameObjectsList) {
                (*gameObject).draw();
        }
}

/**
    @brief Dismantle player game object.
*/

void GameScene::update(double time_elapsed){
    assert(time_elapsed != NULL);
    //It verifies if the player is dead to update scene
    if(!player->isDead()){
        //For each game object detected
        for(auto gameObject : gameObjectsList) {
                //Updates time elapsed
                if(typeid(gameObject) != typeid(Player)){
                    (*gameObject).update(time_elapsed);
                }else {
                    //nothing to do
                }
        }
    //Verifies conditions of winning
    }else {
    verifyWinOrLose();
    }
}

/**
    @brief Verifies number of papers
*/

void GameScene::verifyPapers(){

    //For each game object detected
    for(auto gameObject : gameObjectsList) {
          //If verifies if the game object is a guard
          std::vector<Guard *> guards;
          if(typeid(*gameObject) == typeid(Guard)) {
                  guards.push_back((Guard *)(gameObject));
          //Verifies if the game object is a paper
          }else if(typeid(*gameObject) == typeid(PaperTable)) {
                  //Verifies if all papers are edited
                  bool all_papers_edited = true;
                  (void)all_papers_edited;
                  if(!(((PaperTable*)(gameObject))->getPaper())->isEdited()) {
                      all_papers_edited = false;
                  //All papers are edited
                  }else{
                      int count_papers = 0;
                      count_papers++;
                  }
          }else {
            //nothing to do
          }
    }
}

/**
    @brief Verifies if the papers were edited
*/

void GameScene::allPapersEdited(){
  int count_papers = 0;
  //Verifies if the number of papers edited is equal to the actual number of papers
  if(count_papers >= actual_papers) {
      player->updatePaperQuantity(count_papers);
      actual_papers = count_papers;

  //All papers were edited
  }else {
      actual_papers = count_papers;
  }
}

void GameScene::aliensInPosition(){
  //Verifies if all aliens are in position at the end of the stage
  if((Etemer *)(player->getEtemer())->isInPosition() &&
    (Bilu*)(player->getBilu())->isInPosition() &&
    (Varginha*)(player->getVarginha())->isInPosition()) {
        aliens_in_position = true;

    //Aliens are not in position
    }else {
        aliens_in_position = false;
    }
}

void GameScene::playerIsDead(){
    //If the player is dead it stops the stage timer
    if(!player->isDead()) {
        stage_timer->step();
    }else{
        //nothing to do Player is alive
    }
    bool all_papers_edited = true;
    //If player is dead it reloads stage
    if(player->isDead()) {
        if(stage_timer->elapsed_time() >= DEAD_TIME){
            getSceneManager()->loadScene(6);
        }else {
          //nothing to do
    }

    //Verifies winning conditions
    }else if((all_papers_edited && aliens_in_position) || (InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_K) && skip_timer->total_elapsed_time() >= WIN_TIME)){
        //Loads winning scene
        if(getSceneManager()->get_current_scene_id() == 5){
            getSceneManager()->loadScene(9);
        //Loads losing scene
        }else{
            getSceneManager()->loadScene(7);
        }
    }else {
        //nothing to do
    }
}
/**
    @brief It vefifies if the player has won or lost the game.
*/

void GameScene::verifyWinOrLose(){
        assert(guards != NULL);
        assert(all_papers_edited != NULL);
        assert(count_papers != NULL);

        verifyPapers();
        allPapersEdited();
        aliensInPosition();
        playerIsDead();

        std::vector<Guard *> guards;
        //Verifies if the aliens were detected
        for(Guard * guard : guards) {
            guard->verifyDistance(player->getVarginha());
            guard->verifyDistance(player->getBilu());
            ((Etemer *)(player->getEtemer()))->verifyDistance(guard);
        }
  }

/**
    @brief It starts the game collider.
*/

void GameScene::initializeColliders(){
    assert(gameObjectsList != NULL);
    //For each game object detected
    for(auto gameObject: gameObjectsList){
        //If obejct id equals to wall id it adds a wall
        if(typeid(*gameObject) == typeid(Wall)){
            CollisionManager::instance.addWall(gameObject);
        //If object id equals to guard id it add a guard and the respective field of view of this guard
        }else if(typeid(*gameObject) == typeid(Guard)){
            CollisionManager::instance.addGuard(gameObject);
            CollisionManager::instance.addGuardFieldOfVision(((Guard*)gameObject)->getFieldOfVision());
        //If the object id equals to camera id it adds camera
        }else if(typeid(*gameObject) == typeid(CameraSystem)){
            CollisionManager::instance.addCameraFieldOfVision(((CameraSystem*)gameObject)->getCamera()->getFieldOfVision());
            CollisionManager::instance.addCameraSwitch(((CameraSystem*)gameObject)->getCameraSwitch());
            CollisionManager::instance.addCameraLever(((CameraSystem*)gameObject)->getCameraLever());
        //If the object id equals to PaperTable id it adds one
        }else if(typeid(*gameObject) == typeid(PaperTable)){
            CollisionManager::instance.addPaper(((PaperTable*)(gameObject))->getPaper());
            CollisionManager::instance.addWall(((PaperTable*)(gameObject))->getTable());
        //Adds door
        }else if(typeid(*gameObject) == typeid(DoorSystem)){
            CollisionManager::instance.addDoor(((DoorSystem*)(gameObject))->getDoor());
            CollisionManager::instance.addSwitch(((DoorSystem*)(gameObject))->getSwitch());
            CollisionManager::instance.addWall(((DoorSystem*)(gameObject))->getTable());
        //Adds table
        }else if(typeid(*gameObject) == typeid(Table)){
            CollisionManager::instance.addWall(((Table*)(gameObject)));
        //Adds chair
        }else if(typeid(*gameObject) == typeid(Chair)) {
            CollisionManager::instance.addChair(gameObject);
        //Adds finish point
        }else if(typeid(*gameObject) == typeid(FinishPoint)){
            CollisionManager::instance.addFinishPoint(gameObject);
        }else {
          //nothing to do
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
    assert(actual_papers != NULL);
    //For each game object detected
    for(GameObject* object: gameObjectsList){
        free(object);
    }
    actual_papers = 0;
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
        int compare = 0;
        for(int i=0; i<=600; i+=20) {
            for(int j=0; j<=960; j+=20) {
                tile_file.get(c);
                compare = c-COMPARE_CONSTANT;
                switch(compare) {
                    case 1: gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede2.png", j, HEADER_SIZE + i+25, 20, 40)); break;

                    case 2: gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j+POSITION_CONST, HEADER_SIZE + i, 0, 0));
                            gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j+POSITION_CONST, HEADER_SIZE + i+5, 5, 15));
                            gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j+POSITION_CONST, HEADER_SIZE + i+WALL_POSITION_CONST, 5, 15));
                            gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j+POSITION_CONST, HEADER_SIZE + i+POSITION_CONST, 5, 30));
                            gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j+POSITION_CONST, HEADER_SIZE + i-5, 0, 0));
                            gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j+POSITION_CONST, HEADER_SIZE + i-WALL_POSITION_CONST, 0, 0));
                            gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j+POSITION_CONST, HEADER_SIZE + i-POSITION_CONST, 0, 0)); break;

                    case 3: gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j, HEADER_SIZE + i+POSITION_CONST, 5, 5));
                            gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j+5, HEADER_SIZE + i+POSITION_CONST, 5, 5));
                            gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j+WALL_POSITION_CONST, HEADER_SIZE + i+POSITION_CONST, 5, 5));
                            gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j+POSITION_CONST, HEADER_SIZE +i+POSITION_CONST, 5, 5)); break;

                    case 4: gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j, HEADER_SIZE + i, 0, 0));
                            gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j, HEADER_SIZE + i+5, 5, 15));
                            gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j, HEADER_SIZE + i+WALL_POSITION_CONST, 5, 15));
                            gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j, HEADER_SIZE + i+POSITION_CONST, 5, 30));
                            gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j, HEADER_SIZE + i-5, 0, 0));
                            gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j, HEADER_SIZE + i-WALL_POSITION_CONST, 0, 0));
                            gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", j, HEADER_SIZE + i-POSITION_CONST, 0, 0)); break;

                    case 5: gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_door.png", j+POSITION_CONST, HEADER_SIZE + i-20, 5, 60)); break;

                    case 6: gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_door.png", j, HEADER_SIZE + i-20, 5, 60));break;

                    default:
                            //nothing to do
                            break;
                }
            }
        }
    }else {
      ERROR("Failed to open tiled file");
    }
  }
