// Copyright 2024, Kenneth Villalobos

#include <cmath>

#include "../Components/BounceComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "../Events/OutOfBoundsEvent.h"
#include "MovementSystem.h"

MovementSystem::MovementSystem() {
  this->requireComponent<TransformComponent>();
  this->requireComponent<RigidBodyComponent>();
  this->requireComponent<SpriteComponent>();
}

void MovementSystem::update(std::shared_ptr<EventManager>& eventManager,
  const float deltaTime, const int xLimit, const int yLimit) {
  for (auto entity : this->getSystemEntities()) {
    auto& sprite = entity.getComponent<SpriteComponent>();
    auto& rigidBody = entity.getComponent<RigidBodyComponent>();
    auto& transform = entity.getComponent<TransformComponent>();

    transform.position += rigidBody.velocity * deltaTime;

    const float xSpace =
      transform.position.x + (sprite.width * transform.scale.x);
    const float ySpace =
      transform.position.y + (sprite.height * transform.scale.y);

    if (transform.position.x <= 0 ||
      transform.position.y <= 0 ||
      xSpace >= xLimit ||
      ySpace >= yLimit) {

      if (rigidBody.mustStayInbounds) {
        if (transform.position.x <= 0 ||
          xSpace >= xLimit) {
          transform.position.x = (transform.position.x <= 0) ?
            0 : xLimit - (sprite.width * transform.scale.x);
        }

        if (transform.position.y <= 0 ||
          ySpace >= yLimit) {
          transform.position.y = (transform.position.y <= 0) ?
            0 : yLimit - (sprite.height * transform.scale.y);
        }

        if (entity.hasComponent<BounceComponent>()) {
          auto& bounce = entity.getComponent<BounceComponent>();

          if (rigidBody.velocity.x != 0 &&
            (xSpace >= xLimit ||
            (transform.position.x -
              sprite.width * transform.scale.x * 0.10f) <= 0)) {
              rigidBody.velocity.x *= (std::abs(rigidBody.velocity.x) >= 800 )?
                -1 : -bounce.bounceSpeedup;
          }
          if (rigidBody.velocity.y != 0 &&
            (ySpace >= yLimit ||
            (transform.position.y -
              sprite.height * transform.scale.y * 0.15f) <= 0)) {
            rigidBody.velocity.y *= (std::abs(rigidBody.velocity.y) >= 800) ?
              -1 : -bounce.bounceSpeedup;
          }
        }

      } else {
        eventManager->emitEvent<OutOfBoundsEvent>(entity, eventManager);
      }
    }
  }
}
