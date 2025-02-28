// Copyright 2024, Kenneth Villalobos

#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

#include <memory>

#include "../AssetStore/AssetStore.h"
#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../Events/EnemyKilledEvent.h"
#include "../Events/EntityDefeatedEvent.h"
#include "../Events/EntityRespawnedEvent.h"
#include "../Events/GameOverEvent.h"
#include "../Events/GamePausedEvent.h"
#include "../Events/GameUnPausedEvent.h"
#include "../Events/ProjectileShootedEvent.h"
#include "../Events/SpecialAttackActivatedEvent.h"

class SoundSystem : public System {
public:
  SoundSystem();

  void update(std::shared_ptr<AssetStore>& assetStore);

  void subscribeToEnemyKilledEvents(
    std::shared_ptr<EventManager>& eventManager);
  void subscribeToEntityDefeatedEvents(
    std::shared_ptr<EventManager>& eventManager);
  void subscribeToEntityRespawnedEvents(
    std::shared_ptr<EventManager>& eventManager);
  void subscribeToGamePausedEvents(
    std::shared_ptr<EventManager>& eventManager);
  void subscribeToGameUnPausedEvents(
    std::shared_ptr<EventManager>& eventManager);
  void subscribeToProjectileShootedEvents(
    std::shared_ptr<EventManager>& eventManager);
  void subscribeToSpecialAttackActivatedEvents(
    std::shared_ptr<EventManager>& eventManager);

  void onEnemyKilledEvent(EnemyKilledEvent& event);
  void onEntityDefeatedEvent(EntityDefeatedEvent& event);
  void onEntityRespawnedEvent(EntityRespawnedEvent& event);
  void onGamePausedEvent(GamePausedEvent& event);
  void onGameUnPausedEvent(GameUnPausedEvent& event);
  void onProjectileShootedEvent(ProjectileShootedEvent& event);
  void onSpecialAttackActivatedEvent(SpecialAttackActivatedEvent& event);
};

#endif  // SOUNDSYSTEM_H
