// Copyright 2024 Kenneth Villalobos

#include "CircleCollisionSystem.h"
#include "../Components/CircleColliderComponent.h"
#include "../Components/TransformComponent.h"
#include "../Events/CollisionEvent.h"

CircleCollisionSystem::CircleCollisionSystem() {
  this->requireComponent<CircleColliderComponent>();
  this->requireComponent<TransformComponent>();
}

void CircleCollisionSystem::update(std::shared_ptr<EventManager>& eventManager) {
  auto entities = this->getSystemEntities();
  for (auto i = entities.begin(); i != entities.end(); ++i) {
    auto first = *i;
    const auto& firstCollider = first.getComponent<CircleColliderComponent>();
    const auto& firstTransform = first.getComponent<TransformComponent>();

    for (auto j = i; j != entities.end(); j++) {
      auto second = *j;

      if (first != second) {
        const auto& secondCollider =
          second.getComponent<CircleColliderComponent>();
        const auto& secondTransform =
          second.getComponent<TransformComponent>();

        const glm::vec2 firstCenter = glm::vec2(
          firstTransform.position.x + 16, firstTransform.position.y + 16);

        const glm::vec2 secondCenter = glm::vec2(
          secondTransform.position.x + 16, secondTransform.position.y + 16);

        const bool collision = this->checkCircleCollision(firstCollider.radius,
          firstCenter, secondCollider.radius, secondCenter);

        if (collision) {
          eventManager->emitEvent<CollisionEvent>(first, second);
        }
      }
    }
  }
}

bool CircleCollisionSystem::checkCircleCollision(const float firstRadius,
  const glm::vec2& firstCenter, const float secondRadius,
  const glm::vec2& secondCenter) {
  const glm::vec2 diff = firstCenter - secondCenter;
  const float length = glm::length(diff);

  return (firstRadius + secondRadius) >= length;
}
