#pragma once

#include <memory>
#include <vector>
#include <unordered_map>

#include "glm/glm.hpp"

#include "DebugPrinter.hpp"
#include "resource_manager.hpp"
#include "entity.hpp"
#include "creature_definitions.hpp"


const glm::vec2 creature_size = glm::vec2(64, 64);
const glm::vec2 basket_size { 256, 256 };
const glm::vec2 basket_pos { -16, 480 - basket_size.y + 16 };
const float basket_action_radius = 64.f;
const glm::vec2 basket_action_offset = glm::vec2(basket_size.x / 2.f, basket_size.y / 2.f + 32.f);
const float anim_frame_interval = 0.25f;

struct PointerState {
  glm::vec2 pos;
  bool action_held = false;
  bool action_pressed = false;
};

enum class GamePhase {
  intro,
  park,
  end,
};

enum RenderLayers : uint8_t {
  RenderLayer_bg = 0,
  RenderLayer_park = 10,
  RenderLayer_basket_bg = 20,
  RenderLayer_basket_in = 25,
  RenderLayer_picked = 30,
  RenderLayer_basket_fg = 40,
  RenderLayer_menu = 50,
  RenderLayer_pointer = 60
};

struct GameState {
  GamePhase phase = GamePhase::intro;

  static const int park_creature_amount = 30;
  static const int target_creature_amount = 3;

  Entity logo_entity = 0;

  Entity holding_creature_entity = 0;
  Entity target_creatures[target_creature_amount];
  Entity basket_creatures[park_creature_amount];

  size_t anim_frame_counter = 0;
  double anim_frame_last = 0.f;

  int spawned_dogs_count = 0;
  int collected_dogs = 0;
  int collected_nondogs = 0;
};

struct TransformComponent {
  glm::vec2 pos;
  float angle = 0.f;
};

struct CreatureComponent {
  float excitement = 1.f;
  glm::vec2 heading;
  CreatureCategory category = CreatureCategory::not_dog;
};

struct RenderableComponent {
  std::vector<TextureName> frames;
  int layer = 0;
  int scale_x = 1;
  int scale_y = 1;
};

// This is the thing that drives the whole game
class GameManager {
public:
  GameManager(ResourceManager &resource_manager, DebugPrinter &debug_printer);

  void init_pregame();
  void init_park();
  void init_end();

  void update(
    double time,
    float delta_time,
    const PointerState &pointer_state
  );

  bool is_in_basket(Entity entity) const;
  void put_in_basket(Entity entity);
  int get_amount_in_basket() const;

  bool is_in_targets(TextureName textureName);
  int get_amount_targets() const;
  bool try_remove_from_targets(TextureName textureName);

  void render(const PointerState &pointer_state);

private:
  Entity add_creature_from_definition(const CreatureDefinition &def);

  void draw(TextureName tex_name, glm::vec2 pos, int scale_x = 1, int scale_y = 1, int tint = 0xFFFFFFFF);
  void playfx(SoundName sound_name);

  std::unique_ptr<GameState> state;
  std::unordered_map<Entity, TransformComponent> transforms;
  std::unordered_map<Entity, CreatureComponent> creatures;
  std::unordered_map<Entity, RenderableComponent> renderables;

  GRRLIB_texImg *end_screen_font = NULL;
  TransformComponent end_message_transform;
  ResourceManager &resource_manager;
  DebugPrinter &debug_printer;
};
