#include "engine.hpp"

namespace engine{

    const std::string GAME_NAME = "Conspiracy";
    const std::pair <int, int> WINDOW_SIZE (960, 640);

    SceneManager* scene_manager;
    WindowManager* window_manager;
    SDLManager* sdl_manager;
    double start_time;
    double step_time;
    double time_elapsed;
    double frame_time;
    double frame_rate = 60.0;
    SceneManager* getSceneManager() {
        return scene_manager;
    }
    void loadEngine() {
        scene_manager = new SceneManager();
        window_manager = new WindowManager();
        sdl_manager = new SDLManager();
        start_time = SDL_GetTicks();
        step_time = start_time;
        frame_time = 1000.0/frame_rate;

        if(!sdl_manager->initSDL()) {
            ERROR("ERRO AO INICIAR SDL");
            exit(-1);
        }else if(!window_manager->createWindow(GAME_NAME, WINDOW_SIZE)) {
            ERROR("ERRO AO CRIAR JANELA");
            exit(-1);
        }
    }

    void run() {
        bool is_running = true;
        SDL_Event event;

        while(is_running){
            step_time = SDL_GetTicks();

            engine::InputManager::instance.update(event);
            SDL_RenderClear(WindowManager::getGameCanvas());

            if(engine::InputManager::instance.getQuitRequest()) {
                is_running = false;
                sdl_manager->finalizeSDL();
                window_manager->destroyWindow();
                continue;
            }


            time_elapsed = SDL_GetTicks() - step_time;
            DEBUG("TICKS:" + std::to_string(SDL_GetTicks()));
            DEBUG("frameTime:" + std::to_string(frame_time));
            DEBUG("timeElapsed: " + std::to_string(time_elapsed));
            if(frame_time > time_elapsed) {
                DEBUG("SDL_DELAY: " + std::to_string(frame_time - time_elapsed));
                SDL_Delay(frame_time - time_elapsed);
                time_elapsed = SDL_GetTicks() - step_time;
            }

            if(scene_manager->get_current_scene() != NULL) {
              scene_manager->get_current_scene()->update(time_elapsed);
              scene_manager->get_current_scene()->draw();
            }
            AnimationManager::instance.draw_quads();
            SDL_RenderPresent(WindowManager::getGameCanvas());
        }
    }
}
