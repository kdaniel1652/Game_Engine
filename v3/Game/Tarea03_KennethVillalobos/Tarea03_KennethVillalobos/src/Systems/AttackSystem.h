// Copyright 2024 Kenneth Villalobos

#ifndef ATTACKSYSTEM_H
#define ATTACKSYSTEM_H

#include "../ECS/ECS.h"
#include <glm/glm.hpp>
#include <sol/sol.hpp>


class AttackSystem : public System {
public:
  AttackSystem();

  void update(sol::state& lua);
};

#endif  // ATTACKSYSTEM_H
