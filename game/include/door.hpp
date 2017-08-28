#ifndef DOOR_HPP
#define DOOR_HPP

#include "engine.hpp"
#include "animation.hpp"
#include "game_object.hpp"
#include "audio.hpp"

using namespace engine;

class Door: public GameObject{
public:
    Door(std::string object_name, double position_x, double position_y,
         int width, int height, std::string door_side);
    ~Door();
    void update(double time_elapsed);
    void draw();
    void init();
    animation * get_animation();
    bool is_open();
    void set_open(bool status);
    void play_effect();
    std::string get_door_side();
protected:
    animation* animator;
private:
    audio *door_effect;
    bool open;
    std::string side;
};

#endif
