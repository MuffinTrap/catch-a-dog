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
  renderables[ent] = RenderableComponent();
  renderables[ent].frames = { TextureName::dog1_1, TextureName::dog1_2 };
  renderables[ent].layer = RenderLayer_park;
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

    renderables[ent] = RenderableComponent();
    renderables[ent].frames = { TextureName::dog1_1, TextureName::dog1_2 };
    renderables[ent].layer = RenderLayer_park;
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
  const PointerState &pointer_state
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
        renderables[ent].layer = RenderLayer_picked;
        break;
      }
    }
  }

  if (!pointer_state.action_held && state->holding_creature_entity != 0) {
    // Let go of picked thing

    // if In basket
    if (glm::length(pointer_state.pos - (basket_pos + basket_action_offset)) < basket_action_radius) {
      state->basket_creatures.push_back(state->holding_creature_entity);
      renderables[state->holding_creature_entity].layer = RenderLayer_basket_in;
    }

    // else On ground
    renderables[state->holding_creature_entity].layer = RenderLayer_basket_in;
    state->holding_creature_entity = 0;
  }

  // Move creatures
  for (auto creatures_pair : creatures) {
    Entity ent = creatures_pair.first;

    if (state->holding_creature_entity == ent) {
      // Picked creature
      transforms[ent].pos = pointer_state.pos - glm::vec2(32, 16);
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

void GameManager::draw(TextureName tex_name, glm::vec2 pos) {
  GRRLIB_texImg *tex = resource_manager.tex(tex_name);
  GRRLIB_DrawImg(pos.x, pos.y, tex, 0, 1, 1, 0xFFFFFFFF);
}

struct RenderEnqueuedTex {
  TextureName tex_name;
  glm::vec2 pos;
  int layer = 0;
  float layer_sort_value = 0.f;
};

void GameManager::render(const PointerState &pointer_state) {
  static std::vector<RenderEnqueuedTex> render_queue;
  render_queue.reserve(256);
  render_queue.clear();

  for (auto renderables_pair : renderables) {
    const TransformComponent &trans = transforms.at(renderables_pair.first);
    const RenderableComponent &renderable = renderables_pair.second;

    render_queue.push_back(RenderEnqueuedTex {
      .tex_name = renderable.frames[rand() % renderable.frames.size()],
      .pos = trans.pos,
      .layer = renderable.layer,
      .layer_sort_value = trans.pos.y - 64.f // TODO piiskaa pitäisi antaa
    });
  }

  std::sort(render_queue.begin(), render_queue.end(), [&](const RenderEnqueuedTex &a, const RenderEnqueuedTex &b){
    auto score = [&](const RenderEnqueuedTex &c) -> float { return c.layer * 1000.f + c.layer_sort_value; };
    return score(a) < score(b);
  });

  size_t ri = 0;

  draw(TextureName::background, glm::vec2(0,0));

  for (;render_queue[ri].layer <= RenderLayer_park && ri < render_queue.size(); ++ri) {
    draw(render_queue[ri].tex_name, render_queue[ri].pos);
  }

  draw(TextureName::basket_back, basket_pos);

  for (;render_queue[ri].layer <= RenderLayer_basket_in && ri < render_queue.size(); ++ri) {
    draw(render_queue[ri].tex_name, render_queue[ri].pos);
  }

  draw(TextureName::basket_front, basket_pos + glm::vec2(0, basket_size.y / 2.f));

  for (; ri < render_queue.size(); ++ri) {
    draw(render_queue[ri].tex_name, render_queue[ri].pos);
  }

  draw(pointer_state.action_held ? TextureName::pointer_down : TextureName::pointer_open, pointer_state.pos - glm::vec2(32, 32));

  GRRLIB_Rectangle(basket_pos.x, basket_pos.y, basket_size.x, basket_size.y, 0xFFFFFFFF, 0);
}
