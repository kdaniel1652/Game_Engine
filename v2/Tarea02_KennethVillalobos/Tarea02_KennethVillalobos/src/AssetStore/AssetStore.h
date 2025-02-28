// Copyright 2024, Kenneth Villalobos

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
  std::map<std::string, TTF_Font*> fonts;
  std::map<std::string, Mix_Music*> songs;
  std::map<std::string, Mix_Chunk*> sounds;

public:
  AssetStore() = default;
  ~AssetStore() = default;

  void clearAssets();

  void addTexture(const std::string& assetId, const std::string& filepath,
    SDL_Renderer* renderer);
  SDL_Texture* getTexture(const std::string& assetId);

  void addFont(const std::string& assetId, const std::string& filepath,
    const int fontSize);
  TTF_Font* getFont(const std::string& assetId);

  void addSong(const std::string& assetId, const std::string& filepath);
  Mix_Music* getSong(const std::string& assetId);

  void addSound(const std::string& assetId, const std::string& filepath);
  Mix_Chunk* getSound(const std::string& assetId);
};

#endif  // ASSETSTORE_H
