/**
 * @file audio.hpp
 * @brief class to object of audio, where you can find some values, files, others objects
 * and methods to the same.
 * @copyright  GNU GENERAL PUBLIC LICENSE.
 */

#ifndef AUDIO_HPP
#define AUDIO_HPP

#include "sdl2includes.hpp"
#include <string>


namespace engine{

    class Audio{
/**
* @brief here you can find the construct and destructor method, with attributes and
* methods of the class audio
* @param string-audio_path
* @param string-audio_type
* @param int-volume
*/
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
