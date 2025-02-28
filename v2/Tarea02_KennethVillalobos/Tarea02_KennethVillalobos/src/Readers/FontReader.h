// Copyright 2024, Kenneth Villalobos

#ifndef FONTREADER_H
#define FONTREADER_H

#include <memory>
#include <SDL.h>
#include <string>
#include "../AssetStore/AssetStore.h"
#include "Reader.h"

class FontReader : Reader {
protected:
  std::string label;
  std::string path;
  int size;
  friend class Game;

protected:
  virtual std::istream& read(std::istream& is) override {
    return is >> this->label >> this->path >> this->size;
  };

public:
  FontReader() = default;
  virtual ~FontReader() = default;

  void build(std::shared_ptr<AssetStore>& assetStore) {
    assetStore->addFont(this->label, this->path, this->size);
  }
};

#endif  // FONTREADER_H
