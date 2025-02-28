// Copyright 2024, Kenneth Villalobos

#include "../Components/KeyboardControllerComponent.h"
#include "../Components/RespawnComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/TransformComponent.h"

#include "../Events/EntityRespawnedEvent.h"

#include "RespawnSystem.h"

RespawnSystem::RespawnSystem() {
  this->requireComponent<RespawnComponent>();
  this->requireComponent<TransformComponent>();
  this->requireComponent<SpriteComponent>();
}

void RespawnSystem::update(std::shared_ptr<EventManager>& eventManager,
  const int msSinceLastUpdate) {
  for (Entity entity : this->getSystemEntities()) {
    auto& respawn = entity.getComponent<RespawnComponent>();
    if (respawn.defeated) {
      if (respawn.msSinceDefeat >= respawn.msToRespawn) {
        auto& transform = entity.getComponent<TransformComponent>();
        auto& sprite = entity.getComponent<SpriteComponent>();

        transform.position.x = respawn.respawnPosition.x;
        transform.position.y = respawn.respawnPosition.y;

        if (entity.hasComponent<RigidBodyComponent>()) {
          auto& rigidBody = entity.getComponent<RigidBodyComponent>();
          rigidBody.velocity = glm::vec2(0);
        }

        if (entity.hasComponent<KeyboardControllerComponent>()) {
          auto& keyboard = entity.getComponent<KeyboardControllerComponent>();
          keyboard.up = false;
          keyboard.right = false;
          keyboard.down = false;
          keyboard.left = false;
        }

        respawn.defeated = false;
        respawn.msSinceDefeat = 0;
        respawn.msSinceRespawn = 0;

        eventManager->emitEvent<EntityRespawnedEvent>();
      } else {
        respawn.msSinceDefeat += msSinceLastUpdate;
      }
    } else if (respawn.msSinceRespawn < MS_GRACE_TIME) {
      respawn.msSinceRespawn += msSinceLastUpdate;
    }
  }
}

void RespawnSystem::subscribeToEntityDefeatedEvents(
  std::shared_ptr<EventManager>& eventManager) {
  eventManager->subscribeToEvent<RespawnSystem, EntityDefeatedEvent>(this,
    &RespawnSystem::onEntityDefeatedEvent);
}

void RespawnSystem::onEntityDefeatedEvent(EntityDefeatedEvent& event) {
  if (event.defeatedEntity.hasComponent<RespawnComponent>()) {
    auto& respawn = event.defeatedEntity.getComponent<RespawnComponent>();
    respawn.defeated = true;
    respawn.msSinceDefeat = 0;
  }
}
