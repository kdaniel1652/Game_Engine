// Copyright 2024, Kenneth Villalobos

#include "../Components/TagComponent.h"
#include "EntityCleanerSystem.h"
#include "../Events/EnemyKilledEvent.h"

#include "../Utils/common.h"

EntityCleanerSystem::EntityCleanerSystem() {
}

void EntityCleanerSystem::subscribeToOutOfBoundsEvents(
  std::shared_ptr<EventManager>& eventManager) {
  eventManager->subscribeToEvent<EntityCleanerSystem, OutOfBoundsEvent>(
    this, &EntityCleanerSystem::onOutOfBoundsEvent);
}

void EntityCleanerSystem::onOutOfBoundsEvent(OutOfBoundsEvent& event) {
  event.outEntity.kill();
  if (event.outEntity.getComponent<TagComponent>().tag == tags::ENEMY) {
    event.eventManager->emitEvent<EnemyKilledEvent>(event.outEntity);
  }
}
