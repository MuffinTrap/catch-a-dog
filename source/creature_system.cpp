#include "creature_system.hpp"

CreatureSystem::CreatureSystem() {
  this->creatures.reserve(200);
}

void CreatureSystem::update(double time, double deltaTime) {
  for (auto& [entity, creature] : this->creatures) {

  }
}
