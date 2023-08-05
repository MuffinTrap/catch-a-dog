#pragma once

bool point_in_box(glm::vec2 point, glm::vec2 rect_tl, glm::vec2 rect_size) {
  return (point.x >= rect_tl.x) &&
    (point.x <= rect_tl.x + rect_size.x) &&
    (point.y >= rect_tl.y) &&
    (point.y <= rect_tl.y + rect_size.y);
};
