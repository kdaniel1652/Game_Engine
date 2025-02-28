// Copyright 2024, Kenneth Villalobos

#include "CollisionSystem.h"
#include "../Components/CircleColliderComponent.h"
#include "../Components/RespawnComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "../Events/CollisionEvent.h"

#include "../Utils/common.h"

CollisionSystem::CollisionSystem() {
  this->requireComponent<TransformComponent>();
  this->requireComponent<SpriteComponent>();
  this->requireComponent<CircleColliderComponent>();
}

void CollisionSystem::update(std::shared_ptr<EventManager>& eventManager) {
  auto entities = this->getSystemEntities();
  for (auto i = entities.begin(); i != entities.end(); ++i) {
    auto first = *i;
    if (!first.hasComponent<RespawnComponent>() ||
      (!first.getComponent<RespawnComponent>().defeated &&
        first.getComponent<RespawnComponent>().msSinceRespawn >=
        MS_GRACE_TIME)) {
      auto& firstCollider = first.getComponent<CircleColliderComponent>();
      auto& firstTransform = first.getComponent<TransformComponent>();
      auto& firstSprite = first.getComponent<SpriteComponent>();

      for (auto j = i; j != entities.end(); j++) {
        auto second = *j;

        if (first != second &&
          (!second.hasComponent<RespawnComponent>() ||
            !second.getComponent<RespawnComponent>().defeated)) {
          auto& secondCollider = second.getComponent<CircleColliderComponent>();
          auto& secondTransform = second.getComponent<TransformComponent>();
          auto& secondSprite = second.getComponent<SpriteComponent>();

          const glm::vec2 firstCenter = glm::vec2(
            firstTransform.position.x +
            (firstSprite.width * firstTransform.scale.x),
            firstTransform.position.y +
            (firstSprite.height * firstTransform.scale.y));

          const glm::vec2 secondCenter = glm::vec2(
            secondTransform.position.x +
            (secondSprite.width * secondTransform.scale.x),
            secondTransform.position.y +
            (secondSprite.height * secondTransform.scale.y));

          const bool collision = this->checkCircleCollision(firstCollider.radius,
            firstCenter, secondCollider.radius, secondCenter);

          if (collision) {
            eventManager->emitEvent<CollisionEvent>(first, second, eventManager);
          }
        }
      }
    }
  }
}

bool CollisionSystem::checkCircleCollision(const float firstRadius,
  const glm::vec2& firstCenter, const float secondRadius,
  const glm::vec2& secondCenter) {
  const glm::vec2 diff = firstCenter - secondCenter;
  const float length = glm::length(diff);

  return (firstRadius + secondRadius) >= length;
}
