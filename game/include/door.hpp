#ifndef DOOR_HPP
#define DOOR_HPP

#include "engine.hpp"
#include "animation.hpp"
#include "game_object.hpp"
#include "audio.hpp"

/** The class Door receives an GameObject public class where the parameters to be defined
*received, such as position, type, and methods. The attributes that will be defined
*public and private
*/

using namespace engine;

class Door: public GameObject {
public:
/**
 * Builder method
 * <p>This method performs the action of constructing the methods and passing the variables
 *used in class engine.hpp,animation.hpp,game_object.hpp and audio.hpp</p>
 * @param unsigned double-door_position_x
 * @param unsigned double-door_position_y
 * @param unsigned int-width
 * @param unsigned int-height
 * @param unsigned double-time_elapsed
 * @param unsigned bool-door_status
 * @param unsigned bool-is_open
 * @param unsigned bool-open
 */
    Door(std::string objectName, double door_position_x, double door_position_y,
         int width, int height, std::string doorSide);
    ~Door();
    void update(double time_elapsed);// update the door lever durign time
    void draw();// draw the lever of door
    void init();
    Animation * get_animation();
    bool is_open();
    void set_open(bool door_status);
    void play_effect();
    std::string get_door_side();
protected:
    Animation* animator;
private:
    Audio *door_effect;
    bool open;
    std::string side;
};

#endif
