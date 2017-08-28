#ifndef STAGE_TWO_HPP
#define STAGE_TWO_HPP

#include "engine.hpp"
#include "game_scene.hpp"
#include "player.hpp"
#include "wall.hpp"
#include "game_object.hpp"
#include "guard.hpp"
#include "paper_table.hpp"
#include "camera.hpp"
#include "door_system.hpp"
#include "finish_point.hpp"
#include <typeinfo>

class stage_two: public game_scene {
public:
    stage_two(int id, std::string new_tiled_file);
private:
    void create_guards();
    void create_aliens();
    void create_door_systems();
    void create_papers();
    void create_finish_points();
};

#endif
