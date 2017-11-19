#ifndef CHAIR_HPP
#define CHAIR_HPP

#include "engine.hpp"
#include "sprite.hpp"
#include "game_object.hpp"
#include "audio.hpp"
#include "timer.hpp"

using namespace engine;

class Chair: public GameObject{
public:
    Chair(std::string chair_name, double chair_position_x, double chair_position_y, int chair_width, int chair_height);
    ~Chair();


    Animation * getAnimation();
    void setMoving(bool move);
    void setDirection(std::string currentDirection);

private:
  void update(double timeElapsed);
  void draw();
    void init();
protected:
    Timer* audioTimer = nullptr;
    Audio* chairEffect = nullptr;
    Animation* animator = nullptr;
    bool isMoving; // bool variable that check if the chair are movening or not
    std::string direction;
    void moveInX(double move_chair_in_x);
    void moveInY(double move_chair_in_y);
};

#endif
