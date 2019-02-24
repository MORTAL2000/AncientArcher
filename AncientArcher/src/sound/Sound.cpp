#include "Sound.h"
#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>
#include "../util/mearly.h"

bool soundReady = false;

void playfootstepsound() {

  if (!soundReady) initsound();

  int dist = mearly::NTKR(0, NUMFOOTSTEPS - 1);

  Mix_PlayChannel(-1, footstepsoundeffects[dist], 0);
}

void playgruntsound() {

  if (!soundReady) initsound();

  int dist = mearly::NTKR(0, NUMGRUNTS - 1);

  Mix_PlayChannel(-1, gruntsoundeffects[dist], 0);
}

void playlandingsound() {

  if (!soundReady) initsound();

  Mix_PlayChannel(-1, landingsoundeffect, 0);
}

void playsuccesssound() {

  if (!soundReady) initsound();

  Mix_PlayChannel(-1, successsoundeffect, 0);
}

void playpunchsound() {

  if (!soundReady) initsound();

  Mix_PlayChannel(-1, punchsoundeffect, 0);
}

void playswordswingsound() {

  if (!soundReady) initsound();

  Mix_PlayChannel(-1, swordswingsoundeffect, 0);
}

void playbowsound() {

  if (!soundReady) initsound();

  Mix_PlayChannel(-1, bowsoundeffect, 0);
}

void playequipgearsound() {
  if (!soundReady) initsound();

  Mix_PlayChannel(-1, equipgearsoundeffect, 0);
}

void toggleAmbientWindyNight() {
  if (!soundReady) initsound();
  Mix_PlayMusic(AMBIENT_windy_night, -1);
}

//--------------------init sound---------------
void initsound() {
  SDL_Init(SDL_INIT_AUDIO);
  /* initialize sound */
  int audio_rate = 22050;
  Uint16 audio_format = AUDIO_S16SYS;
  int audio_channels = 2;
  int audio_buffers = 4096;
  if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't init audio: %s", Mix_GetError());
    exit(-3);
  }

  /* load sound assets */
  // load footstep variations
  footstepsoundeffects[0] = Mix_LoadWAV("../AncientArcher/res/sfx/footstep01.wav");  // load footsteps
  footstepsoundeffects[1] = Mix_LoadWAV("../AncientArcher/res/sfx/footstep02.wav");  // load footsteps
  footstepsoundeffects[2] = Mix_LoadWAV("../AncientArcher/res/sfx/footstep03.wav");  // load footsteps
  footstepsoundeffects[3] = Mix_LoadWAV("../AncientArcher/res/sfx/footstep04.wav");  // load footsteps
  footstepsoundeffects[4] = Mix_LoadWAV("../AncientArcher/res/sfx/footstep05.wav");  // load footsteps
  footstepsoundeffects[5] = Mix_LoadWAV("../AncientArcher/res/sfx/footstep06.wav");  // load footsteps
  for (auto &se : footstepsoundeffects) {  //test footstep load
    if (se == nullptr) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
        "Couldn't load audio: %s",
        Mix_GetError());
    }
  }

  // load jump sound effect (grunts)
  gruntsoundeffects[0] = Mix_LoadWAV("../AncientArcher/res/sfx/grunt01.wav");  // load grunts
  gruntsoundeffects[1] = Mix_LoadWAV("../AncientArcher/res/sfx/grunt02.wav");
  gruntsoundeffects[2] = Mix_LoadWAV("../AncientArcher/res/sfx/grunt03.wav");
  gruntsoundeffects[3] = Mix_LoadWAV("../AncientArcher/res/sfx/grunt04.wav");
  for (auto &se : gruntsoundeffects) {  //test grunt load
    if (se == nullptr) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
        "Couldn't load audio: %s",
        Mix_GetError());
    }
  }

  landingsoundeffect = Mix_LoadWAV("../AncientArcher/res/sfx/feetlanding.wav");
  if (landingsoundeffect == nullptr) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
      "Couldn't load audio: %s",
      Mix_GetError());
  }


  successsoundeffect = Mix_LoadWAV("../AncientArcher/res/sfx/success.wav");
  if (successsoundeffect == nullptr) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
      "Couldn't load audio: %s",
      Mix_GetError());
  }

  punchsoundeffect = Mix_LoadWAV("../AncientArcher/res/sfx/punch.wav");
  if (punchsoundeffect == nullptr) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
      "Couldn't load audio: %s",
      Mix_GetError());
  }

  swordswingsoundeffect = Mix_LoadWAV("../AncientArcher/res/sfx/swordswing.wav");
  if (swordswingsoundeffect == nullptr) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
      "Couldn't load audio: %s",
      Mix_GetError());
  }

  bowsoundeffect = Mix_LoadWAV("../AncientArcher/res/sfx/bowfire.wav");
  if (bowsoundeffect == nullptr) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
      "Couldn't load audio: %s",
      Mix_GetError());
  }

  equipgearsoundeffect = Mix_LoadWAV("../AncientArcher/res/sfx/equip_gear.wav");
  if (equipgearsoundeffect == nullptr) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
      "Couldn't load audio: %s",
      Mix_GetError());
  }

  // load ambient wind
  AMBIENT_windy_night = Mix_LoadMUS("../AncientArcher/res/sfx/AMBIENT_windy_night.wav");
  if (AMBIENT_windy_night == nullptr) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
      "Couldn't load audio: %s",
      Mix_GetError());
  }

  soundReady = true;  //kk sound is good to go

}
