#ifndef FINISH_POINT_HPP
#define FINISH_POINT_HPP

#include "game_object.hpp"
#include "animation.hpp"

using namespace engine;

class FinishPoint: public GameObject{
public:
    FinishPoint(std::string objectName, double position_x, double position_y,int width, int height, std::string alienNames);
    void update(double time_elapsed);
    void draw();
    std::string get_alien_names();
private:
    std::string aliens;
    std::string orientation;
    Animation* animator;
    Animation* biluAnim;
    Animation* etemerAnim;
    Animation* varginhaAnim;
};

#endif
