#include "entity.hpp"

Entity new_entity() {
  static uint32_t entity_index = 0;
  return ++entity_index;
}
