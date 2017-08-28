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

class game_scene: public scene {
public:
    game_scene(int id, std::string new_tiled_file);
    game_scene(int id, std::string new_tiled_file, std::string music);
    ~game_scene();
    void load();
    void draw();
    void update(double time_elapsed);
    void unload();
    void verify_win_or_lose();
protected:
    Player* player;
    audio* background_music;
    std::vector<game_object*> game_objects_list;
    std::string tiled_file;
    timer* stage_timer;
    timer* skip_timer;
    int actual_papers;
    bool aliens_in_position;
    void initialize_colliders();
    virtual void create_guards() = 0;
    virtual void create_aliens() = 0;
    void create_cenary();
    virtual void create_door_systems() = 0;
    virtual void create_papers() = 0;
    virtual void create_finish_points() = 0;
    virtual void create_tables();
    void create_game_borders();
    void create_ground();
    virtual void create_chairs();
};

#endif
