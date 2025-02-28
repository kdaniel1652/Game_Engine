// Copyright 2024 Kenneth Villalobos

#ifndef BOXCOLLISIONSYSTEM_H
#define BOXCOLLISIONSYSTEM_H

#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include <glm/glm.hpp>
#include <memory>
#include <sol/sol.hpp>

typedef enum Direction {
  down = 0,
  up,
  left,
  right
} CollisionDirection;

class BoxCollisionSystem : public System {
public:
  BoxCollisionSystem();

  void update(std::shared_ptr<EventManager>& eventManager,
    sol::state& lua);
  static bool checkAABBCollision(const glm::vec2 aPosition,
    const float aWidth, const float aHeight, const glm::vec2 bPosition,
    const float bWidth, const float bHeight);
  bool canCollide(const Entity& a, const Entity& b) const;
  static bool checkCollisionDirection(const Entity& a, const Entity& b,
    const CollisionDirection direction);
};

#endif  // BOXCOLLISIONSYSTEM_H
