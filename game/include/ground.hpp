#ifndef GROUND_HPP
#define GROUND_HPP

#include "animation.hpp"
#include "game_object.hpp"

using namespace engine;

class Ground: public GameObject{
public:
    Ground(std::string object_name, double position_x, double position_y, int width, int height);
    ~Ground();

    void init();
    Animation * getAnimation();
private:
  void update(double time_elapsed);
  void draw();
    Animation* animator;
};
#endif
