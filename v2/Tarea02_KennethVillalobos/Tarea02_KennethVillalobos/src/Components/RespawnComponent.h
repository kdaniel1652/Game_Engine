// Copyright 2024, Kenneth Villalobos

#ifndef RESPAWNCOMPONENT_H
#define RESPAWNCOMPONENT_H

#include <glm/glm.hpp>
#include <string>

#include "../ECS/ECS.h"

#include "../Utils/common.h"

struct RespawnComponent {
public:
  bool defeated;
  int msToRespawn;
  int msSinceDefeat;
  int msSinceRespawn;

  glm::vec2 respawnPosition;

  Entity forceField;

public:
  explicit RespawnComponent(const int msToRespawn = 3000,
    const glm::vec2 respawnPosition = glm::vec2(0),
    const Entity& forceField = Entity(0))
    : defeated(false),
    msToRespawn(msToRespawn),
    msSinceDefeat(0),
    msSinceRespawn(MS_GRACE_TIME),
    respawnPosition(respawnPosition),
    forceField(forceField) {
  };
};

#endif  // RESPAWNCOMPONENT_H
