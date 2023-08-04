#pragma once

#include <unordered_map>

#include "entity.hpp"
#include "resource_manager.hpp"

struct CreatureComponent {
  TextureName tex;
  float excitement = 0.f;
};

class CreatureSystem
{
public:
  CreatureSystem();
  void update(double time, double deltaTime);

  void insert(Entity entity) { creatures.insert_or_assign(entity, CreatureComponent()); };
  void remove(Entity entity) { creatures.erase(entity); };

private:
  std::unordered_map<Entity, CreatureComponent> creatures;
};
