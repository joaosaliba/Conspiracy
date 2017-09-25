/**
 * @file audio.cpp
 * @brief class to object of audio, where you can find some values, files, others objects
 * and methods to the same.
 * @copyright  GNU GENERAL PUBLIC LICENSE.
 */

#include "audio.hpp"
#include "log.h"
#include "string"
#include <assert.h>

using namespace engine;

Audio::Audio(std::string audio_path, std::string audio_type, int volume) {

    assert ( volume != NULL);

  /**
  * @brief Method did to load the audio of the game
  * <p>This method execute actions to load the audio of the game and treat the erros
  * of the class "audio"</p>
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
    }else {
        ERROR("Audio type is not correct");
    }
}

/**
  *    @brief Audio object destructor.
 */
Audio::~Audio(){}

/**
* @brief Method play
* <p>This method execute the action to start the audio of the game</p>
* @param const int-times_to_play
* @return void
*/

void Audio::play(const int times_to_play) {
    assert ( times_to_play != NULL);

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
* @brief Method pause
* <p>This method execute the function of stopping the music of the game</p>
* @return void
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
* @brief Method resume
* <p>This method restart the music of the game</p>
* @return void
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
* @brief Method stop
* <p>This method stop all the audio effects of the game</p>
* @return void
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
