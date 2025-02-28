// Copyright 2024, Kenneth Villalobos

#include <SDL_mixer.h>
#include "MusicManager.h"

void MusicManager::playSong(const std::string& songLabel,
  std::shared_ptr<AssetStore>& assetStore) {
  Mix_PauseMusic();
  this->currentSong = songLabel;

  std::pair<Mix_Music*, int> song = assetStore->getSong(songLabel);
  Mix_VolumeMusic((MIX_MAX_VOLUME * song.second) / 100);
  Mix_PlayMusic(song.first, -1);
  this->isPlaying = true;
}

void MusicManager::pauseSong() {
  Mix_PauseMusic();
  this->isPlaying = false;
}

void MusicManager::resumeSong() {
  Mix_ResumeMusic();
  this->isPlaying = true;
}
