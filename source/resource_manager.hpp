#pragma once

#include <cstdint>
#include <unordered_map>

#include <grrlib.h>
#undef R

#include "sound_effect.hpp"

enum class SoundName : uint32_t
{
  bark1,
  bark2,
  bark3,
  bark4,
  drop,
  ding,
  pickup,
};

enum class TextureName : uint32_t
{
  test_dog,
  test_cat,
  pointer_open,
  pointer_down,
  titlescreen_logo,
  background,
  basket_back,
  basket_front,
  tree,

  dog1_1,
  dog1_2,

  dog2_1,
  dog2_2,
  dog3_1,
  dog3_2,
  assydog1_1,
  assydog1_2,
  assydog2_1,
  assydog2_2,
  assydog3_1,
  assydog3_2,
  notadog1_1,
  notadog1_2,
  notadog2_1,
  notadog2_2,
  notadog3_1,
  notadog3_2,
  notadog4_1,
  notadog4_2,
  notadog5_1,
  notadog5_2,
  oldschooldog1_1,
  oldschooldog1_2,
  oldschooldog2_1,
  oldschooldog2_2,
  oldschooldog3_1,
  oldschooldog3_2,
  ropedog1_1,
  ropedog1_2,
  ropedog2_1,
  ropedog2_2,
  ropedog3_1,
  ropedog3_2,

  end_screen_font,
};

class ResourceManager {
public:
  ResourceManager() {};
  ~ResourceManager();

  Sound_effect &ogg(SoundName sound_name);
  GRRLIB_texImg *tex(TextureName tex_name);
  GRRLIB_texImg *font(TextureName tex_name, int letter_width, int letter_height);

private:
  std::unordered_map<TextureName, GRRLIB_texImg *> textures_loaded;
};

