#include "game_manager.hpp"

#include <cstdlib>

#include <grrlib.h>
#undef R


GameManager::GameManager(
  ResourceManager &resource_manager
) : resource_manager(resource_manager)
{
  this->state.reset(new GameState());
}

void GameManager::init() {
  for (int i = 0; i < 30; ++i) {
    Entity ent = new_entity();
    this->creatures[ent] = CreatureComponent();

    this->transforms[ent] = TransformComponent {
      .pos = glm::vec2(rand() % 120 + i * 23 + 180, rand() % 120 + i * 32 + 32),
      .angle = 0.f
    };
  }
}

void GameManager::update(
  double time,
  double delta_time,
  PointerState pointer_state
) {

  for (auto creature_pair : this->creatures) {
    TransformComponent &trans = (*this->transforms.find(creature_pair.first)).second;
    trans.pos += glm::vec2(glm::sin(time), glm::cos(time));
  }
}

void GameManager::render() {
  for (auto creature_pair : this->creatures) {
    const TransformComponent &trans = this->transforms.at(creature_pair.first);
    const CreatureComponent &creature = creature_pair.second;

    GRRLIB_texImg *tex = this->resource_manager.tex(creature.tex);

    GRRLIB_DrawImg(trans.pos.x, trans.pos.y, tex, 0, 1, 1, 0xFFFFFFFF);
  }
}
