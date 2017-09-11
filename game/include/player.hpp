/**class to object of player, where you can find some objects, files, variables and meths
 *used to the same.
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "alien.hpp"
#include "alien_bilu.hpp"
#include "alien_etemer.hpp"
#include "alien_varginha.hpp"
#include "input_manager.hpp"
#include "audio.hpp"
#include "engine.hpp"
#include "header.hpp"

using namespace engine;

class Player: public GameObject {
public:
    Player(std::pair<int, int> bilu_position, std::pair<int, int> etemer_position,
          std::pair<int,int> varginha_position, int paper_quantity, int stage_number);
    ~Player();
    void update(double time_elapsed);
    void draw();
    bool is_dead();
    Alien * get_bilu();
    Alien * get_varginha();
    Alien * get_etemer();
    void update_paper_quantity(int new_value);
private:
    Animation* exclamation_animation;
    Alien *bilu, *varginha, *etemer;
    Audio *varginha_sound_effect, *etemer_sound_effect, *bilu_sound_effect;
    Header * header;
    int selected_alien;
    void idle_animation(Alien * alien);
    void wait_animation(int before_alien);
};
#endif
