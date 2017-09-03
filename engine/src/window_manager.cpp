#include "window_manager.hpp"
using namespace engine;

SDL_Window *gameWindow;
SDL_Renderer *gameCanvas;

bool WindowManager::createWindow(std::string windowTitle, std::pair<int, int> windowSize){
    INFO("Create window");
    gameWindow = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, windowSize.first,
    windowSize.second, SDL_WINDOW_SHOWN);

    if(gameWindow == NULL){
        return false;
    }

    INFO("Create canvas");
    game_canvas = SDL_CreateRenderer(gameWindow, -1,
        SDL_RENDERER_ACCELERATED);

        if(game_canvas == NULL){
            return false;
        }

        SDL_SetRenderDrawColor(game_canvas, 100, 100, 100, 255);
        SDL_RenderClear(game_canvas);
        SDL_RenderPresent(game_canvas);
        setImageIcon();
        return true;
    }


    bool WindowManager::destroyWindow(){
        INFO("Destroying canvas");
        SDL_DestroyRenderer(game_canvas);
        gameCanvas = NULL;

        INFO("Destroying window");
        SDL_DestroyWindow(game_window);
        game_window = NULL;

        return true;
    }

    SDL_Window* WindowManager::GetGameWindow(){
        return game_window;
    }


    SDL_Renderer* WindowManager::getGameCanvas(){
        return game_canvas;
    }
    
    void WindowManager::setImageIcon(){
      // TODO Change image icon.
      SDL_Surface * image = NULL;
      image = IMG_Load(std::string("assets/sprites/alien.png").c_str());

      if(image == NULL){
            exit(-1);
      }

      SDL_SetWindowIcon(game_window, image);
      SDL_FreeSurface(image);

    }
