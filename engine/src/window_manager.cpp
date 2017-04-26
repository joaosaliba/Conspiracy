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
  gameCanvas = SDL_CreateRenderer(gameWindow, -1,
                                  SDL_RENDERER_ACCELERATED |
                                  SDL_RENDERER_PRESENTVSYNC);

  if(gameCanvas == NULL){
    return false;
  }

  SDL_SetRenderDrawColor(gameCanvas, 0, 0, 0, 0);
  SDL_RenderClear(gameCanvas);
  SDL_RenderPresent(gameCanvas);

  return true;
}


bool WindowManager::destroyWindow(){
  INFO("Destroying canvas");
  SDL_DestroyRenderer(gameCanvas);
  gameCanvas = NULL;

  INFO("Destroying window");
  SDL_DestroyWindow(gameWindow);
  gameWindow = NULL;

  return true;
}

SDL_Window* GetGameWindow(){
    return gameWindow;
}
