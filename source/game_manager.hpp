#pragma once

#include <memory>
#include <vector>
#include <unordered_map>

#include "glm/glm.hpp"

#include "resource_manager.hpp"
#include "entity.hpp"

const glm::vec2 creature_size = glm::vec2(64, 64);
const glm::vec2 basket_size { 128, 128 };
const glm::vec2 basket_pos { 128, 480 - basket_size.y - 64 };

struct PointerState {
  glm::vec2 pos;
  bool action_held = false;
  bool action_pressed = false;
};

enum class GamePhase {
  intro,
  park
};

struct GameState {
  GamePhase phase = GamePhase::intro;

  bool logo_show = true;
  glm::vec2 logo_pos { 640 / 2 - 128, 480 / 2 - 128 };

  Entity holding_creature_entity = 0;
  std::vector<Entity> basket_creatures;
};

struct TransformComponent {
  glm::vec2 pos;
  float angle = 0.f;
};

struct CreatureComponent {
  TextureName tex = TextureName::test_dog;
  float excitement = 0.f;
};

// This is the thing that drives the whole game
class GameManager {
public:
  GameManager(ResourceManager &resource_manager);

  void init_pregame();
  void init_park();

  void update(
    double time,
    float delta_time,
    PointerState pointer_state
  );

  bool is_in_basket(Entity entity) const;

  void render();

private:
  std::unique_ptr<GameState> state;
  std::unordered_map<Entity, TransformComponent> transforms;
  std::unordered_map<Entity, CreatureComponent> creatures;

  ResourceManager &resource_manager;
};
