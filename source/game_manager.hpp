#pragma once

#include <memory>
#include <vector>

#include "glm/glm.hpp"

#include "entity.hpp"
#include "creature_system.hpp"
#include "transform_system.hpp"

struct PointerState {
  glm::vec2 pos;
  bool action_held = false;
};

struct GameState {
  bool logo_show = true;
  glm::vec2 logo_pos { 640 / 2 - 128, 480 / 2 - 128 };

  glm::vec2 basket_pos { 64, 128 };
  glm::vec2 basket_extent { 64, 64 };

  std::vector<Entity> creatures;
};

// This is the thing that drives the whole game
class GameManager {
public:
  GameManager(
    TransformSystem &transform_system,
    CreatureSystem &creature_system,
    ResourceManager &resource_manager
  );

  void init();

  void update(
    double time,
    double delta_time,
    PointerState pointer_state
  );

  void render();

private:
  std::unique_ptr<GameState> state;

  TransformSystem &transform_system;
  CreatureSystem &creature_system;
  ResourceManager &resource_manager;
};
