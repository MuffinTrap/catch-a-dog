#pragma once

bool point_in_box(glm::vec2 point, glm::vec2 rect_tl, glm::vec2 rect_size) {
  return (rect_tl.x <= point.x) &&
    (point.x <= rect_tl.x + basket_size.x) &&
    (rect_tl.y <= point.y) &&
    (point.y <= rect_tl.y + rect_size.y);
};
