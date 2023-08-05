#include "game_manager.hpp"

#include <cstdlib>
#include <algorithm>

#include <grrlib.h>
#undef R

#include "util.hpp"


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

bool GameManager::is_in_basket(Entity entity) const {
  return std::find(
      state->basket_creatures.begin(),
      state->basket_creatures.end(),
      entity)
    != state->basket_creatures.end();
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

      if (is_in_basket(ent)) {
        // Prevent picking from basket
        continue;
      }

      if (point_in_box(pointer_state.pos, transforms[ent].pos, creature_size))
      {
        state->holding_creature_entity = ent;
        break;
      }
    }
  }

  if (!pointer_state.action_held && state->holding_creature_entity != 0) {
    // Let go of picked thing

    // if In basket
    if (point_in_box(pointer_state.pos, basket_pos, basket_size)) {
      state->basket_creatures.push_back(state->holding_creature_entity);
    }

    // else On ground

    state->holding_creature_entity = 0;
  }

  // Move creatures
  for (auto creatures_pair : creatures) {
    Entity ent = creatures_pair.first;

    if (state->holding_creature_entity == ent) {
      // Picked creature
      transforms[ent].pos = pointer_state.pos;
    } else if (is_in_basket(ent)) {
      // Stay still in basket
    } else {
      // Normal roaming creature
      transforms[ent].pos += glm::vec2(glm::sin(time / 8.f), glm::cos(time / 7.f)) * 20.f * delta_time;
    }
  }

  // Scan basket
  if (state->phase == GamePhase::intro) {
    if (state->basket_creatures.size() > 0) {
      init_park();
      state->phase = GamePhase::park;
    }
  }
}

void GameManager::render() {

  GRRLIB_texImg *tex_bg = resource_manager.tex(TextureName::background);
  GRRLIB_DrawImg(0, 0, tex_bg, 0, 1, 1, 0xFFFFFFFF);


  for (auto creatures_pair : creatures) {
    const TransformComponent &trans = transforms.at(creatures_pair.first);
    const CreatureComponent &creature = creatures_pair.second;

    GRRLIB_texImg *tex = resource_manager.tex(creature.tex);

    GRRLIB_DrawImg((int)trans.pos.x, (int)trans.pos.y, tex, 0, 1, 1, 0xFFFFFFFF);
  }
}
