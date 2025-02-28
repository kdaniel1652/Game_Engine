// Copyright 2024, Kenneth Villalobos

#include <SDL_image.h>

#include "AssetStore.h"

void AssetStore::clearAssets() {
  for (auto texture : this->textures) {
    SDL_DestroyTexture(texture.second);
  }
  this->textures.clear();

  for (auto font : this->fonts) {
    TTF_CloseFont(font.second);
  }
  this->fonts.clear();

  for (auto song : this->songs) {
    Mix_FreeMusic(song.second);
  }
  this->songs.clear();

  for (auto sound : this->sounds) {
    Mix_FreeChunk(sound.second);
  }
  this->sounds.clear();
}

void AssetStore::addTexture(const std::string& assetId,
  const std::string& filepath, SDL_Renderer* renderer) {
  SDL_Surface* surface = IMG_Load(filepath.c_str());
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_FreeSurface(surface);

  this->textures.emplace(assetId, texture);
}

SDL_Texture* AssetStore::getTexture(const std::string& assetId) {
  return this->textures[assetId];
}

void AssetStore::addFont(const std::string& assetId,
  const std::string& filepath, const int fontSize) {
  TTF_Font* font = TTF_OpenFont(filepath.c_str(), fontSize);

  this->fonts.emplace(assetId, font);
}

TTF_Font* AssetStore::getFont(const std::string& assetId) {
  return this->fonts[assetId];
}

void AssetStore::addSong(const std::string& assetId,
  const std::string& filepath) {
  Mix_Music* song = Mix_LoadMUS(filepath.c_str());

  this->songs.emplace(assetId, song);
}

Mix_Music* AssetStore::getSong(const std::string& assetId) {
  return this->songs[assetId];
}

void AssetStore::addSound(const std::string& assetId,
  const std::string& filepath) {
  Mix_Chunk* sound = Mix_LoadWAV(filepath.c_str());

  this->sounds.emplace(assetId, sound);
}

Mix_Chunk* AssetStore::getSound(const std::string& assetId) {
  return this->sounds[assetId];
}
