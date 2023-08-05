/* For playing MOD files using
   the GRRMOD library.
   You need to install the library now:
   https://github.com/GRRLIB/GRRMOD


   The player loops the given song forever
*/
#include <cstdio>
#include <grrmod.h>

#include "MODPlayer.hpp"
#include "DebugPrinter.hpp"

/* Include music headers here */
#include "ciiceli_it.h"


void MODPlayer::Init(DebugPrinter *printer) {
  printerPtr = printer;

  songs[0] = {(u8*)ciiceli_it, ciiceli_it_size, 83.0f};

  GRRMOD_Init(true);
  playState = PLAY_NOT_READY;
}

void MODPlayer::SetVolume(int16_t volume_param) {
  if (volume_param >=0 && volume_param <= 255){
    volume = volume_param;
    GRRMOD_SetVolume(volume, volume);
  }
}

void MODPlayer::StartPlaying(int song_index) {
  if (song_index >= 0 && song_index < SONG_AMOUNT ) {

    if (songs[song_index].size == 0) {
      playState = PLAY_ERROR_INVALID_INDEX;
      return;
    }

    if (playState == PLAY_ACTIVE) {
      StopPlaying();
    }
    bool change_song = song_index != current_song;
    if (playState == PLAY_READY && change_song) {
      GRRMOD_Unload();
    }
    if (change_song) {
      GRRMOD_SetMOD(songs[song_index].data, songs[song_index].size);
      current_song = song_index;
    }
    GRRMOD_SetVolume(volume, volume);
    GRRMOD_Start();
    play_duration = 0.0f;
    playState = PLAY_ACTIVE;
  }
}

void MODPlayer::EndFrame(float deltaTime) {
  play_duration += deltaTime;
  if (play_duration > songs[current_song].duration_seconds) {
    StartPlaying(current_song);
  }
}

void MODPlayer::RenderDebugInfo() {
  switch (playState) {
  case PLAY_NOT_READY:
    sprintf(debug_message, "MODPlayer: No song loaded");
    break;
  case PLAY_READY:
    sprintf(debug_message, "MODPlayer: Ready to play");
    break;
  case PLAY_ACTIVE:
    sprintf(debug_message, "MODPlayer: Playing song %d:%s %2.2f/%2.0f", current_song, GRRMOD_GetSongTitle(), play_duration, songs[current_song].duration_seconds);
  break;
  case PLAY_ERROR_INVALID_INDEX:
    sprintf(debug_message, "MODPlayer: Selected song was not loaded");
    break;
  };
  printerPtr->Print(debug_message);
}

void MODPlayer::StopPlaying() {
  if (playState == PLAY_ACTIVE) {
    GRRMOD_Stop();
    playState = PLAY_READY;
  }
}

void MODPlayer::DeInit() {
  if (playState == PLAY_ACTIVE) {
    StopPlaying();
  }
  if (playState == PLAY_READY) {
    GRRMOD_Unload();
  }
  GRRMOD_End();
}


