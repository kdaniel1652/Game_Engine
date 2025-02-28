// Copyright 2024, Kenneth Villalobos

#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include <glm/glm.hpp>
#include <memory>

#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"

class CollisionSystem : public System {
public:
  CollisionSystem();

  void update(std::shared_ptr<EventManager>& eventManager);
  bool checkCircleCollision(const float firstRadius,
    const glm::vec2& firstCenter, const float secondRadius,
    const glm::vec2& secondCenter);
};

#endif  // COLLISIONSYSTEM_H
