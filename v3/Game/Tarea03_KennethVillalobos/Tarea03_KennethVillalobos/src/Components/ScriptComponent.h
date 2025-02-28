// Copyright 2024 Kenneth Villalobos

#ifndef SCRIPTCOMPONENT_H
#define SCRIPTCOMPONENT_H

#include <sol/sol.hpp>

struct ScriptComponent {
  sol::function awake;
  sol::function update;
  sol::function onCollision;
  sol::function onHit;
  sol::function onDeath;

public:
  explicit ScriptComponent(const sol::function& awake = sol::nil,
    const sol::function& update = sol::nil,
    const sol::function& onCollision = sol::nil,
    const sol::function& onHit = sol::nil,
    const sol::function& onDeath = sol::nil)
    : awake(awake),
    update(update),
    onCollision(onCollision),
    onHit(onHit),
    onDeath(onDeath) {
    }
};

#endif  // SCRIPTCOMPONENT_H
