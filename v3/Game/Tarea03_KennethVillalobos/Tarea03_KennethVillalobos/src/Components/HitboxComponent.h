// Copyright 2024 Kenneth Villalobos

#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H

#include <glm/glm.hpp>

struct HitBoxComponent {
public:
  bool active = false;
  int damage;
  int width;
  int height;
  glm::vec2 offset;

public:
  HitBoxComponent(const int damage = 0, const int width = 0,
    const int height = 0, const glm::vec2& offset = glm::vec2(0))
    : damage(damage),
    width(width),
    height(height),
    offset(offset) {
  };
};

#endif  // HITBOXCOMPONENT_H
