// Copyright 2024 Kenneth Villalobos

#include "../Game/Game.h"
#include <SDL_mixer.h>
#include "SoundManager.h"
#include "../Util/RandomGenerator.h"

SoundManager::SoundManager() {
  Mix_Volume(-1, MIX_MAX_VOLUME);
}

void SoundManager::addSound(const std::string& entityType,
  const std::string& action, const std::string& soundLabel) {
  this->sounds[entityType][action].push_back(soundLabel);
}

bool SoundManager::hasSound(const std::string& entityType,
  const std::string& action) const {
  bool hasSound = false;

  if (this->hasEntity(entityType)) {
    hasSound = (this->sounds.at(entityType).find(action) !=
      this->sounds.at(entityType).end());
  }

  return hasSound;
}

void SoundManager::playSound(const std::string& entityType,
  const std::string& action) const {
  const std::vector<std::string>& availableSounds =
    this->sounds.at(entityType).at(action);

  RandomGenerator generator(0, availableSounds.size());
  size_t soundPicked = generator.generate();
  Mix_Chunk* sound =
    Game::getInstance().assetStore->getSound(availableSounds[soundPicked]);
  Mix_PlayChannel(-1, sound, 0);
}
