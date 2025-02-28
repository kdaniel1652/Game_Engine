// Copyright 2024, Kenneth Villalobos

#include <SDL_mixer.h>

#include "../Components/SoundComponent.h"
#include "../Components/TagComponent.h"

#include "SoundSystem.h"

#include "../Utils/common.h"
#include "../Utils/RandomGenerator.h"

SoundSystem::SoundSystem() {
  this->requireComponent<SoundComponent>();
  this->requireComponent<TagComponent>();

  Mix_Volume(-1, MIX_MAX_VOLUME);
}

void SoundSystem::update(std::shared_ptr<AssetStore>& assetStore) {
  for (Entity entity : this->getSystemEntities()) {
    auto& sound = entity.getComponent<SoundComponent>();
    while (sound.timesMustBePlayed > 0) {
      RandomGenerator generator(0, sound.assetIds.size());
      size_t soundPicked = generator.generate();

      Mix_VolumeChunk(assetStore->getSound(sound.assetIds[soundPicked]),
        sound.volumes[soundPicked]);
      Mix_PlayChannel(-1,
        assetStore->getSound(sound.assetIds[soundPicked]), 0);

      --sound.timesMustBePlayed;
    }
  }
}

void SoundSystem::subscribeToEnemyKilledEvents(
  std::shared_ptr<EventManager>& eventManager) {
  eventManager->subscribeToEvent<SoundSystem, EnemyKilledEvent>(this,
    &SoundSystem::onEnemyKilledEvent);
}

void SoundSystem::subscribeToEntityDefeatedEvents(
  std::shared_ptr<EventManager>& eventManager) {
  eventManager->subscribeToEvent<SoundSystem, EntityDefeatedEvent>(this,
    &SoundSystem::onEntityDefeatedEvent);
}

void SoundSystem::subscribeToEntityRespawnedEvents(
  std::shared_ptr<EventManager>& eventManager) {
  eventManager->subscribeToEvent<SoundSystem, EntityRespawnedEvent>(this,
    &SoundSystem::onEntityRespawnedEvent);
}

void SoundSystem::subscribeToGamePausedEvents(
  std::shared_ptr<EventManager>& eventManager) {
  eventManager->subscribeToEvent<SoundSystem, GamePausedEvent>(this,
    &SoundSystem::onGamePausedEvent);
}

void SoundSystem::subscribeToGameUnPausedEvents(
  std::shared_ptr<EventManager>& eventManager) {
  eventManager->subscribeToEvent<SoundSystem, GameUnPausedEvent>(this,
    &SoundSystem::onGameUnPausedEvent);
}

void SoundSystem::subscribeToProjectileShootedEvents(
  std::shared_ptr<EventManager>& eventManager) {
  eventManager->subscribeToEvent<SoundSystem, ProjectileShootedEvent>(this,
    &SoundSystem::onProjectileShootedEvent);
}

void SoundSystem::subscribeToSpecialAttackActivatedEvents(
  std::shared_ptr<EventManager>& eventManager) {
  eventManager->subscribeToEvent<SoundSystem, SpecialAttackActivatedEvent>(
    this, &SoundSystem::onSpecialAttackActivatedEvent);
}

void SoundSystem::onEnemyKilledEvent(EnemyKilledEvent& event) {
  for (Entity sound : this->getSystemEntities()) {
    if (sound.getComponent<TagComponent>().tag ==
      tags::sounds::ENEMY_KILLED) {
      ++sound.getComponent<SoundComponent>().timesMustBePlayed;
    }
  }
}

void SoundSystem::onEntityDefeatedEvent(EntityDefeatedEvent& event) {
  for (Entity sound : this->getSystemEntities()) {
    if (sound.getComponent<TagComponent>().tag ==
      tags::sounds::PLAYER_KILLED) {
      ++sound.getComponent<SoundComponent>().timesMustBePlayed;
    }
  }
}

void SoundSystem::onEntityRespawnedEvent(EntityRespawnedEvent& event) {
  for (Entity sound : this->getSystemEntities()) {
    if (sound.getComponent<TagComponent>().tag ==
      tags::sounds::REVIVE) {
      ++sound.getComponent<SoundComponent>().timesMustBePlayed;
    }
  }
}

void SoundSystem::onGamePausedEvent(GamePausedEvent& event) {
  for (Entity sound : this->getSystemEntities()) {
    if (sound.getComponent<TagComponent>().tag ==
      tags::sounds::PAUSE) {
      ++sound.getComponent<SoundComponent>().timesMustBePlayed;
    }
  }
}

void SoundSystem::onGameUnPausedEvent(GameUnPausedEvent& event) {
  for (Entity sound : this->getSystemEntities()) {
    if (sound.getComponent<TagComponent>().tag ==
      tags::sounds::PAUSE) {
      ++sound.getComponent<SoundComponent>().timesMustBePlayed;
    }
  }
}

void SoundSystem::onProjectileShootedEvent(ProjectileShootedEvent& event) {
  for (Entity sound : this->getSystemEntities()) {
    if (sound.getComponent<TagComponent>().tag ==
      tags::sounds::PROJECTILE_SHOOTED) {
      ++sound.getComponent<SoundComponent>().timesMustBePlayed;
    }
  }
}

void SoundSystem::onSpecialAttackActivatedEvent(
  SpecialAttackActivatedEvent& event) {
  for (Entity sound : this->getSystemEntities()) {
    if (sound.getComponent<TagComponent>().tag ==
      tags::sounds::SPECIAL_ATTACK) {
      ++sound.getComponent<SoundComponent>().timesMustBePlayed;
    }
  }
}
