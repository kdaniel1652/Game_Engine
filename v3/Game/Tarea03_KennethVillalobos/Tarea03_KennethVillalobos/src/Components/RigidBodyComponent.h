// Copyright 2024 Kenneth Villalobos

#ifndef RIGIDBODYCOMPONENT_H
#define RIGIDBODYCOMPONENT_H

#include <glm/glm.hpp>

struct RigidBodyComponent {
public:
  glm::vec2 sumForces = glm::vec2(0);
  glm::vec2 velocity = glm::vec2(0);
  float mass;
  bool onGround = false;
  bool isStatic;

public:
  RigidBodyComponent(const float mass = 0.001f, const bool isStatic = false)
    : mass(mass),
    isStatic(isStatic) {
  }  
};

#endif  // RIGIDBODYCOMPONENT_H