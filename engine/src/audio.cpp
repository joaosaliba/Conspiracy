#include "audio.hpp"
#include "log.h"
#include "string"

using namespace engine;

Audio::Audio(std::string audio_path, std::string audio_type, int volume) {
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

Audio::~Audio() {
}

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

void Audio::stop() {
    if(audio_music != NULL) {
        Mix_HaltChannel(0);
    }else if(audio_effect != NULL) {
        Mix_HaltChannel(-1);
    }else {
        ERROR("Audio effects can not be stopped");
    }
}
