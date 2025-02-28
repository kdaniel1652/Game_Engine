// Copyright 2024 Kenneth Villalobos

#include "AssetStore.h"
#include <SDL_image.h>

void AssetStore::clearAssets() {
  for (auto& texture : this->textures) {
    SDL_DestroyTexture(texture.second);
  }
  this->textures.clear();

  for (auto& font : this->fonts) {
    TTF_CloseFont(font.second);
  }
  this->fonts.clear();

  for (auto& song : this->songs) {
    Mix_FreeMusic(song.second.first);
  }
  this->songs.clear();

  for (auto& sound : this->sounds) {
    Mix_FreeChunk(sound.second);
  }
  this->sounds.clear();
}

void AssetStore::addTexture(const std::string& assetId,
  const std::string& filepath, SDL_Renderer* renderer) {
  SDL_Surface* surface = IMG_Load(filepath.c_str());
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_FreeSurface(surface);

  this->textures[assetId] = texture;
}

void AssetStore::addFont(const std::string& assetId,
  const std::string& filepath, const int fontSize) {
  TTF_Font* font = TTF_OpenFont(filepath.c_str(), fontSize);

  this->fonts[assetId] = font;
}

void AssetStore::addSong(const std::string& assetId,
  const std::string& filepath, const int volume) {
  Mix_Music* song = Mix_LoadMUS(filepath.c_str());

  this->songs[assetId] = std::pair<Mix_Music*, int>(song, volume);
}

void AssetStore::addSound(const std::string& assetId,
  const std::string& filepath, const int volume) {
  Mix_Chunk* sound = Mix_LoadWAV(filepath.c_str());
  Mix_VolumeChunk(sound, volume);

  this->sounds[assetId] = sound;
}
