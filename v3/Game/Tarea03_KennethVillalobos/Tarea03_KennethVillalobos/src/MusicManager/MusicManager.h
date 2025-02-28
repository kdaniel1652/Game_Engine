// Copyright 2024, Kenneth Villalobos

#ifndef MUSICSMANAGER_H
#define MUSICSMANAGER_H

#include "../AssetStore/AssetStore.h"
#include <memory>
#include <string>

class MusicManager {
private:
  bool isPlaying = false;
  std::string currentSong = std::string("");

public:
  MusicManager() = default;
  ~MusicManager() = default;

  void playSong(const std::string& songLabel,
    std::shared_ptr<AssetStore>& assetStore);

  inline bool playing() const {
    return this->isPlaying;
  }
  inline std::string getCurrentSong() const {
    return this->currentSong;
  }

  void pauseSong();
  void resumeSong();
};

#endif  // MUSICSMANAGER_H
