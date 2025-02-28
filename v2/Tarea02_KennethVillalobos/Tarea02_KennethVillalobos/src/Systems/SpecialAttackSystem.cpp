// Copyright 2024, Kenneth Villalobos

#include "../Components/AlliesComponent.h"
#include "../Components/TagComponent.h"
#include "../Components/KeyboardControllerComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/RespawnComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpecialAttackComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"

#include "../Events/SpecialAttackActivatedEvent.h"

#include "SpecialAttackSystem.h"

#include "../Utils/common.h"

SpecialAttackSystem::SpecialAttackSystem() {
  this->requireComponent<SpriteComponent>();
  this->requireComponent<TransformComponent>();
  this->requireComponent<RigidBodyComponent>();
  this->requireComponent<KeyboardControllerComponent>();
  this->requireComponent<ProjectileEmitterComponent>();
  this->requireComponent<AlliesComponent>();
  this->requireComponent<SpecialAttackComponent>();
}

void SpecialAttackSystem::update(const int msSinceLastUpdate) {
  for (Entity entity : this->getSystemEntities()) {
    if (!entity.hasComponent<RespawnComponent>() ||
      !entity.getComponent<RespawnComponent>().defeated) {
      auto& specialAttack = entity.getComponent<SpecialAttackComponent>();
      if (specialAttack.clone.isValid()) {
        if (specialAttack.msSinceActivated >= specialAttack.msDuration) {
          specialAttack.clone.kill();
          specialAttack.clone = Entity(0);
          specialAttack.msSinceLastUsed = 0;
          specialAttack.msSinceActivated = 0;
        } else {
          specialAttack.msSinceActivated += msSinceLastUpdate;
        }
      } else {
        specialAttack.msSinceLastUsed += msSinceLastUpdate;
      }
    }
  }
}

void SpecialAttackSystem::subscribeToMouseClickEvents(
  std::shared_ptr<EventManager>& eventManager) {
  eventManager->subscribeToEvent<SpecialAttackSystem, MouseClickEvent>(
    this, &SpecialAttackSystem::onMouseClickEvent);
}

void SpecialAttackSystem::onMouseClickEvent(MouseClickEvent& event) {
  if (event.button == SDL_BUTTON_RIGHT && event.buttonDown) {
    for (Entity entity : this->getSystemEntities()) {
      if (!entity.hasComponent<RespawnComponent>() ||
        !entity.getComponent<RespawnComponent>().defeated) {
        auto& specialAttack = entity.getComponent<SpecialAttackComponent>();
        if (specialAttack.msSinceLastUsed >= specialAttack.msToBeAvailable) {
          auto& transform = entity.getComponent<TransformComponent>();
          auto& sprite = entity.getComponent<SpriteComponent>();
          auto& rigidBody = entity.getComponent<RigidBodyComponent>();
          auto& allies = entity.getComponent<AlliesComponent>();
          auto& emitter = entity.getComponent<ProjectileEmitterComponent>();

          Entity clone = entity.createAnotherEntity();
          specialAttack.clone = clone;
          clone.addComponent<TagComponent>(tags::CLONE);

          specialAttack.srcRect =
            (specialAttack.srcRect.x == -1 || specialAttack.srcRect.x == -1) ?
            sprite.srcRect : specialAttack.srcRect;

          clone.addComponent<SpriteComponent>(
            specialAttack.cloneAssetId,
            sprite.width,
            sprite.height,
            specialAttack.srcRect.x,
            specialAttack.srcRect.y
          );

          glm::vec2 clonePos = glm::vec2(0);
          const float radians = glm::radians(transform.rotation + 90);
          clonePos.x =
            transform.position.x +
            sprite.width * transform.scale.x * 1.3f * std::cos(radians);
          clonePos.y = transform.position.y +
            sprite.height * transform.scale.y * 1.3f * std::sin(radians);
          clone.addComponent<TransformComponent>(clonePos,
            transform.scale, transform.rotation + 180);

          clone.addComponent<RigidBodyComponent>(rigidBody.velocity,
            rigidBody.speed, rigidBody.speed);
          clone.addComponent<KeyboardControllerComponent>();
          clone.addComponent<AlliesComponent>(allies.team);
          clone.addComponent<ProjectileEmitterComponent>(emitter.assetId,
            emitter.speed, emitter.projectileWidth, emitter.projectileHeight,
            emitter.projectileScale);
          specialAttack.msSinceLastUsed = 0;
          specialAttack.msSinceActivated = 0;

          event.eventManager->emitEvent<SpecialAttackActivatedEvent>();
        }
      }
    }
  }
}
