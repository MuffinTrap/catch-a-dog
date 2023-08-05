#pragma once

#include <cstdint>
#include <unordered_map>

#include <grrlib.h>
#undef R

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
  tree
};

class ResourceManager {
public:
  ResourceManager() {};
  ~ResourceManager();

  GRRLIB_texImg *tex(TextureName tex_name);

private:
  std::unordered_map<TextureName, GRRLIB_texImg *> textures_loaded;
};

