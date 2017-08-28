#include "window_manager.hpp"
using namespace engine;

SDL_Window *game_window;
SDL_Renderer *game_canvas;

bool WindowManager::createWindow(std::string window_title, std::pair<int, int> window_size) {
    INFO("Create window");
    game_window = SDL_CreateWindow(window_title.c_str(), SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, window_size.first,
    window_size.second, SDL_WINDOW_SHOWN);

    if(game_window == NULL) {
        return false;
    }

    INFO("Create canvas");
    game_canvas = SDL_CreateRenderer(game_window, -1,
        SDL_RENDERER_ACCELERATED);

        if(game_canvas == NULL) {
            return false;
        }

        SDL_SetRenderDrawColor(game_canvas, 100, 100, 100, 255);
        SDL_RenderClear(game_canvas);
        SDL_RenderPresent(game_canvas);
        setImageIcon();
        return true;
    }


    bool WindowManager::destroyWindow() {
        INFO("Destroying canvas");
        SDL_DestroyRenderer(game_canvas);
        game_canvas = NULL;

        INFO("Destroying window");
        SDL_DestroyWindow(game_window);
        game_window = NULL;

        return true;
    }

    SDL_Window* WindowManager::GetGameWindow() {
        return game_window;
    }


    SDL_Renderer* WindowManager::getGameCanvas() {
        return game_canvas;
    }
    
    void WindowManager::setImageIcon() {
      // TODO Change image icon.
      SDL_Surface * image = NULL;
      image = IMG_Load(std::string("assets/sprites/alien.png").c_str());

      if(image == NULL) {
            exit(-1);
      }

      SDL_SetWindowIcon(game_window, image);
      SDL_FreeSurface(image);

    }
