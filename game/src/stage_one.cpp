#include "stage_one.hpp"

using namespace engine;

#define PAPERQUANTITY 2
#define STAGENUMBER 1
StageOne::StageOne(int id, std::string new_tiled_file) : GameScene (id, new_tiled_file, "assets/sounds/TEMA1.wav"){

}

void StageOne::create_guards() {
    std::pair <std::string, int> way_one1 ("right", 470);
    std::pair <std::string, int> way_two1 ("up", HEADER_SIZE + 30);
    std::pair <std::string, int> way_three1 ("left", 220);
    std::pair <std::string, int> way_four1 ("down", HEADER_SIZE + 120);
    std::pair <std::string, int> way_five1 ("right", 470);

    guard * guard1 = new Guard("assets/sprites/seguranca_sheet.png", 220, HEADER_SIZE + 120, 18, 35, "right", 2, 15);
    guard1->add_way(1, way_one1);
    guard1->add_way(2, way_two1);
    guard1->add_way(3, way_three1);
    guard1->add_way(4, way_four1);
    guard1->add_way(5, way_five1);

    game_objects_list.push_back(guard1);

    std::pair <std::string, int> way_one2 ("right", 920);
    std::pair <std::string, int> way_two2 ("down", HEADER_SIZE + 550);
    std::pair <std::string, int> way_three2 ("left", 860);
    std::pair <std::string, int> way_four2 ("up", HEADER_SIZE + 50);
    std::pair <std::string, int> way_five2 ("right", 880);
    std::pair <std::string, int> way_six2 ("down", HEADER_SIZE + 550);

    guard * guard2 = new Guard("assets/sprites/seguranca_sheet.png", 880, HEADER_SIZE + 50, 18, 35, "down", 2, 15);
    guard2->add_way(1, way_one2);
    guard2->add_way(2, way_two2);
    guard2->add_way(3, way_three2);
    guard2->add_way(4, way_four2);

    guard2->add_way(5, way_one2);
    guard2->add_way(6, way_two2);
    guard2->add_way(7, way_three2);
    guard2->add_way(8, way_four2);
    guard2->add_way(9, way_five2);
    guard2->add_way(10, way_six2);

    game_objects_list.push_back(guard2);

}

void StageOne::create_aliens() {
    std::pair <int, int> bilu_pos (10, HEADER_SIZE + 500);
    std::pair <int, int> etemer_pos (30, HEADER_SIZE + 510);
    std::pair <int, int> varginha_pos (50, HEADER_SIZE + 500);

    player = new Player(bilu_pos, etemer_pos, varginha_pos, PAPERQUANTITY, STAGENUMBER);

    game_objects_list.push_back(player);
}

void StageOne::create_door_systems() {
    std::pair<int,int> door_one_position (323, HEADER_SIZE + 220);
    std::pair<int,int> switch_one_position (60, HEADER_SIZE + 50);


    std::pair<int,int> door_two_position (660, HEADER_SIZE + 381);
    std::pair<int,int> switch_two_position (650, HEADER_SIZE + 50);

    game_objects_list.push_back(new door_system(door_one_position,switch_one_position, "RIGHT"));
    game_objects_list.push_back(new door_system(door_two_position,switch_two_position, "DOWN"));
}

void StageOne::create_papers() {
    game_objects_list.push_back(new paper_table("Paper", 100, HEADER_SIZE + 200, 60, 34));
    game_objects_list.push_back(new paper_table("Paper", 600, HEADER_SIZE + 220, 60, 34));
}

void StageOne::create_finish_points() {
    game_objects_list.push_back(new finish_point("assets/sprites/cenary/tapete.png", 550, 100, 34, 34, "EBV"));
}
