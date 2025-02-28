// Copyright 2024 Kenneth Villalobos

#ifndef WEIGHTFORCESYSTEM_H
#define WEIGHTFORCESYSTEM_H

#include "../ECS/ECS.h"

class WeightForceSystem : public System {
public:
  WeightForceSystem();

  void update();
};

#endif  // WEIGHTFORCESYSTEM_H
