#ifndef PAPER_TABLE_HPP
#define PAPER_TABLE_HPP

#include "engine.hpp"
#include "animation.hpp"
#include "game_object.hpp"
#include "table.hpp"
#include "paper.hpp"


using namespace engine;

class PaperTable: public GameObject{
public:
    PaperTable(std::string object_name, double position_x, double position_y, int width, int height);
    ~PaperTable();
    void update(double time_elapsed);
    void draw();
    void init();
    Animation * get_animation();
    Paper * get_paper();
    Table* get_table();
protected:
    animation* animator;
    paper* paper;
    table* table;
};

#endif
