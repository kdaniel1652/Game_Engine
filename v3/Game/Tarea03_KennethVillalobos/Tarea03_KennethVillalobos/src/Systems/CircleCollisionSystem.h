// Copyright 2024 Kenneth Villalobos

#ifndef CIRCLECOLLISIONSYSTEM_H
#define CIRCLECOLLISIONSYSTEM_H

#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include <glm/glm.hpp>
#include <memory>

class CircleCollisionSystem : public System {
public:
  CircleCollisionSystem();

  void update(std::shared_ptr<EventManager>& eventManager);
  bool checkCircleCollision(const float firstRadius,
    const glm::vec2& firstCenter, const float secondRadius,
    const glm::vec2& secondCenter);
};

#endif  // CIRCLECOLLISIONSYSTEM_H
