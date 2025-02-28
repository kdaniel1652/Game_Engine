// Copyright 2024 Kenneth Villalobos

#ifndef SCRIPTSYSTEM_H
#define SCRIPTSYSTEM_H

#include "../ECS/ECS.h"
#include <sol/sol.hpp>

class ScriptSystem : public System {
public:
  ScriptSystem();

  void createLuaBindings(sol::state& lua);
  void awake(sol::state& lua, std::set<Entity>& entities);
  void update(sol::state& lua);

private:
  void createLuaClasses(sol::state& lua);
};

#endif  // SCRIPTSYSTEM_H
