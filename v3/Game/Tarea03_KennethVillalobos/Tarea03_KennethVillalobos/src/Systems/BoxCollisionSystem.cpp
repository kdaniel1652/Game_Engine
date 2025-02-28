// Copyright 2024 Kenneth Villalobos

#include "BoxCollisionSystem.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/ScriptComponent.h"
#include "../Components/TransformComponent.h"
#include "../Events/CollisionEvent.h"

BoxCollisionSystem::BoxCollisionSystem() {
  this->requireComponent<BoxColliderComponent>();
  this->requireComponent<TransformComponent>();
}

void BoxCollisionSystem::update(std::shared_ptr<EventManager>& eventManager,
  sol::state& lua) {
  auto entities = this->getSystemEntities();
  for (auto i = entities.begin(); i != entities.end(); ++i) {
    auto a = *i;
    const auto& aCollider = a.getComponent<BoxColliderComponent>();
    const auto& aTransform = a.getComponent<TransformComponent>();

    for (auto j = i; j != entities.end(); j++) {
      auto b = *j;

      if (a != b && this->canCollide(a, b)) {
        const auto& bCollider = b.getComponent<BoxColliderComponent>();
        const auto& bTransform = b.getComponent<TransformComponent>();
 
        const bool collision = this->checkAABBCollision(
          aTransform.position + aCollider.offset,
          static_cast<float>(aCollider.width),
          static_cast<float>(aCollider.height),
          bTransform.position + bCollider.offset,
          static_cast<float>(bCollider.width),
          static_cast<float>(bCollider.height)
        );

        if (collision) {
          eventManager->emitEvent<CollisionEvent>(a, b);

          if (a.hasComponent<ScriptComponent>()) {
            const auto& scriptA = a.getComponent<ScriptComponent>();
            if (scriptA.onCollision != sol::nil) {
              lua["this"] = a;
              scriptA.onCollision(b);
            }
          }

          if (b.hasComponent<ScriptComponent>()) {
            const auto& scriptB = b.getComponent<ScriptComponent>();
            if (scriptB.onCollision != sol::nil) {
              lua["this"] = b;
              scriptB.onCollision(a);
            }
          }
        }
      }
    }
  }
}

bool BoxCollisionSystem::checkAABBCollision(const glm::vec2 aPosition,
  const float aWidth, const float aHeight, const glm::vec2 bPosition,
  const float bWidth, const float bHeight) {
  return (
    aPosition.x < bPosition.x + bWidth &&
    aPosition.x + aWidth > bPosition.x &&
    aPosition.y < bPosition.y + bHeight &&
    aPosition.y + aHeight > bPosition.y
  );
}

bool BoxCollisionSystem::canCollide(const Entity& a,
  const Entity& b) const {
  bool aCanColiide = a.hasComponent<RigidBodyComponent>();
  bool bCanCollide = b.hasComponent<RigidBodyComponent>();

  return aCanColiide || bCanCollide;
}

bool BoxCollisionSystem::checkCollisionDirection(const Entity& a,
  const Entity& b, const CollisionDirection direction) {
  const auto& aTransform = a.getComponent<TransformComponent>();
  const auto& aCollider = a.getComponent<BoxColliderComponent>();
  const auto& bTransform = b.getComponent<TransformComponent>();
  const auto& bCollider = b.getComponent<BoxColliderComponent>();

  const float aX = aTransform.previousPosition.x + aCollider.offset.x;
  const float aY = aTransform.previousPosition.y + aCollider.offset.y;
  const float bX = bTransform.previousPosition.x + bCollider.offset.x;
  const float bY = bTransform.previousPosition.y + bCollider.offset.y;
  bool collision = false;

  if (direction == Direction::down || direction == Direction::up) {
    const float aWidth = static_cast<float>(aCollider.width);
    const float bWidth = static_cast<float>(bCollider.width);

    collision = (
      aX < bX + bWidth &&
      aX + aWidth > bX
      );

    collision = (direction == Direction::up) ?
      (collision && aY < bY) : (collision && aY > bY);

  }
  else if (direction == Direction::left || direction == Direction::right) {
    const float aHeight = static_cast<float>(aCollider.height);
    const float bHeight = static_cast<float>(bCollider.height);

    collision = (
      aY < bY + bHeight &&
      aY + aHeight > bY
      );

    collision = (direction == Direction::right) ?
      (collision && aX > bX) : (collision && aX < bX);
  }

  return collision;
}
