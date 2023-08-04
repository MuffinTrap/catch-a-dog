#pragma once

#include <unordered_map>

#include "glm/glm.hpp"
#include "entity.hpp"

struct TransformComponent
{
  glm::vec2 pos;
  float angle = 0.f;
};


class TransformSystem {
public:
  TransformSystem();

  void insert(Entity entity) { transforms.insert_or_assign(entity, TransformComponent()); };
  void remove(Entity entity) { transforms.erase(entity); };

  glm::vec2 get_pos(Entity entity) const;
  void set_pos(Entity entity, glm::vec2 pos);

private:
  std::unordered_map<Entity, TransformComponent> transforms;
};
