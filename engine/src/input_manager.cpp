#include "input_manager.hpp"
#include "log.h"

using namespace engine;

InputManager InputManager::instance;

    void InputManager::keyRepetitionDetector(int keyAction, SDL_Event event){

      keyAction = event.key.keysym.sym;
      //If there is no key event repetition it only answers the current event
      if(!event.key.repeat) {
          keyActive[keyAction] = true;
          keyPrevious[keyAction] = false;
          INFO("PUSH");

      //If there is repetition it answers the previous action
      }else if(event.key.repeat) {
          keyPrevious[keyAction] = true;
      //No key event detected
      }else {
          ERROR("No key event");
      }
    }

    void InputManager::keyUp(int previousAction, SDL_Event event){
      SDL_PollEvent(&event);
      previousAction = event.key.keysym.sym;
      keyPrevious = keyActive;
      keyActive[previousAction] = false;
      INFO("RELEASE");
    }

    void InputManager::update(SDL_Event event) {
        int keyAction = 0, previousAction = 0;

        //While SDL is detecting key events
        while(SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                quitRequest = true;
                break;
                case SDL_KEYDOWN:
                    keyRepetitionDetector(keyAction, event);
                break;
                case SDL_KEYUP:
                    keyUp(previousAction, event);
                break;

                default:
                    //nothing to do
                    break;
            }
        }
    }


    bool InputManager::getQuitRequest(){
        return quitRequest;
    }

    bool InputManager::isKeyPressed(int iKeyCode) {
        return keyActive[iKeyCode];
    }

    bool InputManager::isKeyReleased(int iKeyCode){
        return (!keyActive[iKeyCode] && keyPrevious[iKeyCode]);
    }

    bool InputManager::isKeyTriggered(int iKeyCode){
        //It verifies if the key is triggered
        if(keyActive[iKeyCode] && !keyPrevious[iKeyCode]){
            keyPrevious[iKeyCode] = true;
            return true;
        //No key triggered
        } else{
            return false;
        }
    }

    void InputManager::setQuitRequest(bool isRequest){
        quitRequest = isRequest;
    }
