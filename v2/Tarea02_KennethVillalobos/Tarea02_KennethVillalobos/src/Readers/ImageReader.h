// Copyright 2024, Kenneth Villalobos

#ifndef IMAGEREADER_H
#define IMAGEREADER_H

#include <memory>
#include <SDL.h>
#include <string>
#include "../AssetStore/AssetStore.h"
#include "Reader.h"

class ImageReader : Reader {
protected:
  std::string label;
  std::string path;
  int width;
  int height;
  friend class Game;

protected:
  virtual std::istream& read(std::istream& is) override {
    return is >> this->label >> this->path >> this->width >> this->height;
  };

public:
  ImageReader() = default;
  virtual ~ImageReader() = default;

  void build(std::shared_ptr<AssetStore>& assetStore,
    SDL_Renderer* renderer) {
    assetStore->addTexture(this->label, this->path,
      renderer);
  }
};

#endif  // IMAGEREADER_H
