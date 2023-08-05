#pragma once

#include <stdint.h>
#include <stddef.h>

class DebugPrinter;


/*
struct MOD_Channel
{
  int freq;
  int vol;
  int realvol;
  float width;
};
*/
struct MOD_Song
{
  uint8_t* data;
  uint32_t size = 0;
  float duration_seconds;
};

enum PlayState {
  PLAY_NOT_READY,
  PLAY_READY,
  PLAY_ACTIVE,
  PLAY_ERROR_INVALID_INDEX
};

class MODPlayer {
public:
  void Init(DebugPrinter *printer);
  void SetVolume(int16_t volume);
  void StartPlaying(int song_index);
  void EndFrame(float deltaTime);
  void RenderDebugInfo();
  void StopPlaying();

  void DeInit();
private:
  // float calc_size(uint8_t voice, MOD_Channel* channel);

  char debug_message[120];

  static const int SONG_AMOUNT = 4;
  MOD_Song songs[SONG_AMOUNT];
  int current_song = -1;
  int16_t volume = 255;

  float play_duration = 0.0f;

  PlayState playState;

  DebugPrinter *printerPtr;
};
