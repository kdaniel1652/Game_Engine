// Copyright 2024 Kenneth Villalobos

#ifndef ASSETSTORE_H
#define ASSETSTORE_H

#include <map>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>

class AssetStore {
private:
  std::map<std::string, SDL_Texture*> textures;
  std::map < std::string, TTF_Font*> fonts;
  std::map<std::string, std::pair<Mix_Music*, int>> songs;
  std::map<std::string, Mix_Chunk*> sounds;

public:
  AssetStore() = default;
  ~AssetStore() = default;

  void clearAssets();

  void addTexture(const std::string& assetId, const std::string& filepath,
    SDL_Renderer* renderer);
  inline SDL_Texture* getTexture(const std::string& assetId) {
    return this->textures.at(assetId);
  }

  void addFont(const std::string& assetId, const std::string& filepath,
    const int fontSize);
  inline TTF_Font* getFont(const std::string& assetId) {
    return this->fonts.at(assetId);
  }

  void addSong(const std::string& assetId, const std::string& filepath,
    const int volumne);
  inline std::pair<Mix_Music*, int> getSong(const std::string& assetId) {
    return this->songs.at(assetId);
  }

  void addSound(const std::string& assetId, const std::string& filepath,
    const int volume);
  inline Mix_Chunk* getSound(const std::string& assetId) {
    return this->sounds.at(assetId);
  }
};

#endif  // ASSETSTORE_H
