#ifndef PROGRESS_BAR_HPP
#define PROGRESS_BAR_HPP

#include "sdl2includes.hpp"
#include "window_manager.hpp"
#include "game_object.hpp"

namespace engine{
    class ProgressBar: public GameObject{
    public:
        ProgressBar(double positionX, double positionY, int width, int height);
        ~ProgressBar();
        void update(double timeElapsed);
        void draw();
        double getPercent();

    private:
        double percent;
        int pw;
        int px;
        SDL_Rect *backRect;
        SDL_Rect *frontRect;
        SDL_Color backColor;
        SDL_Color frontColor;
        SDL_Color oldColor;
    };
}

#endif
