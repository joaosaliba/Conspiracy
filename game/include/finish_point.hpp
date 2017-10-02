/**
 * @file finish_point.hpp
 * @brief class to object of finish_point, where you can find some values, files,
 * others objects used in this class and methods to the same.
 * @copyright  GNU GENERAL PUBLIC LICENSE.
 */

#ifndef FINISH_POINT_HPP
#define FINISH_POINT_HPP

#include "game_object.hpp"
#include "animation.hpp"



using namespace engine;

class FinishPoint: public GameObject{
public:
    FinishPoint(std::string objectName, double position_x, double position_y,int width, int height, std::string alien_names);
    void update(double time_elapsed);
    void draw();
    std::string get_alien_names();
private:
    std::string aliens;
    std::string orientation;
    Animation* animator;
    Animation* bilu_anim;
    Animation* etemer_anim;
    Animation* varginha_anim;
};

#endif
