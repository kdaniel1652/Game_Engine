// Copyright 2024 Kenneth Villalobos

#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../ECS/ECS.h"

class MovementSystem : public System {
public:
  MovementSystem();

  void update(const float deltaTime);

  static float terminalVelocity(const Entity& entity);
};

#endif  // MOVEMENTSYSTEM_H
