#include "creature_system.hpp"

CreatureSystem::CreatureSystem() {
  this->creatures.reserve(200);
}

CreatureComponent &CreatureSystem::get_ref(Entity entity) {
  return this->creatures.at(entity);
}
