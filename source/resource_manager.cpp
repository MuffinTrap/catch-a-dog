#include "resource_manager.hpp"

#include "test_dog_png.h"

typedef const uint8_t * TextureData;

static std::unordered_map<TextureName, TextureData> texture_data_map {
  { TextureName::test_dog, test_dog_png }
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
