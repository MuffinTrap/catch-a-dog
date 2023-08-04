#pragma once

#include <unordered_map>

#include "entity.hpp"
#include "resource_manager.hpp"

struct CreatureComponent {
  TextureName tex = TextureName::test_dog;
  float excitement = 0.f;
};

class CreatureSystem
{
public:
  CreatureSystem();

  void insert(Entity entity) { creatures.insert_or_assign(entity, CreatureComponent()); };
  void remove(Entity entity) { creatures.erase(entity); };

  CreatureComponent &get_ref(Entity entity);

private:
  std::unordered_map<Entity, CreatureComponent> creatures;
};
