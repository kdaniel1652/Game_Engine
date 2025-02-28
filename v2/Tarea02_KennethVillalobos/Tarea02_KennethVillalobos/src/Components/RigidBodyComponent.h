// Copyright 2024, Kenneth Villalobos

#ifndef RIGIDBODYCOMPONENT_H
#define RIGIDBODYCOMPONENT_H

#include <glm/glm.hpp>

struct RigidBodyComponent {
public:
  glm::vec2 velocity;
  float speed;
  bool mustStayInbounds;

public:
  explicit RigidBodyComponent(const glm::vec2& velocity = glm::vec2(0),
    const float speed = 0, const bool mustStayInbounds = false)
    :velocity(velocity),
    speed(speed),
    mustStayInbounds(mustStayInbounds) {
  };
};

#endif  // RIGIDBODYCOMPONENT_H
