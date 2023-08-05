#include "resource_manager.hpp"

#include "test_dog_png.h"
#include "test_cat_png.h"
#include "pointer_open_png.h"
#include "pointer_down_png.h"
#include "titlescreen_logo_png.h"
#include "background_png.h"
#include "basket_back_png.h"
#include "basket_front_png.h"
#include "tree_png.h"

typedef const uint8_t * TextureData;

static std::unordered_map<TextureName, TextureData> texture_data_map {
  { TextureName::test_dog,          test_dog_png },
  { TextureName::test_cat,          test_cat_png },
  { TextureName::pointer_open,      pointer_open_png },
  { TextureName::pointer_down,      pointer_down_png },
  { TextureName::titlescreen_logo,  titlescreen_logo_png },
  { TextureName::background,        background_png },
  { TextureName::basket_back,       basket_back_png },
  { TextureName::basket_front,      basket_front_png },
  { TextureName::tree,              tree_png },
};

ResourceManager::~ResourceManager() {
  for (auto &texture : this->textures_loaded) {
    GRRLIB_FreeTexture(texture.second);
  }
}

GRRLIB_texImg *ResourceManager::tex(TextureName tex_name) {
  if (auto found = this->textures_loaded.find(tex_name); found != this->textures_loaded.end()) {
    return (*found).second;
  }

  TextureData tex_data = texture_data_map.at(tex_name);
  GRRLIB_texImg *loaded = GRRLIB_LoadTexture(tex_data);

  this->textures_loaded[tex_name] = loaded;

  return loaded;
}
