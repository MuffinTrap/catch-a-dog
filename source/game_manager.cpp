#include "game_manager.hpp"

#include <cstdlib>

#include <grrlib.h>
#undef R


GameManager::GameManager(
  TransformSystem &transform_system,
  CreatureSystem &creature_system,
  ResourceManager &resource_manager
) : transform_system(transform_system),
  creature_system(creature_system),
  resource_manager(resource_manager)
{
  this->state.reset(new GameState());
}

void GameManager::init() {
  for (int i = 0; i < 30; ++i) {
    Entity ent = new_entity();
    this->creature_system.insert(ent);
    this->transform_system.insert(ent);
    this->state->creatures.push_back(ent);

    this->transform_system.set_pos(ent, glm::vec2(rand() % 120 + i * 23 + 180, rand() % 120 + i * 32 + 32));

    CreatureComponent &creature = this->creature_system.get_ref(ent);
    creature.tex = TextureName::test_dog;
  }
}

void GameManager::update(
  double time,
  double delta_time,
  PointerState pointer_state
) {

  for (auto entity : this->state->creatures) {
    glm::vec2 pos = this->transform_system.get_pos(entity);
    pos += glm::vec2(glm::sin(time), glm::cos(time));
    this->transform_system.set_pos(entity, pos);
  }
}

void GameManager::render() {
  for (auto entity : this->state->creatures) {
    glm::vec2 pos = this->transform_system.get_pos(entity);
    const CreatureComponent &creature = this->creature_system.get_ref(entity);

    GRRLIB_texImg *tex = this->resource_manager.tex(creature.tex);

    GRRLIB_DrawImg(pos.x, pos.y, tex, 0, 1, 1, 0xFFFFFFFF);
  }
}
