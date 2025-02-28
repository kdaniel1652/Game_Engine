// Copyright 2024 Kenneth Villalobos

#ifndef CLEANINGSYSTEM_H
#define CLEANINGSYSTEM_H

#include "../ECS/ECS.h"
#include <sol/sol.hpp>

class CleaningSystem : public System {
public:
  CleaningSystem();

  void update(sol::state& lua);
};

#endif  // CLEANINGSYSTEM_H
