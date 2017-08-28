#ifndef AUDIO_HPP
#define AUDIO_HPP

#include "sdl2includes.hpp"
#include <string>

namespace engine{

class Audio{
    public:
        Audio(std::string audio_path, std::string audio_type, int volume);
        ~Audio();
        void play(const int times_to_play);
        void pause();
        void resume();
        void stop();
    private:
        Mix_Music* audio_music = NULL;
        Mix_Chunk* audio_effect = NULL;
    };
}
#endif
