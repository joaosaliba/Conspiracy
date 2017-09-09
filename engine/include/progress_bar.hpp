#ifndef PROGRESS_BAR_HPP
#define PROGRESS_BAR_HPP

#include "sdl2includes.hpp"
#include "window_manager.hpp"
#include "game_object.hpp"

#include <vector>

namespace engine {
    class progress_bar: public game_object {
    public:
        progress_bar(double position_x, double position_y, int width, int height, 
        double increment);
        progress_bar(double position_x, double position_y, int width, int height,
                    double increment, std::vector<unsigned int> new_back_color, 
        std::vector<unsigned int> new_front_color);
        ~progress_bar();
        void update(double time_elapsed);
        void draw();
        double get_percent();
        void reset_percent();

    private:
        double percent;
        double progress_increment;
        int pw;
        int px;
        SDL_Rect *back_rect;
        SDL_Rect *front_rect;
        SDL_Color back_color;
        SDL_Color front_color;
        SDL_Color old_color;
    };
}

#endif
