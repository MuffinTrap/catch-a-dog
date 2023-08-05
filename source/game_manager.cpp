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
  // Logo
  {
    Entity ent = new_entity();
    transforms[ent] = TransformComponent();
    transforms[ent].pos = glm::vec2(640 / 2 - 128, 480 / 2 - 192);
    renderables[ent] = RenderableComponent();
    renderables[ent].frames = { TextureName::titlescreen_logo };
    renderables[ent].layer = RenderLayer_menu;

    state->logo_entity = ent;
  }

  // Turorial dog
  {
    Entity ent = new_entity();
    creatures[ent] = CreatureComponent();
    creatures[ent].excitement = 0.f;
    transforms[ent] = TransformComponent {
      .pos = glm::vec2(640/2 - 32, 480 - 480 / 4),
      .angle = 0.f
    };
    renderables[ent] = RenderableComponent();
    renderables[ent].frames = { TextureName::dog1_1, TextureName::dog1_2 };
    renderables[ent].layer = RenderLayer_park;
  }
}

void GameManager::init_park() {
  for (int i = 0; i < 30; ++i) {
    Entity ent = new_entity();
    creatures[ent] = CreatureComponent();
    creatures[ent].excitement = .5f;
    creatures[ent].heading = glm::normalize(glm::vec2(rand() % 256 - 128, rand() % 256 - 128));

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
    CreatureComponent &creature = creatures[ent];

    if (state->holding_creature_entity == ent) {
      // Picked creature
      transforms[ent].pos = pointer_state.pos - glm::vec2(32, 16);
    } else if (is_in_basket(ent)) {
      // Stay still in basket
    } else {
      // Normal roaming creature
      transforms[ent].pos += creature.heading * 60.f * delta_time * creature.excitement;

      if (transforms[ent].pos.x < 64 || transforms[ent].pos.x > 640 - 64) {
        transforms[ent].pos.x = std::max(64.f, std::min(transforms[ent].pos.x, 640.f - 64.f));
        creature.heading.x = -creature.heading.x;
      }

      if (transforms[ent].pos.y < 64 || transforms[ent].pos.y > 480 - 64) {
        transforms[ent].pos.y = std::max(64.f, std::min(transforms[ent].pos.y, 480.f - 64.f));
        creature.heading.y = -creature.heading.y;
      }

      // fffuuuuuuu.... texture anchor point changes when flipping.... argh...
      //renderables[ent].scale_x = creature.heading.x < 0.f ? 1 : -1;
    }
  }

  // Scan basket
  if (state->phase == GamePhase::intro) {
    if (state->basket_creatures.size() > 0) {
      init_park();
      state->phase = GamePhase::park;
    }
  }

  if (state->phase == GamePhase::park) {
    transforms[state->logo_entity].pos -= glm::vec2(0, 1) * 256.f * delta_time;
    if (transforms[state->logo_entity].pos.y < -512.f) {
      renderables.erase(state->logo_entity);
    }
  }
}

void GameManager::draw(TextureName tex_name, glm::vec2 pos, int scale_x, int scale_y) {
  GRRLIB_texImg *tex = resource_manager.tex(tex_name);
  GRRLIB_DrawImg(pos.x, pos.y, tex, 0, scale_x, scale_y, 0xFFFFFFFF);
}

struct RenderCommand {
  TextureName tex_name;
  glm::vec2 pos;
  int layer = 0;
  float layer_sort_value = 0.f;
  int scale_x = 1;
  int scale_y = 1;
};

void GameManager::render(const PointerState &pointer_state) {
  static std::vector<RenderCommand> render_queue;
  render_queue.reserve(256);
  render_queue.clear();

  for (auto renderables_pair : renderables) {
    const TransformComponent &trans = transforms.at(renderables_pair.first);
    const RenderableComponent &renderable = renderables_pair.second;

    render_queue.push_back(RenderCommand {
      .tex_name = renderable.frames[rand() % renderable.frames.size()],
      .pos = trans.pos,
      .layer = renderable.layer,
      .layer_sort_value = trans.pos.y - 64.f, // TODO piiskaa pitäisi antaa
      .scale_x = renderable.scale_x,
      .scale_y = renderable.scale_y,
    });
  }

  std::sort(render_queue.begin(), render_queue.end(), [&](const RenderCommand &a, const RenderCommand &b){
    auto score = [&](const RenderCommand &c) -> float { return c.layer * 1000.f + c.layer_sort_value; };
    return score(a) < score(b);
  });

  auto draw_command = [&](const RenderCommand &cmd) {
    draw(cmd.tex_name, cmd.pos, cmd.scale_x, cmd.scale_y);
  };

  size_t ri = 0;

  draw(TextureName::background, glm::vec2(0,0));

  for (;render_queue[ri].layer <= RenderLayer_park && ri < render_queue.size(); ++ri) {
    draw_command(render_queue[ri]);
  }

  draw(TextureName::basket_back, basket_pos);

  for (;render_queue[ri].layer <= RenderLayer_basket_in && ri < render_queue.size(); ++ri) {
    draw_command(render_queue[ri]);
  }

  draw(TextureName::basket_front, basket_pos + glm::vec2(0, basket_size.y / 2.f));

  for (; ri < render_queue.size(); ++ri) {
    draw_command(render_queue[ri]);
  }

  draw(pointer_state.action_held ? TextureName::pointer_down : TextureName::pointer_open, pointer_state.pos - glm::vec2(32, 32));

  GRRLIB_Rectangle(basket_pos.x, basket_pos.y, basket_size.x, basket_size.y, 0xFFFFFFFF, 0);
}
