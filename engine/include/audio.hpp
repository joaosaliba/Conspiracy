/**@description class to object of audio, where you can find some values, files, others objects
 *and meths to the same.
 */

#ifndef AUDIO_HPP
#define AUDIO_HPP

#include "sdl2includes.hpp"
#include <string>


namespace engine{

    class Audio{
/** 
* Método construtor
* <p>Esse método executa a ação de construir os métodos e passar as variáreis
*utilizadas na classe audio.hpp</p>
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
