// Copyright 2024, Kenneth Villalobos

#include "../Components/AlliesComponent.h"
#include "../Components/LifesComponent.h"
#include "../Components/SpecialAttackComponent.h"
#include "../Components/TagComponent.h"
#include "DamageSystem.h"
#include "../Events/EnemyKilledEvent.h"
#include "../Events/EntityDefeatedEvent.h"
#include "../Events/GameOverEvent.h"

#include "../Utils/common.h"

void DamageSystem::handleEntity(Entity& entity,
  std::shared_ptr<EventManager>& eventManager) {
  // Check in case the entity has lives
  if (entity.hasComponent<LifesComponent>()) {
    auto& lifes = entity.getComponent<LifesComponent>();
    --lifes.lifes;
    if (entity.hasComponent<SpecialAttackComponent>()) {
      auto& specialAttack = entity.getComponent<SpecialAttackComponent>();
      if (specialAttack.clone.isValid()) {
        specialAttack.clone.kill();
        specialAttack.clone = Entity(0);
      }
      specialAttack.msSinceLastUsed = 0;
      specialAttack.msSinceActivated = 0;
    }

    if (lifes.lifes > 0) {
      eventManager->emitEvent<EntityDefeatedEvent>(entity);
    }
    else {
      entity.kill();

      if (entity.getComponent<TagComponent>().tag == tags::PLAYER) {
        eventManager->emitEvent<GameOverEvent>();
      } else if (entity.getComponent<TagComponent>().tag == tags::ENEMY) {
        eventManager->emitEvent<EnemyKilledEvent>(entity);
      }
      
    }
  }
  else {
    entity.kill();
    if (entity.getComponent<TagComponent>().tag == tags::ENEMY) {
      eventManager->emitEvent<EnemyKilledEvent>(entity);
    }
  }
}

DamageSystem::DamageSystem() {
}

void DamageSystem::subscribeToCollisionEvents(
  std::shared_ptr<EventManager>& eventManager) {
  eventManager->subscribeToEvent<DamageSystem, CollisionEvent>(this,
    &DamageSystem::onCollisionEvent);
}

void DamageSystem::onCollisionEvent(CollisionEvent& event) {
  if (!event.first.hasComponent<AlliesComponent>() ||
    !event.second.hasComponent<AlliesComponent>()) {
    this->handleEntity(event.first, event.eventManager);
    this->handleEntity(event.second, event.eventManager);
    
  } else {
    if (event.first.getComponent<AlliesComponent>().team !=
      event.second.getComponent<AlliesComponent>().team) {
      this->handleEntity(event.first, event.eventManager);
      this->handleEntity(event.second, event.eventManager);
    }
  }
  
}
