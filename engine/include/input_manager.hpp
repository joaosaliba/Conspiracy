#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include "sdl2includes.hpp"
#include <unordered_map>

namespace engine{

    class InputManager{

    public:
        enum KeyPress{
            KEY_PRESS_UP = SDLK_UP,
            KEY_PRESS_DOWN = SDLK_DOWN,
            KEY_PRESS_RIGHT = SDLK_RIGHT,
            KEY_PRESS_LEFT = SDLK_LEFT,
            KEY_PRESS_SPACE = SDLK_SPACE,
            KEY_PRESS_ONE = SDLK_1,
            KEY_PRESS_TWO = SDLK_2,
            KEY_PRESS_THREE = SDLK_3,
            KEY_PRESS_ESC = SDLK_ESCAPE,
            KEY_PRESS_ENTER = SDLK_RETURN,
            KEY_PRESS_L = SDLK_l,
            KEY_PRESS_K = SDLK_k
        };

        static InputManager instance;
        void update(SDL_Event event);
        bool getQuitRequest();
        void setQuitRequest(bool isRequest);
        void Update(void);
        void keyRepetitionDetector(int keyAction, SDL_Event event);
        void keyUp(int previousAction, SDL_Event event);

        bool is_key_triggered(int iKeyCode);
        bool is_key_pressed(int iKeyCode);
        bool is_key_released(int iKeyCode);

    private:
        InputManager(): quitRequest(false){}
        bool quitRequest;
        std::unordered_map<int, bool> keyActive;
        std::unordered_map<int, bool> keyPrevious;
    };
}
#endif
