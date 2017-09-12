/**@description class to object of audio, where you can find some variables, files, others objects
 *and meths to the same.
 * @param string-audio_path
 * @param string-audio_type
 * @param int-volume
 */

#include "audio.hpp"
#include "log.h"
#include "string"

using namespace engine;

Audio::Audio(std::string audio_path, std::string audio_type, int volume){
  /**
  * Método feito para carregar o audio do game
  * <p>Esse método executa as ações de carregar o audio do jogo e tratar os erros do mesmo
  *utilizadas na classe audio</p>
  * @return string-audio_type
  * @return string-audio_effect
  */
    if(audio_type.compare("MUSIC") == 0) {
        audio_music = Mix_LoadMUS(audio_path.c_str());
        Mix_VolumeMusic(volume);
        if(audio_music == NULL) {
            ERROR("Audio file could not be loaded");
        }
    }else if(audio_type.compare("EFFECT") == 0) {
        audio_effect = Mix_LoadWAV(audio_path.c_str());
        Mix_VolumeChunk(audio_effect, volume);
        if(audio_effect == NULL) {
            ERROR("Audio file could not be loaded");
        }
    }else{
        ERROR("Audio type is not correct");
    }
}

Audio::~Audio(){}

/**
* Método play
* <p>Esse método executa a função de começar o audio do game</p>
*@param const int-times_to_play
*/

void Audio::play(const int times_to_play) {
    if(audio_music != NULL) {
        if(Mix_PlayMusic(audio_music, times_to_play) == -1) {
            ERROR("Audio could not be played");
        }
    }else {
        if(Mix_PlayChannel(-1, audio_effect, times_to_play) == -1) {
            ERROR("Audio could not be played");
        }
    }
}

/**
* Método pause
* <p>Esse método executa a função de parar a música do game</p>
*/

void Audio::pause() {
    if(audio_music != NULL) {
        if(Mix_PausedMusic() != 1) {
            Mix_PauseMusic();
        }else {
            ERROR("This audio has already been paused");
        }
    }else {
        ERROR("Audio effects can not be paused");
    }
}

/**
* Método resume
* <p>Esse método executa a função de recomeçar a música do game</p>
*/
void Audio::resume() {
    if(audio_music != NULL) {
        if(Mix_PausedMusic() == 1) {
            Mix_ResumeMusic();
        }else {
            ERROR("This audio is not paused");
        }
    }else {
        ERROR("Audio effects can not be resumed");
    }
}

/**
* Método stop
* <p>Esse método executa a função de parar todos os efeitos de audio do game</p>
*/

void Audio::stop() {
    if(audio_music != NULL) {
        Mix_HaltChannel(0);
    }else if(audio_effect != NULL) {
        Mix_HaltChannel(-1);
    }else {
        ERROR("Audio effects can not be stopped");
    }
}
