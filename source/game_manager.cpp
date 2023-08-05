#include "game_manager.hpp"

#include <cstdlib>

#include <grrlib.h>
#undef R


GameManager::GameManager(
  ResourceManager &resource_manager
) : resource_manager(resource_manager)
{
  state.reset(new GameState());
}

void GameManager::init_pregame() {
  Entity ent = new_entity();
  creatures[ent] = CreatureComponent();
  transforms[ent] = TransformComponent {
    .pos = glm::vec2(640/2 - 32, 480 / 3 - 32),
    .angle = 0.f
  };
}

void GameManager::init_park() {
  for (int i = 0; i < 30; ++i) {
    Entity ent = new_entity();
    creatures[ent] = CreatureComponent();
    creatures[ent].excitement = .5f;

    transforms[ent] = TransformComponent {
      .pos = glm::vec2(rand() % 120 + 180, rand() % 120 + 180),
      .angle = 0.f
    };
  }
}

void GameManager::update(
  double time,
  float delta_time,
  PointerState pointer_state
) {

  if (pointer_state.action_pressed && state->holding_creature_entity == 0) {
    // Try to pick up something new

    for (auto &creatures_pair : creatures) {
      Entity ent = creatures_pair.first;

      if (glm::length((transforms[ent].pos + creature_size / 2.f) - pointer_state.pos) < creature_size.x / 2.f) {
        state->holding_creature_entity = ent;
        break;
      }
    }
  }

  if (!pointer_state.action_held && state->holding_creature_entity != 0) {
    // Let go of picked thing

    // if In basket

    // else On ground

    state->holding_creature_entity = 0;
  }

  // Move creatures
  for (auto creatures_pair : creatures) {
    Entity ent = creatures_pair.first;

    if (state->holding_creature_entity != ent) {
      // Normal roaming creature
      transforms[ent].pos += glm::vec2(glm::sin(time / 8.f), glm::cos(time / 7.f)) * 20.f * delta_time;
    } else {
      // Picked creature
      transforms[ent].pos = pointer_state.pos;
    }
  }
}

void GameManager::render() {
  for (auto creatures_pair : creatures) {
    const TransformComponent &trans = transforms.at(creatures_pair.first);
    const CreatureComponent &creature = creatures_pair.second;

    GRRLIB_texImg *tex = resource_manager.tex(creature.tex);

    GRRLIB_DrawImg((int)trans.pos.x, (int)trans.pos.y, tex, 0, 1, 1, 0xFFFFFFFF);
  }
}
