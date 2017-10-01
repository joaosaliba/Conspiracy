#ifndef COLLISION_MANAGER_HPP
#define COLLISION_MANAGER_HPP

#include <vector>
#include "engine.hpp"
#include "game_object.hpp"
#include "line.hpp"
#include "field_of_vision.hpp"

using namespace engine;

class CollisionManager{
public:
    bool verifyCollisionWithWalls(GameObject* game_object);
    bool verifyCollisionWithWallsAndChairs(GameObject* game_object);
    bool verify_collision_with_guards(GameObject* game_object);
    bool verify_collision_with_cameras(GameObject* game_object);
    bool verifyCollisionWithOtherChairs(GameObject* game_object);
    GameObject* verifyCollisionWithPapers(GameObject* game_object);
    GameObject* verifyCollisionWithSwitches(GameObject* game_object);
    GameObject* verify_collision_with_cameraswitches(GameObject* game_object);
    GameObject* verifyCollisionWithCameraLevers(GameObject* game_object);
    GameObject* verify_collision_with_finish_points(GameObject* game_object);
    bool verifyCollision(GameObject* game_object_collision, GameObject* game_object_collision2);
    std::pair<std::string, GameObject *> verifyCollisionWithChairs(GameObject* game_object_collision);
    std::string verifyCollisionChair(GameObject* game_object_collision, GameObject* game_object_collision2);
    void addWall(GameObject* game_object);
    void addGuard(GameObject* game_object);
    void addPaper(GameObject* game_object);
    void addDoor(GameObject* game_object);
    void addGuardFieldOfVision(FieldOfVision* field_vision);
    void addCameraFieldOfVision(FieldOfVision* field_vision);
    void addSwitch(GameObject* game_object);
    void addChair(GameObject* game_object);
    void addCameraSwitch(GameObject* game_object);
    void addCameraLever(GameObject* game_object);
    void addFinishPoint(GameObject* game_object);
    void resetLists();
    bool verify_collision_with_guardsBody(GameObject* game_object);
    static CollisionManager instance;
private:
    double CCW(std::pair<int, int> line_a, std::pair<int, int> line_b, std::pair<int, int> line_c);
    bool verifyLineCollisionWithLine(std::pair<int, int> line_a, std::pair<int, int> line_b, std::pair<int, int> line_c, std::pair<int, int> line_d);
    bool verifyRectangleCollisionWithLine(GameObject* game_object, std::pair<int, int> line_a, std::pair<int, int> line_b);
    bool verifyCollisionWithFieldsOfVision(GameObject*game_object_collision, std::vector<FieldOfVision*> fields);
    std::vector<GameObject*> wallList;
    std::vector<GameObject*> guardList;
    std::vector<FieldOfVision*> guardsVision;
    std::vector<GameObject*> paperList;
    std::vector<FieldOfVision*> camerasVision;
    std::vector<GameObject*> doorList;
    std::vector<GameObject*> switchList;
    std::vector<GameObject*> cameraLeverList;
    std::vector<GameObject*> cameraSwitchList;
    std::vector<GameObject*> chairList;
    std::vector<GameObject*> finishPointList;
    double calculateDistance(std::pair<double,double> center,std::pair<double,double> lineCenter);
};

#endif
