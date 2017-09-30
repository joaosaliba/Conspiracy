#include "stage_three.hpp"
#include "chair.hpp"

using namespace engine;
#define PAPERQUANTITY 3
#define STAGENUMBER 3
StageThree::StageThree(int id, std::string newTiledFile) : GameScene (id, newTiledFile, "assets/sounds/TEMA3.wav"){

}

void StageThree::createGuards(){
    std::pair <std::string, int> GuardOneWayOne ("right", 600);
    std::pair <std::string, int> GuardOneWayTwo ("up", HEADER_SIZE + 30);
    std::pair <std::string, int> GuardOneWayThree ("left", 30);
    std::pair <std::string, int> GuardOneWayFour ("down", HEADER_SIZE + 180);
    std::pair <std::string, int> GuardOneWayFive ("left", 30);

    Guard * guard1 = new Guard("assets/sprites/seguranca_sheet.png", 30, HEADER_SIZE + 180, 18, 35, "right", 2, 10);
    guard1->addWay(1, GuardOneWayOne);
    guard1->addWay(2, GuardOneWayTwo);
    guard1->addWay(3, GuardOneWayThree);
    guard1->addWay(4, GuardOneWayFour);
    guard1->addWay(5, GuardOneWayFive);

    gameObjectsList.push_back(guard1);

    std::pair <std::string, int> GuardTwoWayOne ("left", 450);
    std::pair <std::string, int> GuardTwoWayTwo ("down", HEADER_SIZE + 300);
    std::pair <std::string, int> GuardTwoWayThree ("right", 640);
    std::pair <std::string, int> GuardTwoWayFour ("down", HEADER_SIZE + 300);
    std::pair <std::string, int> GuardTwoWayFive ("right", 920);
    std::pair <std::string, int> GuardTwoWaySix ("up", HEADER_SIZE + 50);
    std::pair <std::string, int> GuardTwoWaySeven ("left", 770);
    std::pair <std::string, int> GuardTwoWayEight ("up", HEADER_SIZE + 50);
    std::pair <std::string, int> GuardTwoWayNine ("left", 770);

    Guard * guard2 = new Guard("assets/sprites/seguranca_sheet.png", 750, HEADER_SIZE + 50, 18, 35, "left", 2, 10);
    guard2->addWay(1, GuardTwoWayOne);
    guard2->addWay(2, GuardTwoWayTwo);
    guard2->addWay(3, GuardTwoWayThree);
    guard2->addWay(4, GuardTwoWayFour);
    guard2->addWay(5, GuardTwoWayFive);
    guard2->addWay(6, GuardTwoWaySix);
    guard2->addWay(7, GuardTwoWaySeven);
    guard2->addWay(8, GuardTwoWayEight);
    guard2->addWay(9, GuardTwoWayNine);

    gameObjectsList.push_back(guard2);

    std::pair <std::string, int> GuardThreeWayOne ("right", 900);
    std::pair <std::string, int> GuardThreeWayTwo ("left", 300);

    Guard * guard3 = new Guard("assets/sprites/seguranca_sheet.png", 500, HEADER_SIZE + 420, 18, 35, "right", 2, 10);
    guard3->addWay(1, GuardThreeWayOne);
    guard3->addWay(2, GuardThreeWayTwo);

    gameObjectsList.push_back(guard3);

    CameraSwitch* cameraSwitch1 = new CameraSwitch(460, 460, "right");
    Camera* camera1 = new Camera(350,425,"upleft",80,220,120);
    CameraSystem* cameraSystem1 = new CameraSystem(camera1,cameraSwitch1);

    gameObjectsList.push_back(cameraSystem1);


    CameraSwitch* cameraSwitch2 = new CameraSwitch(460, 100, "right");
    Camera* camera2 = new Camera(220,70,"right",80,300,320);
    CameraSystem* cameraSystem2 = new CameraSystem(camera2,cameraSwitch2);

    gameObjectsList.push_back(cameraSystem2);
}

void StageThree::createAliens(){
    std::pair <int, int> biluPos (280, HEADER_SIZE + 560);
    std::pair <int, int> etemerPos (300, HEADER_SIZE + 560);
    std::pair <int, int> varginhaPos (575, HEADER_SIZE + 550);

    player = new Player(biluPos, etemerPos, varginhaPos, PAPERQUANTITY, STAGENUMBER);
    gameObjectsList.push_back(player);
}

void StageThree::createDoorSystems(){
    std::pair<int,int> doorOnePosition (357, HEADER_SIZE + 298);
    std::pair<int,int> switchOnePosition (880, HEADER_SIZE + 50);

    std::pair<int,int> doorTwoPosition (583, HEADER_SIZE + 178);
    std::pair<int,int> switchTwoPosition (10, HEADER_SIZE + 430);

    std::pair<int,int> doorThreePosition (700, HEADER_SIZE + 339);
    std::pair<int,int> switchThreePosition (150, HEADER_SIZE + 50);

    gameObjectsList.push_back(new DoorSystem(doorOnePosition,switchOnePosition, "LEFT"));
    gameObjectsList.push_back(new DoorSystem(doorTwoPosition,switchTwoPosition, "RIGHT"));
    gameObjectsList.push_back(new DoorSystem(doorThreePosition,switchThreePosition, "DOWN"));
}

void StageThree::createPapers(){
    gameObjectsList.push_back(new PaperTable("Paper", 30, HEADER_SIZE + 250, 60, 34));
    gameObjectsList.push_back(new PaperTable("Paper", 475, HEADER_SIZE + 170, 60, 34));
    gameObjectsList.push_back(new PaperTable("Paper", 400, HEADER_SIZE + 290, 60, 34));
}

void StageThree::createFinishPoints(){
    gameObjectsList.push_back(new FinishPoint("assets/sprites/cenary/tapete_lateral.png", 940, 260, 34, 34, "EBV"));
}

void StageThree::createChairs(){
    gameObjectsList.push_back(new Chair("assets/sprites/cadeira_sheet(20X27).png", 300, HEADER_SIZE + 480, 20, 16));
    gameObjectsList.push_back(new Chair("assets/sprites/cadeira_sheet(20X27).png", 750, HEADER_SIZE + 120, 20, 16));
}
