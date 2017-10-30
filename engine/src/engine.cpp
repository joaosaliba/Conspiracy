/**
    @file engine.cpp
    @brief Manage the engine of the game.
    @copyright MIT License.
*/

//#define NDEBUG *uncomment to disable assertions
#include "engine.hpp"
#include <assert.h>

namespace engine{

    double MILI_SECOND = 1000.0;
    const std::string GAME_NAME = "Conspiracy";
    const std::pair <int, int> WINDOW_SIZE (960, 640);

    SceneManager* scene_manager = nullptr;
    WindowManager* window_manager = nullptr;
    SDLManager* sdl_manager = nullptr;

    double engine_start_time = 0.0;
    double engine_step_time = 0.0;
    double engine_time_elapsed = 0.0;
    double frame_time = 0.0;
    double frame_rate = 60.0;

    SceneManager* getSceneManager() {
        assert(scene_manager != NULL);
        return scene_manager;
}

    /**
      @brief It loads the game engine.
    */

    void loadEngine() {
         INFO("Loading engine");
         assert(engine_start_time != NULL);
         assert(engine_step_time != NULL);
         assert(engine_time_elapsed != NULL);
         scene_manager = new SceneManager();

         engine_start_time = SDL_GetTicks();
         engine_step_time = engine_start_time;
         frame_time = MILI_SECOND/frame_rate;

         sdl_manager = new SDLManager();
         window_manager = new WindowManager();
         //If there is an error while initializing SDL it exits.
         if(!sdl_manager->initSDL()) {
             ERROR("ERRO AO INICIAR SDL");
             exit(-1);
         }
         //If window manager fails in creating window it exits.
         else if(!window_manager->createWindow(GAME_NAME, WINDOW_SIZE)) {
             ERROR("ERRO AO CRIAR JANELA");
             exit(-1);
         }else {
             ERROR("ERRO AO CARREGAR ENGINE");
         }
     }


    /**
      @brief It detects a delay in the engine
    */

    void delayDetector(){
      INFO("Detecting delay");
      if(frame_time > engine_time_elapsed) {
          DEBUG("SDL_DELAY: " + std::to_string(frame_time - engine_time_elapsed));
          SDL_Delay(frame_time - engine_time_elapsed);
          engine_time_elapsed = SDL_GetTicks() - engine_step_time;
      //If no delay is detected
      }else {
          //nothing to do
      }
    }

    /**
      @brief It stops the engine if requested
      @param[in] engine_is_running it tells if the engine is running_engine
      @param[in] SDL_Event event event object
    */

    void stopEngine(bool engine_is_running, SDL_Event event){
        INFO("Stoping engine");
        bool running_engine = engine_is_running;
        //If while engine is running it gets a quit request, SDL is finalized and Window is destroyed
        if(engine::InputManager::instance.getQuitRequest()) {
            running_engine = false;
            assert(engine_is_running != NULL);
            sdl_manager->finalizeSDL();
            window_manager->destroyWindow();
            engine_is_running = running_engine;
            //Else it keeps engine running
        }else {
            engine_step_time = SDL_GetTicks();
            engine::InputManager::instance.update(event);
            SDL_RenderClear(WindowManager::getGameCanvas());
        }
    }

    /**
      @brief If the scene is null it draws the scene
    */

    void nullSceneCorrection(){
        INFO("Correcting null sound");
        //If the current scene is null it updates and draw the scene
        if(scene_manager->get_current_scene() != NULL) {
            scene_manager->get_current_scene()->update(engine_time_elapsed);
            scene_manager->get_current_scene()->draw();
        //It draws the scene
        }else {
            scene_manager->get_current_scene()->draw();
        }
    }
    /**
      @brief It starts the game engine
    */

    void run() {
         INFO("Running engine");
         assert(engine_start_time != NULL);
         assert(engine_step_time != NULL);
         assert(engine_time_elapsed != NULL);
         assert(engine_is_running != NULL);

         SDL_Event event;
         bool engine_is_running = true;
         //While engine is running
         while(engine_is_running){
             engine_step_time = SDL_GetTicks();
             assert(engine_step_time != NULL);
             engine::InputManager::instance.update(event);
             SDL_RenderClear(WindowManager::getGameCanvas());

             stopEngine(engine_is_running, event);

             engine_time_elapsed = SDL_GetTicks() - engine_step_time;
             DEBUG("TICKS:" + std::to_string(SDL_GetTicks()));
             DEBUG("frameTime:" + std::to_string(frame_time));
             DEBUG("timeElapsed: " + std::to_string(engine_time_elapsed));
             assert(frame_time != NULL);
             assert(engine_time_elapsed != NULL);

             //It detects a delay in the engine
             delayDetector();

             //It detects a null scene
             nullSceneCorrection();

             assert(get_current_scene() != NULL);
             AnimationManager::instance.draw_quads();
             SDL_RenderPresent(WindowManager::getGameCanvas());
         }
  }
}
