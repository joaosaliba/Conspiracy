#include "stage_two.hpp"

using namespace engine;

#define PAPERQUANTITY 3
#define STAGENUMBER 2

stage_two::stage_two(int id, std::string new_tiled_file) :
game_scene (id, new_tiled_file, "assets/sounds/TEMA2.wav") {

}

void stage_two::create_guards() {
    std::pair <std::string, int> way_one_1 ("right", 300);
    std::pair <std::string, int> way_two_1 ("up", HEADER_SIZE + 30);
    std::pair <std::string, int> way_three_1 ("left", 20);
    std::pair <std::string, int> way_four_1 ("down", HEADER_SIZE + 120);
    std::pair <std::string, int> way_five_1 ("right", 300);

    guard * guard_1 = new guard(
        "assets/sprites/seguranca_sheet.png", 20, HEADER_SIZE + 120, 18, 35, "right", 2, 10);
    guard_1->add_way(1, way_one_1);
    guard_1->add_way(2, way_two_1);
    guard_1->add_way(3, way_three_1);
    guard_1->add_way(4, way_four_1);
    guard_1->add_way(5, way_five_1);

    game_objects_list.push_back(guard_1);

    std::pair <std::string, int> way_one_2 ("left", 700);
    std::pair <std::string, int> way_two_2 ("down", HEADER_SIZE + 400);
    std::pair <std::string, int> way_three_2 ("right", 920);
    std::pair <std::string, int> way_four_2 ("up", HEADER_SIZE + 200);
    std::pair <std::string, int> way_five_2 ("left", 750);
    std::pair <std::string, int> way_six_2 ("up", HEADER_SIZE + 50);

    guard * guard_2 = new guard(
        "assets/sprites/seguranca_sheet.png", 750, HEADER_SIZE + 50, 18, 35, "down", 2, 10);
    guard_2->add_way(1, way_one_2);
    guard_2->add_way(2, way_two_2);
    guard_2->add_way(3, way_three_2);
    guard_2->add_way(4, way_four_2);
    guard_2->add_way(5, way_five_2);
    guard_2->add_way(6, way_six_2);

    game_objects_list.push_back(guard_2);

    std::pair <std::string, int> way_one_3 ("down", HEADER_SIZE + 430);
    std::pair <std::string, int> way_two_3 ("left", 300);
    std::pair <std::string, int> way_three_3 ("down", HEADER_SIZE + 500);
    std::pair <std::string, int> way_four_3 ("right", 650);
    std::pair <std::string, int> way_five_3 ("up", HEADER_SIZE + 300);
    std::pair <std::string, int> way_six_3 ("left", 520);
    std::pair <std::string, int> way_seven_3 ("up", HEADER_SIZE + 210);
    std::pair <std::string, int> way_eight_3 ("right", 650);
    std::pair <std::string, int> way_nine_3 ("down", HEADER_SIZE + 350);
    std::pair <std::string, int> way_ten_3 ("left", 300);
    std::pair <std::string, int> way_eleven_3 ("up", HEADER_SIZE + 210);
    std::pair <std::string, int> way_twelve_3 ("right", 505);
    std::pair <std::string, int> way_thirteen_3 ("down", HEADER_SIZE + 210);


    guard * guard_3 = new guard(
        "assets/sprites/seguranca_sheet.png", 500, HEADER_SIZE + 200, 18, 35, "down", 2, 10);
    guard_3->add_way(1, way_one_3);
    guard_3->add_way(2, way_two_3);
    guard_3->add_way(3, way_three_3);
    guard_3->add_way(4, way_four_3);
    guard_3->add_way(5, way_five_3);
    guard_3->add_way(6, way_six_3);
    guard_3->add_way(7, way_seven_3);
    guard_3->add_way(8, way_eight_3);
    guard_3->add_way(9, way_nine_3);
    guard_3->add_way(10, way_ten_3);
    guard_3->add_way(11, way_eleven_3);
    guard_3->add_way(12, way_twelve_3);
    guard_3->add_way(13, way_thirteen_3);


    game_objects_list.push_back(guard_3);

    camera_switch* camera_switch_1 = new camera_switch(660, 500, "right");
    camera* camera_1 = new camera(680,510,"right");
    camera_system* camera_system_1 = new camera_system(camera_1,camera_switch_1);

    game_objects_list.push_back(camera_system_1);


    camera_switch* camera_switch2 = new camera_switch(942, 150, "right");
    camera* camera_2 = new camera(942,250,"left", 80, 180, 200);

    camera_system* camera_system2 = new camera_system(camera_2,camera_switch2);

    game_objects_list.push_back(camera_system2);
}

void stage_two::create_aliens() {
    std::pair <int, int> bilu_pos (880, HEADER_SIZE + 550);
    std::pair <int, int> etemer_pos (900, HEADER_SIZE + 550);
    std::pair <int, int> varginha_pos (920, HEADER_SIZE + 550);

    player = new Player(bilu_pos, etemer_pos, varginha_pos, PAPERQUANTITY, STAGENUMBER);
    game_objects_list.push_back(player);
}

void stage_two::create_door_systems() {
    std::pair<int,int> door_one_position (163, HEADER_SIZE + 257);
    std::pair<int,int> switch_one_position (610, HEADER_SIZE + 50);

    std::pair<int,int> door_two_position (163, HEADER_SIZE + 497);
    std::pair<int,int> switch_two_position (800, HEADER_SIZE + 50);

    game_objects_list.push_back(new door_system(door_one_position,switch_one_position, "RIGHT"));
    game_objects_list.push_back(new door_system(door_two_position,switch_two_position, "RIGHT"));
}

void stage_two::create_papers() {
    game_objects_list.push_back(new paper_table("Paper", 30, HEADER_SIZE + 250, 60, 34));
    game_objects_list.push_back(new paper_table("Paper", 350, HEADER_SIZE + 170, 60, 34));
    game_objects_list.push_back(new paper_table("Paper", 30, HEADER_SIZE + 490, 60, 34));
}

void stage_two::create_finish_points() {
    game_objects_list.push_back(new finish_point("assets/sprites/cenary/tapete.png", 550, 100, 34, 34, "EB"));
    game_objects_list.push_back(new finish_point("assets/sprites/cenary/tapete.png", 250, 45, 34, 34, "V"));
}
