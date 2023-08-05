#pragma once

#include <vector>

#include "resource_manager.hpp"

enum class CreatureCategory {
  dog, not_dog
};

struct CreatureDefinition {
  std::vector<TextureName> frames;
  CreatureCategory category = CreatureCategory::not_dog;
};

const std::vector<CreatureDefinition> creature_definition_pool = {
  {
    .frames = {
      TextureName::dog1_1,
      TextureName::dog1_2,
    },
    .category = CreatureCategory::dog,
  },
  {
    .frames = {
      TextureName::dog2_1,
      TextureName::dog2_2,
    },
    .category = CreatureCategory::dog,
  },
  {
    .frames = {
      TextureName::dog3_1,
      TextureName::dog3_2,
    },
    .category = CreatureCategory::dog,
  },
  {
    .frames = {
      TextureName::assydog1_1,
      TextureName::assydog1_2,
    },
    .category = CreatureCategory::dog,
  },
  {
    .frames = {
      TextureName::assydog2_1,
      TextureName::assydog2_2,
    },
    .category = CreatureCategory::dog,
  },
  {
    .frames = {
      TextureName::assydog3_1,
      TextureName::assydog3_2,
    },
    .category = CreatureCategory::dog,
  },
  {
    .frames = {
      TextureName::notadog1_1,
      TextureName::notadog1_2,
    },
    .category = CreatureCategory::not_dog,
  },
  {
    .frames = {
      TextureName::notadog2_1,
      TextureName::notadog2_2,
    },
    .category = CreatureCategory::not_dog,
  },
  {
    .frames = {
      TextureName::notadog3_1,
      TextureName::notadog3_2,
    },
    .category = CreatureCategory::not_dog,
  },
  {
    .frames = {
      TextureName::notadog4_1,
      TextureName::notadog4_2,
    },
    .category = CreatureCategory::not_dog,
  },
  {
    .frames = {
      TextureName::notadog5_1,
      TextureName::notadog5_2,
    },
    .category = CreatureCategory::not_dog,
  },
  {
    .frames = {
      TextureName::oldschooldog1_1,
      TextureName::oldschooldog1_2,
    },
    .category = CreatureCategory::dog,
  },
  {
    .frames = {
      TextureName::oldschooldog2_1,
      TextureName::oldschooldog2_2,
    },
    .category = CreatureCategory::dog,
  },
  {
    .frames = {
      TextureName::oldschooldog3_1,
      TextureName::oldschooldog3_2,
    },
    .category = CreatureCategory::dog,
  },
  {
    .frames = {
      TextureName::ropedog1_1,
      TextureName::ropedog1_2,
    },
    .category = CreatureCategory::dog,
  },
  {
    .frames = {
      TextureName::ropedog2_1,
      TextureName::ropedog2_2,
    },
    .category = CreatureCategory::dog,
  },
  {
    .frames = {
      TextureName::ropedog3_1,
      TextureName::ropedog3_2,
    },
    .category = CreatureCategory::dog,
  },
};
