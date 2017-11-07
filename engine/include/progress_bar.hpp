/**
 * @file progress_bar.cpp
 * @brief class to object of progress_bar, where you can find some values, files,
 * others objects used in this class and methods to the same.
 * @copyright  GNU GENERAL PUBLIC LICENSE.
 */


#ifndef PROGRESS_BAR_HPP
#define PROGRESS_BAR_HPP

#include "sdl2includes.hpp"
#include "window_manager.hpp"
#include "game_object.hpp"
#include "log.h"
#include <vector>

namespace engine {
    class ProgressBar: public GameObject {
    public:
        ProgressBar(double position_x, double position_y, int width, int height, double increment);
        ProgressBar(double position_x, double position_y, int width, int height,
                    double increment, std::vector<unsigned int> newBackColor, std::vector<unsigned int> newFrontColor);
        ~ProgressBar();
        void update(double time_elapsed);
        void draw();
        double get_percent();
        void reset_percent();

    private:
        double percent = 0.0;
        double progress_increment = 0.0;
        int pw = 0;
        int px = 0;
        SDL_Rect *back_rect = nullptr;
        SDL_Rect *front_rect = nullptr;
        SDL_Color back_color;
        SDL_Color front_color;
        SDL_Color old_color;
    };
}

#endif
