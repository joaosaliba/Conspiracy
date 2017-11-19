#ifndef TABLE_HPP
#define TABLE_HPP

#include "engine.hpp"
#include "sprite.hpp"
#include "game_object.hpp"

using namespace engine;

class Table: public GameObject{
public:
    Table(std::string objectName, double position_x, double position_y, int width, int height);
    ~Table();
    void update(double time_elapsed);
    void draw();
    void init();
    Animation * getAnimation();
protected:
    Animation* animator;
};

#endif
