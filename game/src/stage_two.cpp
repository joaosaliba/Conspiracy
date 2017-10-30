#include "stage_two.hpp"

using namespace engine;
#define PAPERQUANTITY 3
#define STAGENUMBER 2
#define GUARD_PATH 300
#define GUARD_PATH2 700
#define GUARD_PATH3 750
#define GUARD_PATH4 650

StageTwo::StageTwo(int id, std::string newTiledFile) : GameScene (id, newTiledFile, "assets/sounds/TEMA2.wav"){

}


void StageTwo::createGuards(){

    Guard * guard1 = new Guard("assets/sprites/seguranca_sheet.png", 20, HEADER_SIZE + 120, 18, 35, "right", 2, 10);

    std::pair <std::string, int> GuardOneWayOne ("right", GUARD_PATH);
    std::pair <std::string, int> GuardOneWayTwo ("up", HEADER_SIZE + 30);
    std::pair <std::string, int> GuardOneWayThree ("left", 20);
    std::pair <std::string, int> GuardOneWayFour ("down", HEADER_SIZE + 120);
    std::pair <std::string, int> GuardOneWayFive ("right", GUARD_PATH);
    guard1->addWay(1, GuardOneWayOne);
    guard1->addWay(2, GuardOneWayTwo);
    guard1->addWay(3, GuardOneWayThree);
    guard1->addWay(4, GuardOneWayFour);
    guard1->addWay(5, GuardOneWayFive);

    gameObjectsList.push_back(guard1);


    Guard * guard2 = new Guard("assets/sprites/seguranca_sheet.png", GUARD_PATH3, HEADER_SIZE + 50, 18, 35, "down", 2, 10);

    std::pair <std::string, int> GuardTwoWayOne ("left", GUARD_PATH2);
    std::pair <std::string, int> GuardTwoWayTwo ("down", HEADER_SIZE + 400);
    std::pair <std::string, int> GuardTwoWayThree ("right", 920);
    std::pair <std::string, int> GuardTwoWayFour ("up", HEADER_SIZE + 200);
    std::pair <std::string, int> GuardTwoWayFive ("left", GUARD_PATH3);
    std::pair <std::string, int> GuardTwoWaySix ("up", HEADER_SIZE + 50);
    guard2->addWay(1, GuardTwoWayOne);
    guard2->addWay(2, GuardTwoWayTwo);
    guard2->addWay(3, GuardTwoWayThree);
    guard2->addWay(4, GuardTwoWayFour);
    guard2->addWay(5, GuardTwoWayFive);
    guard2->addWay(6, GuardTwoWaySix);

    gameObjectsList.push_back(guard2);

    Guard * guard3 = new Guard("assets/sprites/seguranca_sheet.png", 500, HEADER_SIZE + 200, 18, 35, "down", 2, 10);

    std::pair <std::string, int> GuardThreeWayOne ("down", HEADER_SIZE + 430);
    std::pair <std::string, int> GuardThreeWayTwo ("left", GUARD_PATH);
    std::pair <std::string, int> GuardThreeWayThree ("down", HEADER_SIZE + 500);
    std::pair <std::string, int> GuardThreeWayFour ("right", GUARD_PATH4);
    std::pair <std::string, int> GuardThreeWayFive ("up", HEADER_SIZE + GUARD_PATH);
    std::pair <std::string, int> GuardThreeWaySix ("left", 520);
    std::pair <std::string, int> GuardThreeWaySeven ("up", HEADER_SIZE + 210);
    std::pair <std::string, int> GuardThreeWayEight ("right", GUARD_PATH4);
    std::pair <std::string, int> GuardThreeWayNine ("down", HEADER_SIZE + 350);
    std::pair <std::string, int> GuardThreeWayTen ("left", GUARD_PATH);
    std::pair <std::string, int> GuardThreeWayEleven ("up", HEADER_SIZE + 210);
    std::pair <std::string, int> GuardThreeWayTwelve ("right", 505);
    std::pair <std::string, int> GuardThreeWayThirteen ("down", HEADER_SIZE + 210);

    guard3->addWay(1, GuardThreeWayOne);
    guard3->addWay(2, GuardThreeWayTwo);
    guard3->addWay(3, GuardThreeWayThree);
    guard3->addWay(4, GuardThreeWayFour);
    guard3->addWay(5, GuardThreeWayFive);
    guard3->addWay(6, GuardThreeWaySix);
    guard3->addWay(7, GuardThreeWaySeven);
    guard3->addWay(8, GuardThreeWayEight);
    guard3->addWay(9, GuardThreeWayNine);
    guard3->addWay(10, GuardThreeWayTen);
    guard3->addWay(11, GuardThreeWayEleven);
    guard3->addWay(12, GuardThreeWayTwelve);
    guard3->addWay(13, GuardThreeWayThirteen);

    gameObjectsList.push_back(guard3);


    CameraSwitch* cameraSwitch1 = new CameraSwitch(660, 500, "right");
    Camera* camera1 = new Camera(680,510,"right");
    CameraSystem* cameraSystem1 = new CameraSystem(camera1,cameraSwitch1);

    gameObjectsList.push_back(cameraSystem1);


    CameraSwitch* cameraSwitch2 = new CameraSwitch(942, 150, "right");
    Camera* camera2 = new Camera(942,250,"left", 80, 180, 200);

    CameraSystem* cameraSystem2 = new CameraSystem(camera2,cameraSwitch2);

    gameObjectsList.push_back(cameraSystem2);
}

void StageTwo::createAliens(){
    std::pair <int, int> biluPos (880, HEADER_SIZE + 550);
    std::pair <int, int> etemerPos (900, HEADER_SIZE + 550);
    std::pair <int, int> varginhaPos (920, HEADER_SIZE + 550);

    player = new Player(biluPos, etemerPos, varginhaPos, PAPERQUANTITY, STAGENUMBER);
    gameObjectsList.push_back(player);
}

void StageTwo::createDoorSystems(){
    std::pair<int,int> doorOnePosition (163, HEADER_SIZE + 257);
    std::pair<int,int> switchOnePosition (610, HEADER_SIZE + 50);

    std::pair<int,int> doorTwoPosition (163, HEADER_SIZE + 497);
    std::pair<int,int> switchTwoPosition (800, HEADER_SIZE + 50);

    gameObjectsList.push_back(new DoorSystem(doorOnePosition,switchOnePosition, "RIGHT"));
    gameObjectsList.push_back(new DoorSystem(doorTwoPosition,switchTwoPosition, "RIGHT"));
}

void StageTwo::createPapers(){
    gameObjectsList.push_back(new PaperTable("Paper", 30, HEADER_SIZE + 250, 60, 34));
    gameObjectsList.push_back(new PaperTable("Paper", 350, HEADER_SIZE + 170, 60, 34));
    gameObjectsList.push_back(new PaperTable("Paper", 30, HEADER_SIZE + 490, 60, 34));
}

void StageTwo::createFinishPoints(){
    gameObjectsList.push_back(new FinishPoint("assets/sprites/cenary/tapete.png", 550, 100, 34, 34, "EB"));
    gameObjectsList.push_back(new FinishPoint("assets/sprites/cenary/tapete.png", 250, 45, 34, 34, "V"));
}
