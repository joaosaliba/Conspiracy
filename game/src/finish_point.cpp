#include "finish_point.hpp"

FinishPoint::FinishPoint(std::string objectName, double position_x,
                                                 double position_y,
                                                 int width,
                                                 int height,
                                                 std::string alienNames): GameObject(objectName,
                                                                                     position_x,
                                                                                     position_y,
                                                                                     width,
                                                                                     height){
    aliens = alienNames;
    if(objectName.compare("assets/sprites/cenary/tapete.png") == 0){
        animator = new Animation(objectName, 2, 1, 0.5);
        orientation = "UPDOWN";
    }else{
        animator = new Animation(objectName, 1, 2, 0.5);
        orientation = "LEFTRIGHT";
    }
    etemerAnim = new Animation("assets/sprites/cenary/SAIDA_TEMER.png", 1, 1, 0.5);
    biluAnim = new Animation("assets/sprites/cenary/SAIDA_BILU.png", 1, 1, 0.5);
    varginhaAnim = new Animation("assets/sprites/cenary/SAIDA_VARGINHA.png", 1, 1, 0.5);
}

void FinishPoint::update(double timeElapsed){
    timeElapsed = timeElapsed;
    animator->update();
    biluAnim->update();
    etemerAnim->update();
    varginhaAnim->update();
}

std::string FinishPoint::get_alien_names(){
    return aliens;
}

void FinishPoint::draw(){
    animator->draw_instant(get_position_x(), get_position_y());

    if(orientation.compare("UPDOWN") == 0){
        if(aliens.compare("EBV") == 0){
            etemerAnim->draw_instant(get_position_x()+1, get_position_y()+3.5);
            biluAnim->draw_instant(get_position_x()+12, get_position_y()+3.5);
            varginhaAnim->draw_instant(get_position_x()+23, get_position_y()+3.5);
        }else if(aliens.compare("EB") == 0){
            etemerAnim->draw_instant(get_position_x()+1, get_position_y()+3.5);
            biluAnim->draw_instant(get_position_x()+23, get_position_y()+3.5);
        }else if(aliens.compare("BV") == 0){
            biluAnim->draw_instant(get_position_x()+1, get_position_y()+3.5);
            varginhaAnim->draw_instant(get_position_x()+23, get_position_y()+3.5);
        }else if(aliens.compare("EV") == 0){
            etemerAnim->draw_instant(get_position_x()+1, get_position_y()+3.5);
            varginhaAnim->draw_instant(get_position_x()+23, get_position_y()+3.5);
        }else if(aliens.compare("E") == 0){
            etemerAnim->draw_instant(get_position_x()+12, get_position_y()+3.5);
        }else if(aliens.compare("B") == 0){
            biluAnim->draw_instant(get_position_x()+12, get_position_y()+3.5);
        }else if(aliens.compare("V") == 0){
            varginhaAnim->draw_instant(get_position_x()+12, get_position_y()+3.5);
        }
    }else{
        if(aliens.compare("EBV") == 0){
            etemerAnim->draw_instant(get_position_x()+3.5, get_position_y()+1);
            biluAnim->draw_instant(get_position_x()+3.5, get_position_y()+12);
            varginhaAnim->draw_instant(get_position_x()+3.5, get_position_y()+23);
        }else if(aliens.compare("EB") == 0){
            etemerAnim->draw_instant(get_position_x()+3.5, get_position_y()+1);
            biluAnim->draw_instant(get_position_x()+3.5, get_position_y()+23);
        }else if(aliens.compare("BV") == 0){
            biluAnim->draw_instant(get_position_x()+3.5, get_position_y()+1);
            varginhaAnim->draw_instant(get_position_x()+2, get_position_y()+23);
        }else if(aliens.compare("EV") == 0){
            etemerAnim->draw_instant(get_position_x()+3.5, get_position_y()+1);
            varginhaAnim->draw_instant(get_position_x()+3.5, get_position_y()+23);
        }else if(aliens.compare("E") == 0){
            etemerAnim->draw_instant(get_position_x()+3.5, get_position_y()+12);
        }else if(aliens.compare("B") == 0){
            biluAnim->draw_instant(get_position_x()+3.5, get_position_y()+12);
        }else if(aliens.compare("V") == 0){
            varginhaAnim->draw_instant(get_position_x()+3.5, get_position_y()+12);
        }
    }
}
