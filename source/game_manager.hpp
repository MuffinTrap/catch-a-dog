#pragma once

#include <memory>
#include <vector>
#include <unordered_map>

#include "glm/glm.hpp"

#include "resource_manager.hpp"
#include "entity.hpp"

struct PointerState {
  glm::vec2 pos;
  bool action_held = false;
};

struct GameState {
  bool logo_show = true;
  glm::vec2 logo_pos { 640 / 2 - 128, 480 / 2 - 128 };

  glm::vec2 basket_pos { 64, 128 };
  glm::vec2 basket_extent { 64, 64 };
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

  void init();

  void update(
    double time,
    double delta_time,
    PointerState pointer_state
  );

  void render();

private:
  std::unique_ptr<GameState> state;
  std::unordered_map<Entity, TransformComponent> transforms;
  std::unordered_map<Entity, CreatureComponent> creatures;

  ResourceManager &resource_manager;
};
