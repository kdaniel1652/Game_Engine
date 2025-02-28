// Copyright 2024, Kenneth Villalobos

#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <glm/glm.hpp>

struct TransformComponent {
public:
  glm::vec2 position;
  glm::vec2 scale;
  float rotation;

public:
  TransformComponent(const glm::vec2& position = glm::vec2(0),
    const glm::vec2& scale = glm::vec2(1, 1), const float rotation = 0.0)
    : position(position),
    scale(scale),
    rotation(rotation) {
  };
};

#endif  // TRANSFORMCOMPONENT_H
