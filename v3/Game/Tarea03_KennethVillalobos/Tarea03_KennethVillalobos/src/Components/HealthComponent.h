// Copyright 2024 Kenneth Villalobos

#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include <Vector>
#include "../ECS/ECS.h"

struct HealthComponent {
public:
  int maxHealth;
  int currentHealth;
  std::vector<Entity> hearts;

public:
  HealthComponent(const int maxHealth = 1,
    const int currentHealth = 1)
    : maxHealth(maxHealth),
    currentHealth(std::min(currentHealth, maxHealth)),
    hearts(0) {
  };
};

#endif  // HEALTHCOMPONENT_H
