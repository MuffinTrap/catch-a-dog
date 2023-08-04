#include "transform_system.hpp"


TransformSystem::TransformSystem() {
  this->transforms.reserve(200);
}

glm::vec2 TransformSystem::get_pos(Entity entity) const {
  return this->transforms.at(entity).pos;
}

void TransformSystem::set_pos(Entity entity, glm::vec2 pos) {
  this->transforms[entity].pos = pos;
}
