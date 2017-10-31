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

Audio::Audio(std::string audio_path, std::string audio_type, int audio_volume) {

    assert ( audio_volume != NULL);

    //verify if the volume exist
    if(audio_volume == NULL) {
      ERROR("do not exist the volume");
      exit(-1);
    }else {
      //nothing to do
    }

  /**
  * @brief Method create_music
  * <p>This method load the audio music of the game
  * @param[in] audio_type - std::string
  * @param[in] audio_path - std::string
  * @param[in] audio_volume - int
  * @return[out] audio_music - Mix_Music*
  */

    audio_music = create_music(audio_type, audio_path, audio_volume);

    /**
    * @brief Method create_effect
    * <p>This method load the effect of the music in the game
    * @param[in] audio_type - std::string
    * @param[in] audio_path - std::string
    * @param[in] audio_volume - int
    * @return[out] audio_effect - Mix_Chunk*
    */

    audio_effect = create_effect(audio_type, audio_path, audio_volume);

    /**
    * @brief Method verify_error
    * <p>This method verify if the audio and the effect is NULL.
    * @param[in] audio_effect - Mix_Chunk*
    * @param[in] audio_music - Mix_Music*
    * @return[out] void
    */

    verify_error(audio_music, audio_effect);
}


Audio::create_effect(std::string audio_type, std::string audio_path, int audio_volume){
//assert()
    Mix_Chunk* audio_effect = nullptr;

    if(audio_type.compare("EFFECT") == 0) {
      audio_effect = Mix_LoadWAV(audio_path.c_str());
      Mix_VolumeChunk(audio_effect, audio_volume);
      if(audio_effect == NULL) {
        ERROR("Audio file could not be loaded");
    }

  }
  return audio_effect;
}


Audio::create_music(std::string audio_type, std::string audio_path, int audio_volume){
    //assert()

    Mix_Music* audio_music = nullptr;
    if(audio_type.compare("MUSIC") == 0) {

        audio_music = Mix_LoadMUS(audio_path.c_str());
        Mix_VolumeMusic(audio_volume);
        if(audio_music == NULL) {
            ERROR("Audio file could not be loaded");

        }

    }
    return audio_music;
}

Audio::verify_error(Mix_Music* audio_music, Mix_Music* audio_effect){

    if(audio_music == NULL & audio_effect == NULL){
      ERROR("Audio type is not correct");
    }
}



/**
  *    @brief Audio object destructor.
 */
Audio::~Audio(){}

/**
* @brief Method play
* <p>This method call other 2 functions to see if the music or effect of
* the music will give error</p>
* @param[in] const int-times_to_play
* @return void
*/

void Audio::play(const int times_to_play) {

    assert ( times_to_play != NULL);

    verify_audio_music_error(times_to_play);

    verify_audio_effect_error(times_to_play);

  /**  if(audio_music != NULL) {
        //if the audio music is differente of null he get in and make others logical flows
        if(Mix_PlayMusic(audio_music, times_to_play) == -1) {
            ERROR("Audio could not be played");
        }else {
            //if Mix_PlayMusic be different of -1 it can be played
        }
    }else {
        if(Mix_PlayChannel(-1, audio_effect, times_to_play) == -1) {
            ERROR("Audio could not be played");
        }else {
            //if Mix_PlayChannel be different of -1 he can be played
        }
    }*/
}

Audio::verify_audio_music_error(const int times_to_play){

    assert ( times_to_play != NULL);

    if(audio_music != NULL) {
        //if the audio music is differente of null he get in and make others logical flows
        if(Mix_PlayMusic(audio_music, times_to_play) == -1) {
            ERROR("Audio could not be played");
        }else {
            //if Mix_PlayMusic be different of -1 it can be played
        }
      }
}

Audio::verify_audio_effect_error(const int times_to_play){
    assert (times_to_play != NULL);

    if(audio_effect != NULL){
        if(Mix_PlayChannel(-1, audio_effect, times_to_play) == -1) {
            ERROR("Audio could not be played");
        }else {
            //if Mix_PlayChannel be different of -1 he can be played
        }
      }
}

/**
* @brief Method pause
* <p>This method execute the function of stopping the music of the game</p>
* @return void
*/

void Audio::pause() {
    //if the audio music is differente from null he get in and make others logical flows
    if(audio_music != NULL) {
        //if Mix_PausedMusic is different of 1 he pause the music, or he send a error messsage
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
    //if the audio music is differente of null he get in and make others logical flows
    if(audio_music != NULL) {
        //this part verify if the music status is paused, then this IF resume the music, or send error message
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
