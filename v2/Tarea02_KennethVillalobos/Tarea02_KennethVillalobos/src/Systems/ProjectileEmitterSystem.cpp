// Copyright 2024, Kenneth Villalobos

#include <cmath>
#include <glm/glm.hpp>

#include "../Components/AlliesComponent.h"
#include "../Components/CircleColliderComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/RespawnComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TagComponent.h"
#include "../Components/TransformComponent.h"

#include "../Events/ProjectileShootedEvent.h"

#include "ProjectileEmitterSystem.h"

#include "../Utils/common.h"

ProjectileEmitterSystem::ProjectileEmitterSystem() {
  this->requireComponent<ProjectileEmitterComponent>();
  this->requireComponent<TransformComponent>();
  this->requireComponent<SpriteComponent>();
  this->requireComponent<AlliesComponent>();
}

void ProjectileEmitterSystem::subscribeToMouseClickEvents(
  std::shared_ptr<EventManager>& eventManager) {
  eventManager->subscribeToEvent<ProjectileEmitterSystem, MouseClickEvent>(
    this, &ProjectileEmitterSystem::onMouseClickEvent);
}

void ProjectileEmitterSystem::onMouseClickEvent(MouseClickEvent& event) {
  if (event.button == SDL_BUTTON_LEFT && event.buttonDown) {
    for (Entity entity : this->getSystemEntities()) {
      if (!entity.hasComponent<RespawnComponent>() ||
        !entity.getComponent<RespawnComponent>().defeated) {
        auto& emitter = entity.getComponent<ProjectileEmitterComponent>();
        auto& transform = entity.getComponent<TransformComponent>();
        auto& sprite = entity.getComponent<SpriteComponent>();
        auto& allies = entity.getComponent<AlliesComponent>();

        emitter.projectileWidth = (emitter.projectileWidth == 0) ?
          sprite.width : emitter.projectileWidth;
        emitter.projectileHeight = (emitter.projectileHeight == 0) ?
          sprite.width : emitter.projectileHeight;
        emitter.projectileScale = (emitter.projectileScale == glm::vec2()) ?
          transform.scale : emitter.projectileScale;
        emitter.srcRect =
          (emitter.srcRect.x == -1 || emitter.srcRect.x == -1) ?
          sprite.srcRect : emitter.srcRect;

        Entity bullet = entity.createAnotherEntity();
        bullet.addComponent<TagComponent>(tags::BULLET);
        bullet.addComponent<SpriteComponent>(
          emitter.assetId,
          emitter.projectileWidth,
          emitter.projectileHeight,
          emitter.srcRect.x,
          emitter.srcRect.y
        );

        glm::vec2 projectilePosition(0, 0);
        projectilePosition.x = transform.position.x +
          sprite.width * transform.scale.x / 2.0f -
          emitter.projectileWidth * emitter.projectileScale.x / 2.0f;
        projectilePosition.y = transform.position.y +
          sprite.height * transform.scale.y / 2.0f -
          emitter.projectileHeight * emitter.projectileScale.y / 2.0f;

        bullet.addComponent<TransformComponent>(projectilePosition,
          emitter.projectileScale, transform.rotation);

        const float radians = glm::radians(transform.rotation - 90);

        bullet.addComponent<RigidBodyComponent>(
          glm::vec2(emitter.speed * std::cos(radians),
            emitter.speed * std::sin(radians)), emitter.speed, false);
        bullet.addComponent<CircleColliderComponent>(
          std::min(emitter.projectileWidth * emitter.projectileScale.x,
            emitter.projectileHeight * emitter.projectileScale.y) * 0.8f);
        bullet.addComponent<AlliesComponent>(allies.team);

        event.eventManager->emitEvent<ProjectileShootedEvent>();
      }
    }
  }
}
