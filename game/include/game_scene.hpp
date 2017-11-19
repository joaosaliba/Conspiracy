/**Class to create, destroy and
*manipulate the scenes of the game.
*/

#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include "engine.hpp"
#include "scene.hpp"
#include "player.hpp"
#include "wall.hpp"
#include "game_object.hpp"
#include "guard.hpp"
#include "camera.hpp"
#include "progress_bar.hpp"
#include "timer.hpp"
#include "player.hpp"
#include "camera_system.hpp"

#include <fstream>
#include <vector>

#ifndef HEADER_SIZE
#define HEADER_SIZE 40
#endif

using namespace engine;

class GameScene: public Scene{
public:
    GameScene(int id, std::string new_tiled_file);
    GameScene(int id, std::string new_tiled_file, std::string music);
    ~GameScene();
protected:
    Player* player;
    Audio* background_music;
    std::vector<GameObject*> gameObjectsList;
    std::string tiled_file;
    Timer* stage_timer;
    Timer* skip_timer;
    int actual_papers;
    bool aliens_in_position;
    void initializeColliders();
    virtual void createGuards() = 0;
    virtual void createAliens() = 0;
    void createCenary();
    virtual void createDoorSystems() = 0;
    virtual void createPapers() = 0;
    virtual void createFinishPoints() = 0;
    virtual void createTables();
    void createGameBorders();
    void createGround();
    virtual void createChairs();
private:
    void load();
    void draw();
    void update(double time_elapsed);
    void unload();
    void verifyWinOrLose();
    void verifyPapers();
    void allPapersEdited();
    void aliensInPosition();
    void playerIsDead();
};

#endif
