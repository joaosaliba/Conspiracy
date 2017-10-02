/**
 * @file finish_point.cpp
 * @brief class to object of finish_point, where you can find some values, files,
 * others objects used in this class and methods to the same.
 * @copyright  GNU GENERAL PUBLIC LICENSE.
 */

#include "finish_point.hpp"
#include <assert.h>

//#define NDEBUG *uncomment to disable assertions

FinishPoint::FinishPoint(std::string object_name, double position_x,
                                                 double position_y,
                                                 int width,
                                                 int height,
                                                 std::string alien_names): GameObject(object_name,
                                                                                     position_x,
                                                                                     position_y,
                                                                                     width,
                                                                                     height){
    aliens = alien_names;
    if(object_name.compare("assets/sprites/cenary/tapete.png") == 0) {
        animator = new Animation(object_name, 2, 1, 0.5);
        orientation = "UPDOWN";
    }else {
        animator = new Animation(object_name, 1, 2, 0.5);
        orientation = "LEFTRIGHT";
    }
    etemer_anim = new Animation("assets/sprites/cenary/SAIDA_TEMER.png", 1, 1, 0.5);
    bilu_anim = new Animation("assets/sprites/cenary/SAIDA_BILU.png", 1, 1, 0.5);
    varginha_anim = new Animation("assets/sprites/cenary/SAIDA_VARGINHA.png", 1, 1, 0.5);
}

void FinishPoint::update(double time_elapsed) {
    time_elapsed = time_elapsed;
    animator->update();
    bilu_anim->update();
    etemer_anim->update();
    varginha_anim->update();
}

std::string FinishPoint::get_alien_names() {
    return aliens;
}

void FinishPoint::draw() {
    animator->draw_instant(get_position_x(), get_position_y());

    if(orientation.compare("UPDOWN") == 0) {
        if(aliens.compare("EBV") == 0) {
            etemer_anim->draw_instant(get_position_x()+1, get_position_y()+3.5);
            bilu_anim->draw_instant(get_position_x()+12, get_position_y()+3.5);
            varginha_anim->draw_instant(get_position_x()+23, get_position_y()+3.5);
        }else if(aliens.compare("EB") == 0) {
            etemer_anim->draw_instant(get_position_x()+1, get_position_y()+3.5);
            bilu_anim->draw_instant(get_position_x()+23, get_position_y()+3.5);
        }else if(aliens.compare("BV") == 0) {
            bilu_anim->draw_instant(get_position_x()+1, get_position_y()+3.5);
            varginha_anim->draw_instant(get_position_x()+23, get_position_y()+3.5);
        }else if(aliens.compare("EV") == 0) {
            etemer_anim->draw_instant(get_position_x()+1, get_position_y()+3.5);
            varginha_anim->draw_instant(get_position_x()+23, get_position_y()+3.5);
        }else if(aliens.compare("E") == 0) {
            etemer_anim->draw_instant(get_position_x()+12, get_position_y()+3.5);
        }else if(aliens.compare("B") == 0) {
            bilu_anim->draw_instant(get_position_x()+12, get_position_y()+3.5);
        }else if(aliens.compare("V") == 0) {
            varginha_anim->draw_instant(get_position_x()+12, get_position_y()+3.5);
        }
    }else {
        if(aliens.compare("EBV") == 0) {
            etemer_anim->draw_instant(get_position_x()+3.5, get_position_y()+1);
            bilu_anim->draw_instant(get_position_x()+3.5, get_position_y()+12);
            varginha_anim->draw_instant(get_position_x()+3.5, get_position_y()+23);
        }else if(aliens.compare("EB") == 0) {
            etemer_anim->draw_instant(get_position_x()+3.5, get_position_y()+1);
            bilu_anim->draw_instant(get_position_x()+3.5, get_position_y()+23);
        }else if(aliens.compare("BV") == 0) {
            bilu_anim->draw_instant(get_position_x()+3.5, get_position_y()+1);
            varginha_anim->draw_instant(get_position_x()+2, get_position_y()+23);
        }else if(aliens.compare("EV") == 0) {
            etemer_anim->draw_instant(get_position_x()+3.5, get_position_y()+1);
            varginha_anim->draw_instant(get_position_x()+3.5, get_position_y()+23);
        }else if(aliens.compare("E") == 0) {
            etemer_anim->draw_instant(get_position_x()+3.5, get_position_y()+12);
        }else if(aliens.compare("B") == 0) {
            bilu_anim->draw_instant(get_position_x()+3.5, get_position_y()+12);
        }else if(aliens.compare("V") == 0) {
            varginha_anim->draw_instant(get_position_x()+3.5, get_position_y()+12);
        }else {
          //nothing to do
        }
    }
}
