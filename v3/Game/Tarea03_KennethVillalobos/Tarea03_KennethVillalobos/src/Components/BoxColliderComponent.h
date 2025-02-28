// Copyright 2024 Kenneth Villalobos

#ifndef BOXCOLLIDERCOMPONENT_H
#define BOXCOLLIDERCOMPONENT_H

#include <glm/glm.hpp>

struct BoxColliderComponent {
public:
  int width;
  int height;
  glm::vec2 offset;

public:
  BoxColliderComponent(const int width = 0, const int height = 0,
    const glm::vec2& offset = glm::vec2(0))
    : width(width),
    height(height),
    offset(offset) {
  };
};

#endif  // BOXCOLLIDERCOMPONENT_H
