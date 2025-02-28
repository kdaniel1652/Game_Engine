// Copyright 2024, Kenneth Villalobos

#include <SDL_mixer.h>

#include "../Components/MusicComponent.h"

#include "MusicSystem.h"

MusicSystem::MusicSystem() {
  this->requireComponent<MusicComponent>();
}

void MusicSystem::update(Entity& song,
  std::shared_ptr<AssetStore>& assetStore) {
  auto& music = song.getComponent<MusicComponent>();
  if (!music.isPlaying) {
    Mix_PauseMusic();
    for (Entity entity : this->getSystemEntities()) {
      if (entity != song) {
        auto& otherMusic = entity.getComponent<MusicComponent>();
        otherMusic.isPlaying = false;
      }
    }

    Mix_VolumeMusic((MIX_MAX_VOLUME * music.volume) / 100);
    Mix_PlayMusic(assetStore->getSong(music.assetId), -1);
    music.isPlaying = true;
  }
}

void MusicSystem::subscribeToGamePausedEvents(
  std::shared_ptr<EventManager>& eventManager) {
  eventManager->subscribeToEvent<MusicSystem, GamePausedEvent>(this,
    &MusicSystem::onGamePausedEvent);
}

void MusicSystem::subscribeToGameUnPausedEvents(
  std::shared_ptr<EventManager>& eventManager) {
  eventManager->subscribeToEvent<MusicSystem, GameUnPausedEvent>(this,
    &MusicSystem::onGameUnPausedEvent);
}

void MusicSystem::onGamePausedEvent(GamePausedEvent& event) {
  (void)event;
  Mix_PauseMusic();
}

void MusicSystem::onGameUnPausedEvent(GameUnPausedEvent& event) {
  (void)event;
  Mix_ResumeMusic();
}
