// Copyright 2024 Kenneth Villalobos

#include <algorithm>
#include <cmath>
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "MovementSystem.h"
#include "../Util/common.h"

MovementSystem::MovementSystem() {
  this->requireComponent<RigidBodyComponent>();
  this->requireComponent<TransformComponent>();
}

void MovementSystem::update(const float deltaTime) {
  for (auto entity : this->getSystemEntities()) {
    auto& rigidBody = entity.getComponent<RigidBodyComponent>();
    auto& transform = entity.getComponent<TransformComponent>();

    rigidBody.velocity += (rigidBody.sumForces * deltaTime);

    rigidBody.onGround = (rigidBody.velocity.y == 0);

    transform.previousPosition = transform.position;
    transform.position += rigidBody.velocity * deltaTime;

    rigidBody.sumForces = glm::vec2(0);
  }
}

float MovementSystem::terminalVelocity(const Entity& entity) {
  const auto& rigidBody = entity.getComponent<RigidBodyComponent>();

  float crossSectional = 1024;
  if (entity.hasComponent<SpriteComponent>() &&
    entity.hasComponent<TransformComponent>()) {
    const auto& transform = entity.getComponent<TransformComponent>();
    const auto& sprite = entity.getComponent<SpriteComponent>();

    crossSectional = sprite.width * transform.scale.x *
      sprite.height * transform.scale.y;
  }

  return std::sqrt(
    (2 * rigidBody.mass * constants::GRAVITY) /
    (constants::AIR_DENSITY * constants::DRAG_COEFFICIENT * crossSectional)) *
    constants::PIXELS_PER_METER;
}
