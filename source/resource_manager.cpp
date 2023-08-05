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
#include "dog1_1_png.h"
#include "dog1_2_png.h"
#include "dog2_1_png.h"
#include "dog2_2_png.h"
#include "dog3_1_png.h"
#include "dog3_2_png.h"
#include "assydog1_1_png.h"
#include "assydog1_2_png.h"
#include "assydog2_1_png.h"
#include "assydog2_2_png.h"
#include "assydog3_1_png.h"
#include "assydog3_2_png.h"
#include "notadog1_1_png.h"
#include "notadog1_2_png.h"
#include "notadog2_1_png.h"
#include "notadog2_2_png.h"
#include "notadog3_1_png.h"
#include "notadog3_2_png.h"
#include "notadog4_1_png.h"
#include "notadog4_2_png.h"
#include "notadog5_1_png.h"
#include "notadog5_2_png.h"
#include "oldschooldog1_1_png.h"
#include "oldschooldog1_2_png.h"
#include "oldschooldog2_1_png.h"
#include "oldschooldog2_2_png.h"
#include "oldschooldog3_1_png.h"
#include "oldschooldog3_2_png.h"
#include "ropedog1_1_png.h"
#include "ropedog1_2_png.h"
#include "ropedog2_1_png.h"
#include "ropedog2_2_png.h"
#include "ropedog3_1_png.h"
#include "ropedog3_2_png.h"

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
  { TextureName::dog1_1,            dog1_1_png },
  { TextureName::dog1_2,            dog1_2_png },
  { TextureName::dog2_1,            dog2_1_png },
  { TextureName::dog2_2,            dog2_2_png },
  { TextureName::dog3_1,            dog3_1_png },
  { TextureName::dog3_2,            dog3_2_png },
  { TextureName::assydog1_1,        assydog1_1_png },
  { TextureName::assydog1_2,        assydog1_2_png },
  { TextureName::assydog2_1,        assydog2_1_png },
  { TextureName::assydog2_2,        assydog2_2_png },
  { TextureName::assydog3_1,        assydog3_1_png },
  { TextureName::assydog3_2,        assydog3_2_png },
  { TextureName::notadog1_1,        notadog1_1_png },
  { TextureName::notadog1_2,        notadog1_2_png },
  { TextureName::notadog2_1,        notadog2_1_png },
  { TextureName::notadog2_2,        notadog2_2_png },
  { TextureName::notadog3_1,        notadog3_1_png },
  { TextureName::notadog3_2,        notadog3_2_png },
  { TextureName::notadog4_1,        notadog4_1_png },
  { TextureName::notadog4_2,        notadog4_2_png },
  { TextureName::notadog5_1,        notadog5_1_png },
  { TextureName::notadog5_2,        notadog5_2_png },
  { TextureName::oldschooldog1_1,   oldschooldog1_1_png },
  { TextureName::oldschooldog1_2,   oldschooldog1_2_png },
  { TextureName::oldschooldog2_1,   oldschooldog2_1_png },
  { TextureName::oldschooldog2_2,   oldschooldog2_2_png },
  { TextureName::oldschooldog3_1,   oldschooldog3_1_png },
  { TextureName::oldschooldog3_2,   oldschooldog3_2_png },
  { TextureName::ropedog1_1,        ropedog1_1_png },
  { TextureName::ropedog1_2,        ropedog1_2_png },
  { TextureName::ropedog2_1,        ropedog2_1_png },
  { TextureName::ropedog2_2,        ropedog2_2_png },
  { TextureName::ropedog3_1,        ropedog3_1_png },
  { TextureName::ropedog3_2,        ropedog3_2_png },
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
