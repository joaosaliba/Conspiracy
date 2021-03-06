#ifndef WINDOW_MANAGER_HPP
#define WINDOW_MANAGER_HPP

#include <string>
#include <sdl2includes.hpp>
#include "log.h"

namespace engine{
    class WindowManager{
    public:
        bool createWindow(std::string windowTitle, std::pair<int, int> windowSize);
        bool destroyWindow();
        SDL_Window* GetGameWindow();
        void test_game_window();
        void test_game_canvas();
        static SDL_Renderer* getGameCanvas();
    private:
        void setImageIcon();
    };
}
#endif
