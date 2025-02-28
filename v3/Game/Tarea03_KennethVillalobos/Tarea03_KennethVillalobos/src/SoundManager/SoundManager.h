// Copyright 2024 Kenneth Villalobos

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "../AssetStore/AssetStore.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

typedef std::map<std::string, std::vector<std::string>> actionSounds;

class SoundManager {
private:
  std::map<std::string, actionSounds> sounds;

public:
  SoundManager();
  ~SoundManager() = default;

  inline void clear() {
    this->sounds.clear();
  }

  void addSound(const std::string& entityType, const std::string& action,
    const std::string& soundLabel);

  bool hasSound(const std::string& entityType,
    const std::string& action) const;

  inline bool hasEntity(const std::string& entityType) const {
    return this->sounds.find(entityType) != this->sounds.end();
  }

  void playSound(const std::string& entityType,
    const std::string& action) const;
};

#endif  // SOUNDMANAGER_H
