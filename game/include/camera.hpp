/**
 * @file camera.hpp
 * @brief class to object of camera, where you can find some values, files,
 * others objects used in this class and methods to the same.
 * @copyright  GNU GENERAL PUBLIC LICENSE.
 */

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "engine.hpp"
#include "input_manager.hpp"
#include "animation.hpp"
#include "enemy.hpp"
#include "field_of_vision.hpp"

using namespace engine;



class Camera: public Enemy{
public:
    Camera(double camera_position_x, double camera_position_y, std::string direction);
    Camera(double camera_position_x, double camera_position_y, std::string direction, int angle_of_vision, int range, int initial_angle);
    ~Camera();
    void update(double time_elapsed);
    void draw();
    int get_range();
    void turn_off();
    bool is_turned_on();
    void set_states(int angle2, int angle3);
    void change_state(int state);
    FieldOfVision* getFieldOfVision();
private:
    void initialize_vision(int p_range, int p_angle_of_vision, std::string direction);
    void initialize_animator(std::string filename);
    int range = 0;
    bool turned_on = false;
    std::vector<int> angles;
    int angle_of_vision = 0;
    int initial_angle = 0;
    int state = 0;
    FieldOfVision* fieldOfVision = nullptr;
    Animation* animator = nullptr;
};

#endif
